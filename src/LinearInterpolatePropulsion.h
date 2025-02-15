#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
#include <cmath>

class LinearInterpolatePropulsion {
    public:
    //Linearly interpolates 2 vectors
    vector<double> linearInterpolate(vector<double> start, vector<double> end, double currentStep);

    //finds the 2 data points for the next linear interpolation
    vector<vector<double>> interpolateData(vector<vector<double>> data, double stepSize);

    //writes the final data to a CSV
    void writeToCSV(const std::vector<std::vector<double>>& data, const std::string& filename);

    private:
    
};
