#ifndef PHOENIX_POSITION_PROVIDER_H
#define PHOENIX_POSITION_PROVIDER_H

double linearInterp(double x, std::vector<double> all_x, std::vector<double> all_y);

bool fileExists(const std::string& filename);
std::vector<std::vector<float>> parseFile(const std::string& filename);

std::vector<double> convertToMs(std::vector<double> machData);
std::vector<double> initAltitudesVector();

#endif /* PHOENIX_POSITION_PROVIDER_H */