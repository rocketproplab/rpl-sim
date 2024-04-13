#ifndef SIMPARAMS_H
#define SIMPARAMS_H

#include <boost/program_options.hpp>
#include <iostream>
#include <string>

#include "exitCodeDefines.hpp"
namespace po = boost::program_options;

// A struct used by parse_command_line_arguments to return a lot of information.
struct CliParseResult {
    int exit_code;         // Exit code. 0 is okay, everything else is an error.
    po::variables_map vm;  // Map of named variables
};

// A struct containing decoded command line arguments
// and some inputs parsed from files.
struct SimParams {
    std::string init_state_path;
    std::string output_path;
};

struct ParseSimParamsResult {
    int exit_code;         // Exit code. 0 is okay, everything else is an error.
    SimParams sim_params;  // Read parameters
};

// Creates the options object
po::options_description get_options_description()
{
    po::options_description options("Arguments");
    options.add_options()("help,h", "Displays the help message")(
        "init-state,i", po::value<std::string>()->required(),
        "path of initial state configuration file")(
        "output,o", po::value<std::string>()->required(),
        "path of simulator output file");

    return options;
}

// JUST parses command line arguments.
CliParseResult parse_command_line_arguments(int argC, char *argV[])
{
    // Initialize result
    CliParseResult result;
    result.exit_code = EXIT_CODE_OK;

    // Get description
    po::options_description options = get_options_description();

    // Before running notify (which throws exceptions if the program option
    // requirements are not met) check if we parsed 'help.' If so, exit early
    // and display the help message.
    po::store(po::parse_command_line(argC, argV, options),
              result.vm);  // Store performs a best-effort parse without
                           // throwing exceptions
    if (result.vm.count("help")) {
        std::cout << options << "\n";  // TODO: Consider decoupling output logic
                                       // from parsing logic.

        result.exit_code = EXIT_CODE_DISPLAYED_HELP;
        return result;
    }

    // Try parsing command line arguments.
    try {
        po::notify(result.vm);
    } catch (std::exception &e) {
        std::cerr << " Error:" << e.what()
                  << std::endl;  // TODO: Consider decoupling output logic from
                                 // parsing logic.

        result.exit_code = EXIT_CODE_LINE_ARGUMENT_ERROR;
        return result;
    } catch (...) {
        std::cerr << "Unknown CLI error!"
                  << std::endl;  // TODO: Consider decoupling output logic from
                                 // parsing logic.

        result.exit_code = EXIT_CODE_LINE_ARGUMENT_ERROR;
        return result;
    }

    // At this point, our variables map is populated with valid values
    // Conduct any further filtering here.

    return result;
}

// Parses command line arguments and populates the given SimParams struct with
// the command line arguments.
//
// argC and argV are the values passed into main regarding the available command
// line arguments.
//
// Returns an integer exit code. If 0, the arguments were parsed correctly and
// the SimParams struct has valid data. If any exit code other than zero, the
// SimParams were not populated and the program should exit.

ParseSimParamsResult get_params(int argC, char *argV[])
{
    ParseSimParamsResult result;

    // Attempt to parse command line arguments
    CliParseResult cli_parse_result = parse_command_line_arguments(argC, argV);
    result.exit_code = cli_parse_result.exit_code;  // Exit early if
    if (result.exit_code != EXIT_CODE_OK) {
        return result;
    }

    result.sim_params.output_path =
        cli_parse_result.vm["output"].as<std::string>();

    return result;
}

#endif /* SIMPARAMS_H */
