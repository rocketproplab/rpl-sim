
#include <filesystem>

// TODO: Does this need bounds checking?
double linearInterp(double x, vector<double> all_x, vector<double> all_y) {
    if (all_x[0] == x) {
        return all_y[0];
    } else if (all_x[0] < x) {
        int pos = 0;
        while (all_x[pos] < x) {
            pos++;
        }
        double x1 = all_x[pos - 1];
        double x2 = all_x[pos];
        double y1 = all_y[pos - 1];
        double y2 = all_y[pos];
        double slope = (y2 - y1) / (x2 - x1);
        return y1 + (x - x1) * slope;
    } else { // if we are extrapolating behind all_x (only consider behind because we never extrapolate over)
        double x1 = all_x[1];
        double x2 = all_x[0];
        double y1 = all_y[1];
        double y2 = all_y[0];
        double slope = (y2 - y1) / (x2 - x1);
        return y1 + (x - x1) * slope;
    }
}

/// Parses a CSV file
vector<vector<float>> parseFile(const string& filename){
    vector<vector<float>> result; // Vector to store the final result

    std::ifstream atmos_file(filename);
    if (!atmos_file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << endl;
        return result; // Return an empty vector if the file cannot be opened
    }

    string line;
    while (std::getline(atmos_file, line)) {
        vector<float> row; // Vector to store the values of a single row

        std::istringstream iss(line);
        string value;
        while (std::getline(iss, value, ',')) {
            float floatValue = stof(value);
            row.push_back(floatValue);
        }

        result.push_back(row); // Add the row to the final result
    }

    atmos_file.close();

    return result;
}

/// Returns true if the file the given path exists, false otherwise.
bool fileExists(const std::string& path)
{
    const std::filesystem::path pathThatMightExist(path);
    return std::filesystem::exists(pathThatMightExist);
}


std::vector<double> convertToMs(std::vector<double> machData) 
{
    vector<double> toReturn;
    for(double num: machData){
        num = num*343;
        toReturn.push_back(num);
    }
    // cout << toReturn[0] << endl;
    // cout << toReturn[99] << endl;
    return toReturn;
}

std::vector<double> initAltitudesVector()
{
    vector<double> toReturn;
    for(int i = 0; i < 10001; i++){
        toReturn.push_back(double(i)); 
    }
    return toReturn;
}