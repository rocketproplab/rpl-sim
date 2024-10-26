#ifndef VIRTUAL_BAROMETER
#define VIRTUAL_BAROMETER
#include "PhoenixPositionProvider.h"
#include <random>
#include "Vector3.hpp"

class VirtualBarometer {
    public:
        VirtualBarometer(unsigned int rs, double alt, double ns);
        double get_reported_altitude();
        void process(double);
        PhoenixPositionProvider position_provider;
    private:
        unsigned int random_seed;
        double altitude_of_launch_site;
        double noise;
        Vector3 current_position;
        std::default_random_engine rng;
        std::uniform_real_distribution<double> distribution;
};

#endif