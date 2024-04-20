#include "VirtualBarometer.h"

VirtualBarometer::VirtualBarometer(long rs, double alt, double ns): 
random_seed {rs}, altitude_of_launch_site {alt}, noise {ns} {
    // initialize position provider
    position_provider {};
    current_position {0, 0, altitude_of_launch_site};

    // initialize random number generator
    rng {};
    rng.seed(random_seed);
    rng_provider {-noise, noise};
};

void VirtualBarometer::process(double deltatime) {
    position_provider.process(deltatime);
    current_position = current_position + position_provider.getPosition();
}

double VirtualBarometer::get_reported_altitude() {
    double rand = rng_provider(rng);
    return current_position.z + rand;
}