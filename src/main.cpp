#include "SimParams.hpp"
#include "exitCodeDefines.hpp"
#include "output_types.hpp"
#include <iostream>
#include <string>
#include <boost/asio.hpp>

boost::asio::io_context ioctx;
boost::asio::serial_port* port;
boost::asio::streambuf response;
std::size_t msg_len;

int main(int ac, char *av[])
{

    ParseSimParamsResult result = get_params(ac, av);
    SimParams params = result.sim_params;
    DataLog data;

    data.write_to_file(params.output_path);

    if (result.exit_code != EXIT_CODE_OK) {
        return result.exit_code;
    }

    if(params.serial_port != "NUL"){
        try {
            port = new boost::asio::serial_port(ioctx, params.serial_port);
        }
        catch (boost::system::system_error &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return EXIT_CODE_INVALID_SERIAL;
        }
        port->set_option(boost::asio::serial_port_base::baud_rate(115200));
        port->set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::none));
        port->set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::none));
        port->set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::one));
        port->set_option(boost::asio::serial_port::character_size(boost::asio::serial_port::character_size(8)));

        msg_len = boost::asio::read_until(*port, response, "started");
        response.consume(msg_len);
        char msg = '0';
        while(msg <= '9'){
            boost::asio::write(*port, boost::asio::buffer(&msg, 1));
            msg_len = boost::asio::read_until(*port, response, "\r\n");
            std::string line(
                boost::asio::buffers_begin(response.data()),
                boost::asio::buffers_begin(response.data()) + msg_len);
            std::cout << "Received " << line << std::endl;
            response.consume(msg_len);
            msg++;
        }
    }
    


    delete port;
    return EXIT_CODE_OK;
}
