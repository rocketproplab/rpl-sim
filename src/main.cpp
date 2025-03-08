#include "SimParams.hpp"
#include "exitCodeDefines.hpp"
#include "output_types.hpp"
#include "../src/LinearInterpolatePropulsion.h"

#include "Physics.hpp"
#include "Vector3.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

double STEP_SIZE = 0.1;
/**
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
 */

std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    //initialize variables and create evenly spaced csv file
    start_csv(STEP_SIZE);
    std::string filename = "discrete_data_" + std::to_string(STEP_SIZE) + ".csv";
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open " << filename << std::endl;
        return 1;
    }

    // open output file for burn stage simulation data
    // csv columns: time, pos_x, pos_y, pos_z, vel_x, vel_y, vel_z
    std::ofstream outputFile("burn_output.csv");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open burn_output.csv for writing" << std::endl;
        return 1;
    }
    outputFile << "time,pos_x,pos_y,pos_z,vel_x,vel_y,vel_z\n";

    // initilize: starting with zero velocity at position 0
    Physics::XY_State currentState;
    currentState.position = Vector3(0, 0, 0);
    currentState.velocity = Vector3(0, 0, 0);

    std::string line;
    double prevTime = 0.0;
    bool firstLine = true;
    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;
        std::vector<std::string> tokens = split(line, ',');
        if (tokens.size() < 3) continue;  // there should be 3 columns

        double time = std::stod(tokens[0]);
        double airDensity = std::stod(tokens[1]);
        double acceleration = std::stod(tokens[2]);

        // Determine dt. For evenly spaced data, dt should be constant.
        double dt = firstLine ? 0.1 : (time - prevTime);
        firstLine = false;
        prevTime = time;

        // Update the state using the CSV sensor data.
        currentState = Physics::updateState(currentState, dt, acceleration, airDensity);

        // Write the current time, position, and velocity to the output CSV.
        outputFile << time << ","
                   << currentState.position.x << ","
                   << currentState.position.y << ","
                   << currentState.position.z << ","
                   << currentState.velocity.x << ","
                   << currentState.velocity.y << ","
                   << currentState.velocity.z << "\n";
    }

    inputFile.close();
    outputFile.close();

    std::cout << "Simulation complete. Output written to burn_output.csv" << std::endl;
    return 0;
}