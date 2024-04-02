#ifndef SIMPARAMS_H
#define SIMPARAMS_H

#include <iostream>
#include <string>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

// A struct containing decoded command line arguments
// and some inputs parsed from files.
struct SimParams
{
    std::string init_state_path;
    std::string output_path;
};

// Parses command line arguments and populates the given SimParams struct with the command
// line arguments.
//
// argC and argV are the values passed into main regarding the available command line arguments.
//
// Returns an integer exit code. If 0, the arguments were parsed correctly and the SimParams struct has
// valid data. If any exit code other than zero, the SimParams were not populated and the program should exit.
int parse_sim_params_from_command_line_arguments(SimParams& params, int argC, char *argV[])
{
    po::options_description options("Arguments");
    options.add_options()
        ("help,h", "Displays the help message")
        ("init-state,i", po::value<std::string>(params->init_state_path)->required(), "path of initial state configuration file")
        ("output,o", po::value<std::string>(params->output_path)->required(), "path of simulator output file")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argC, argV, options), vm);

    if (vm.count("help")) {
        std::cout << options << "\n";
        return EXIT_CODE_DISPLAYED_HELP;
    }

    try
    {
        po::notify(vm);
    }
    catch(std::exception& e)
    {
        std::cerr << " Error:" << e.what() << std::endl;
        return EXIT_CODE_LINE_ARGUMENT_ERROR;
    }
    catch(...)
    {
        std::cerr << "Unknown CLI error!" << std::endl;
        return EXIT_CODE_LINE_ARGUMENT_ERROR;
    }

    return 0;
}

#endif /* SIMPARAMS_H */