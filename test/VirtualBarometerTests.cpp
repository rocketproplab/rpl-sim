#include "catch2/catch_test_macros.hpp"
#include "../src/PhoenixPositionProvider.h"
#include "../src/VirtualBarometer.h"
#include "catch2/matchers/catch_matchers_floating_point.hpp"

constexpr double delta = 0.001;

TEST_CASE("Compare Barometer - Position Provider", "NORMAL") {
    unsigned int seed = 5; 
    double alt = 0.0;
    double noise = 0.1;
    VirtualBarometer vb {seed, alt, noise};
    vb.process(1);
    double target = vb.position_provider.getPosition().z;
    REQUIRE_THAT(vb.get_reported_altitude(), Catch::Matchers::WithinAbs(target, noise));
}

TEST_CASE("Ensure deterministic - Seperate barometers") {
    unsigned int seed = 5; 
    double alt = 0.0;
    double noise = 0.1;
    VirtualBarometer vb1 {seed, alt, noise};
    VirtualBarometer vb2 {seed, alt, noise};
    vb1.process(1);
    vb2.process(1);
    double vb1Altitude = vb1.get_reported_altitude();
    double vb2Altitude = vb2.get_reported_altitude();
    REQUIRE_THAT(vb1Altitude, Catch::Matchers::WithinAbs(vb2Altitude, delta));
}

TEST_CASE("Check altitude changes after process - Single barometer") {
    unsigned int seed = 5; 
    double alt = 0.0;
    double noise = 0.1;
    VirtualBarometer vb {seed, alt, noise};
    vb.process(1);
    double altitude_before = vb.get_reported_altitude();
    vb.process(1);
    double altitude_after = vb.get_reported_altitude();
    double diff = altitude_after - altitude_before;
    REQUIRE_THAT(diff, Catch::Matchers::WithinAbs(altitude_before, noise));
}

