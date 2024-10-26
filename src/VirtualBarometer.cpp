#include "VirtualBarometer.h"

VirtualBarometer::VirtualBarometer(unsigned int rs, double alt, double ns): 
    random_seed{rs}, altitude_of_launch_site{alt}, noise{ns}, position_provider{},
    rng {rs}, distribution {-ns, ns}
{
    // initialize position provider
    current_position = Vector3{0, 0, altitude_of_launch_site};
};

void VirtualBarometer::process(double deltatime) {
    std::cout << "PROCESSING NEW POSITION" << '\n';
    position_provider.process(deltatime);
    Vector3 new_position = position_provider.getPosition();
    current_position = current_position + new_position;
}

double VirtualBarometer::get_reported_altitude() {
    std::cout << "GETTING REPORTED ALTITUDE" << '\n';
    double rand = distribution(rng);
    return current_position.z + rand;
}