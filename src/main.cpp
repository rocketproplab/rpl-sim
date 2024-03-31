#include "optparse.h"

#include <iostream>

const std::string version =
    "%prog 1.0\nCopyright (C) 2023\n"
    "TODO MIT LICENSE";

int main(int argc, char *argv[])
{

    

    optparse::OptionParserExcept parser = optparse::OptionParserExcept().version(version)
          .description("Description")
          .epilog("Epilog");



    parser.add_option("--output")
        .help("The path at which to write the simulation dump file.");


    // --------------------------------

    optparse::OptionGroup position_provider("Position Provider Data");

    position_provider.add_option("--pp-atmosphere-isa-csv")
        .help("The path at which an atmosphere ISA datafile exists.");

    position_provider.add_option("--pp-thrust-curve-csv")
        .help("The path at which data for the thrust curve of the main engine exists.");

    position_provider.add_option("--pp-mach-vs-cd.csv")
        .help("TODO TODO IDK WTF THIS IS, ASK PROPULSION TEAM. REQUIRED THO :)");

    parser.add_option_group(position_provider);

    // --------------------------------

    try
    {
        const optparse::Values &options = parser.parse_args(argc, argv);
        const std::vector<std::string> args = parser.args();

        std::cout << "output: " << options["output"] << std::endl;

        std::cout << std::endl << "leftover arguments: " << std::endl;
        for (std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it)
        {
            std::cout << "arg: " << *it << std::endl;
        }
    }
    catch (int ret_code)
    {
        std::cout << "OptionParser has thrown " << ret_code << std::endl;
        return ret_code;
    }

    return 0;
}