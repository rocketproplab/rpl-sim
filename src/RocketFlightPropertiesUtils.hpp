#ifndef PHOENIX_POSITION_PROVIDER_H
#define PHOENIX_POSITION_PROVIDER_H

double linearInterp(double x, std::vector<double> all_x, std::vector<double> all_y);

bool fileExists(const std::string& filename);
std::vector<std::vector<float>> parseFile(const std::string& filename);


#endif /* PHOENIX_POSITION_PROVIDER_H */