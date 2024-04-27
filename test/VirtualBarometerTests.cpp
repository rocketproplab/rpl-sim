#include <catch2/catch_test_macros.hpp>
#include "../src/PhoenixPositionProvider.h"
#include "../src/VirtualBarometer.h"

constexpr double delta = 0.001;

TEST_CASE("Compare Barometer - Position Provider", "NORMAL") {
    long seed = 5; 
    double alt = 0.0;
    double noise = 1.0;
    VirtualBarometer vb {seed, alt, noise};
    vb.process(1);
    double target = vb.position_provider.getPosition().z;
    REQUIRE_THAT(vb.get_reported_altitude(), WithinABS(target, noise))
}

TEST_CASE("Ensure deterministic", "Seperate barometers") {
    long seed = 5; 
    double alt = 0.0;
    double noise = 1.0;
    VirtualBarometer vb1 {seed, alt, noise};
    VirtualBarometer vb2 {seed, alt, noise};
    vb1.process(1);
    vb2.process(1)
    double target = vb2.get_reported_altitude()
    REQUIRE_THAT(vb1.get_reported_altitude(), WithinABS(target, delta))
}

TEST_CASE("Ensure deterministic", "Single barometer") {
    long seed = 5; 
    double alt = 0.0;
    double noise = 1.0;
    VirtualBarometer vb {seed, alt, noise};
    vb.process(1);
    double altitude_before = vb.get_reported_altitude()
    vb.process(1);
    double altitude_after = vb.get_reported(altitude)
    double diff = altitude_after - altitude_before;
    REQUIRE_THAT(diff, WithinABS(altitude_before, delta))
}

