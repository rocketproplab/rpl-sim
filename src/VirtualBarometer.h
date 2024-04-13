#include "PhoenixPositionProvider.h"
#include <random>
#include "Vector3.hpp"

class VirtualBarometer {
    public:
        VirtualBarometer(long, double, double);
        double get_reported_altitude();
        void process(double);
    private:
        long random_seed;
        double altitude_of_launch_site;
        double noise;
        Vector3 current_position;
        PhoenixPositionProvider position_provider;
        std::default_random_engine rng;
};