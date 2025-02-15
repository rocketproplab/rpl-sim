#include "LinearInterpolatePropulsion.h"
using namespace std;
/*
TODO Add documentation
*/
vector<double> linearInterpolate(vector<double> start, vector<double> end, double currentStep){
    double t1 = start[0], acceleration1 = start[1], pressure1 = start[2];
    double t2 = end[0], acceleration2 = end[1], pressure2 = end[2];
    vector<double> interpolatedData;
    interpolatedData.push_back(currentStep);
    double timeDiff = (currentStep - t1) / (t2 - t1);
    interpolatedData.push_back(lerp(acceleration1, acceleration2, timeDiff));
    interpolatedData.push_back(lerp(pressure1, pressure2, timeDiff));
    return interpolatedData;  
}
/**
 * @input: data- data read from csv file
 *       : stepsize- how often we want 
 */
//@TODO use start as index and use while loop to iterate to currStep, avoid assigning vectors
// each loop in the for loop
vector<vector<double>> interpolateData(vector<vector<double>> data, double stepSize){
    vector<vector<double>> discreteData;
    // @TODO use alr created interpolate function
    double currentStep = 0;
    vector<double> start;
    vector<double> end;

    //iterate through each csv value
    for(int i = 0; i < data.size(); i++){
        if(currentStep > data[data.size() - 1][0]){
            break;
        }
        //if data alr exists for this step no need to interpolate
        //@TODO make # a constant
        if(data[i][0] + 0.0001 > currentStep && data[i][0] - 0.0001 < currentStep){
            discreteData.push_back(data[i]);
            currentStep += stepSize;
            start = data[i];
            end.clear();
        }
        //get to data point right after currentStep
        while(i < data.size() - 1){
            if(data[i][0] < currentStep && data[i+1][0] > currentStep){
                break;
            }
            i++;
        }
        start = data[i];
        end = data[i+1];
        i--;
        //placeholder function
        vector<double> newVect = linearInterpolate(start, end, currentStep);
        discreteData.push_back(newVect);
        currentStep += stepSize;
    }
    return discreteData;
    
}
    
void writeToCSV(const std::vector<std::vector<double>>& data, const std::string& filename) {
    // Create output file in data directory
    std::ofstream outputFile(filename);
    
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file:" << filename << std::endl;
        return;
    }

    // Write each row of data
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            outputFile << row[i];
            if (i != row.size() - 1) {
                outputFile << ",";  // Add comma between values
            }
        }
        outputFile << "\n";  // Newline after each row
    }

    outputFile.close();
    std::cout << "CSV file created: " << filename << std::endl;
}

int main()
{
    std::cout << "RUNNING FILE" << std::endl;
    std::string filename = "sim_data_nowind.csv";
    
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::vector<std::vector<double>> data;
    std::string line;

    while (std::getline(file, line)) {
        std::vector<double> row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            row.push_back(stold(cell));
        }

        data.push_back(row);
    }

    file.close();
    
    //
    std::cout << "RUNNING!!!!" << std::endl;
    vector<vector<double>> discreteData = interpolateData(data, 0.1);
    writeToCSV(discreteData, "discrete_data.csv");
    
    return 0;
}