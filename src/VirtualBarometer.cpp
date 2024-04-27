#include "VirtualBarometer.h"

VirtualBarometer::VirtualBarometer(long rs, double alt, double ns): 
    random_seed{rs}, altitude_of_launch_site{alt}, noise{ns}
{
    // initialize position provider
    position_provider = PhoenixPositionProvider{};
    current_position  = Vector3{0, 0, altitude_of_launch_site};

    // initialize random number generator
    rng = std::default_random_engine{};
    rng.seed(random_seed);
    rng_provider = std::uniform_real_distribution{-noise, noise};
};

void VirtualBarometer::process(double deltatime) {
    position_provider.process(deltatime);
    current_position = current_position + position_provider.getPosition();
}

double VirtualBarometer::get_reported_altitude() {
    double rand = rng_provider(rng);
    return current_position.z + rand;
}