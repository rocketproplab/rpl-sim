#include "exitCodeDefines.hpp"
#include "SimParams.hpp"

#include <iostream>
#include <string>
#include <boost/program_options.hpp>


namespace po = boost::program_options;

int main(int ac, char *av[])
{
    SimParams p;

    int exit_code = parse_command_line_arguments(p, ac, av);
    return exit_code;
}


