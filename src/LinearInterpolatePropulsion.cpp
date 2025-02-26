#include "LinearInterpolatePropulsion.h"
using namespace std;

double ACCEPTABLE_TIME_ERROR = 0.0001;

/*
 * Linearly interpolate two values based on a fraction
*/
double interpolate(double a, double b, double f)
{
    return a * (1.0 - f) + (b * f);
}

/**
* Linearly interpolates two points to get a correct value in the middle
*/
vector<double> linearInterpolate(vector<double> start, vector<double> end, double currentStep){
    //get our base values from the vector
    double t1 = start[0], acceleration1 = start[1], pressure1 = start[2];
    double t2 = end[0], acceleration2 = end[1], pressure2 = end[2];
    
    //create the new interpolated vector
    vector<double> interpolatedData;
    interpolatedData.push_back(currentStep);
    double timeDiff = (currentStep - t1) / (t2 - t1);
    interpolatedData.push_back(interpolate(acceleration1, acceleration2, timeDiff));
    interpolatedData.push_back(interpolate(pressure1, pressure2, timeDiff));
    return interpolatedData;  
}

/**
 * @input: data- data read from csv file
 *       : stepsize- how often we want there to be a data point ex: 0.1 = every .1 second 
 */
vector<vector<double>> interpolateData(vector<vector<double>> data, double stepSize){
    vector<vector<double>> discreteData;
    double currentStep = 0;
    vector<double> start;
    vector<double> end;

    //iterate through each csv value
    for(long unsigned int i = 0; i < data.size(); i++){
        if(currentStep > data[data.size() - 1][0]){
            break;
        }
        //if data already exists for this step no need to interpolate
        if(data[i][0] + ACCEPTABLE_TIME_ERROR > currentStep && 
            data[i][0] - ACCEPTABLE_TIME_ERROR < currentStep){
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
        //get vectors surrounding the current step time value
        start = data[i];
        end = data[i+1];
        i--;

        //get our new updated vector from linear interpolation
        vector<double> newVect = linearInterpolate(start, end, currentStep);
        discreteData.push_back(newVect);
        currentStep += stepSize;
    }
    return discreteData;
    
}
 
/**
  * Creates a csv from a data vector. This should be the linearly interpolated data 
 */   
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

/**
 * Helper function that starts the csv conversion
 */
int start(double stepSize){
    //open the csv file
    std::string filename = "sim_data_nowind.csv";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    //load the csv data into a vector for easy conversion
    std::vector<std::vector<double>> data;
    std::string line;
    while (std::getline(file, line)) {
        std::vector<double> row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            row.push_back(stod(cell));
        }

        data.push_back(row);
    }

    file.close();
    
    //interpolate the data and then write to a new csv with the step size in the name
    vector<vector<double>> discreteData = interpolateData(data, stepSize);
    std::string newFilename = "discrete_data_" + std::to_string(stepSize) + ".csv";
    writeToCSV(discreteData, newFilename);
    return 0;
}