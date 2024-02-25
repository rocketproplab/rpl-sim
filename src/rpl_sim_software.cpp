/* Name: rpl_sim_software.cpp
 * Descriptoion: send software simulation packet to the flight computer through
  serial
 */
#include "rpl_sim_host.h" 
using namespace Rocket;

#include <string>
#include <iostream>
#include <cstdio>

//Windoes OS API
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

int main(int argc, char* argv[]) {

    FILE *serial_port = fopen("/dev/ttyUSB0", "w"); // Open the serial port in write mode

    if (serial_port == nullptr) {
        std::cerr << "Failed to open the serial port." << std::endl;
    }

    //TO DO: determin how the time is synced throughout the program
    long time_millis = millis();
    long time_micros = micros();

    while (true) {
        sim_struct sim_data;
        //Refreshing the strut before sending through serial
        sim_data.curr_coords[0] = curr_coords()[0];
        sim_data.curr_coords[1] = curr_coords()[1];
        sim_data.curr_coords[2] = curr_coords()[2];
        sim_data.bmp_pressure = get_bmp_pressure();
        sim_data.bmp_altitude = get_bmp_altitude();
        sim_data.bmp_temperature = get_bmp_temperature();
        sim_data.sd_card_begin = get_sd_card_begin();
        sim_data.sd_card_open = get_sd_card_open();
        sim_data.solenoid1_state = get_solenoid_state1(); 
        sim_data.solenoid2_state = get_solenoid_state2();
        sim_data.pressure_transducer1 = get_pressure_transducer1();
        sim_data.pressure_transducer2 = get_pressure_transducer2();

        // Write data to the serial port
        fprintf(serial_port, "%s", sim_data);
        fflush(serial_port); //Flush the output buffer to ensure data is sent immediately
    }


    //Close the serial port
    fclose(serial_port);
}