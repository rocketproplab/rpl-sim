#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
#include <cmath>

    //math behind interpolation
    double interpolate(double a, double b, double f);
    
    //Linearly interpolates 2 vectors
    std::vector<double> linearInterpolate(std::vector<double> start, std::vector<double> end, double currentStep);

    //finds the 2 data points for the next linear interpolation
    std::vector<std::vector<double>> interpolateData(std::vector<std::vector<double>> data, double stepSize);

    //writes the final data to a CSV
    void writeToCSV(const std::vector<std::vector<double>>& data, const std::string& filename);

    int start(double stepSize);
