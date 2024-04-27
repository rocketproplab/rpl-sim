#include "PhoenixPositionProvider.h"
#include <random>
#include "Vector3.hpp"

class VirtualBarometer {
    public:
        VirtualBarometer(long, double, double);
        double get_reported_altitude();
        void process(double);
        PhoenixPositionProvider position_provider;
    private:
        long random_seed;
        double altitude_of_launch_site;
        double noise;
        Vector3 current_position;
        std::default_random_engine rng;
        std::uniform_real_distribution<> rng_provider;
};