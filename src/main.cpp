#include "SimParams.hpp"
#include "exitCodeDefines.hpp"
#include "output_types.hpp"

int main(int ac, char *av[])
{
    ParseSimParamsResult result = get_params(ac, av);
    SimParams params = result.sim_params;
    DataLog data;

    data.write_to_file(params.output_path);

    if (result.exit_code != EXIT_CODE_OK) {
        return result.exit_code;
    }

    return EXIT_CODE_OK;
}
