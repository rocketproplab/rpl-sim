
#include "exitCodeDefines.hpp"

#include "SimParams.hpp"


int main(int ac, char *av[])
{

    ParseSimParamsResult result = get_params(ac, av);

    if (result.exit_code != EXIT_CODE_OK) { return result.exit_code; }

    return EXIT_CODE_OK;
}


