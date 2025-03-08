//Imports needed to test
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <sstream>

//Imports the tested functions
#include "../src/PhoenixPositionProvider.h"
#include "../src/LinearInterpolatePropulsion.h"
#include "Physics.hpp"

//(1.0)
TEST_CASE("In pre-flight stage", "Pre-flight")
{
    PhoenixPositionProvider ppp{};
    REQUIRE(ppp.getFlightState() == PhoenixPositionProvider::State::PRE_FLIGHT);
}

// (2.0)
TEST_CASE("Ignite working normally", "Ignite")
{
    PhoenixPositionProvider ppp{};
    ppp.ignite();
    REQUIRE(ppp.getFlightState() == PhoenixPositionProvider::State::BURN);
    REQUIRE(ppp.didIgnite());
    // error if called twice
    REQUIRE_THROWS_AS(ppp.ignite(), std::runtime_error);
}

// (3.0)
TEST_CASE("Drogue stage okay", "Drogue")
{
    PhoenixPositionProvider ppp{};
    REQUIRE_THROWS_AS(ppp.drogue(), std::runtime_error);
    ppp.ignite();
    ppp.drogue();
    // error if called twice
    REQUIRE_THROWS_AS(ppp.drogue(), std::runtime_error);
    REQUIRE(ppp.getFlightState() == PhoenixPositionProvider::State::DROGUE);
}

// (4.0)
TEST_CASE("Chute stage okay", "Chute")
{
    PhoenixPositionProvider ppp{};
    REQUIRE_THROWS_AS(ppp.chute(), std::runtime_error);
    ppp.ignite();
    ppp.drogue();
    ppp.chute();
    // error if called twice
    REQUIRE_THROWS_AS(ppp.chute(), std::runtime_error);
    REQUIRE(ppp.getFlightState() == PhoenixPositionProvider::State::CHUTE);
}

// (5.0)
TEST_CASE("Rocket State Transitions to BURN to COAST after Fuel Cutoff")
{
    PhoenixPositionProvider ppp{};
    ppp.ignite();
    ppp.process(16.47);
    REQUIRE(ppp.getFlightState() == PhoenixPositionProvider::State::BURN);
    ppp.process(0.03);
    REQUIRE(ppp.getFlightState() == PhoenixPositionProvider::State::COAST);
}

// (6.0)
TEST_CASE(
    "Rocket State Will Remain BURN if currentTime is == BurnTime + "
    "IgnitionTime")
{
    PhoenixPositionProvider ppp{};
    ppp.ignite();
    ppp.process(16.47);
    REQUIRE(ppp.getFlightState() == PhoenixPositionProvider::State::BURN);
    ppp.process(0.01);
    // currentTime is 16.48 at this point, which is == to BurnTime
    REQUIRE(ppp.getFlightState() == PhoenixPositionProvider::State::BURN);
    ppp.process(0.01);
    // after this, currentTime is 16.49, which should transition rocket to COAST
    REQUIRE(ppp.getFlightState() == PhoenixPositionProvider::State::COAST);
}

// (7.0)
TEST_CASE("Testing State Transition, but with ignitionTime != 0")
{
    PhoenixPositionProvider ppp{};
    ppp.process(0.5);
    ppp.ignite();
    ppp.process(16.47);
    REQUIRE(ppp.getFlightState() == PhoenixPositionProvider::State::BURN);
    ppp.process(0.01);
    // currentTime is 16.48 at this point, which is == to BurnTime
    REQUIRE(ppp.getFlightState() == PhoenixPositionProvider::State::BURN);
    ppp.process(0.01);
    // after this, currentTime is 16.49, which should transition rocket to COAST
    REQUIRE(ppp.getFlightState() == PhoenixPositionProvider::State::COAST);
}

// (8.0)
TEST_CASE("Testing if y-vel decreases && y-pos increases in COAST stage")
{
    PhoenixPositionProvider ppp{};
    ppp.process(0.5);
    ppp.ignite();
    ppp.process(16.48);
    stateType burning = ppp.getCurrentConditions();
    ppp.process(0.01);
    stateType coasting = ppp.getCurrentConditions();

    REQUIRE(burning[2] < coasting[2]);  // y_pos while burn < y_pos during coast
    REQUIRE(burning[3] > coasting[3]);  // y_vel while burn > y_vel during coast
}

// (9.0)
TEST_CASE("Testing if y_pos/vel make sense in CHUTE stage")
{
    PhoenixPositionProvider ppp{};
    ppp.ignite();
    ppp.process(16.48);
    ppp.process(
        30);  // according to Yihong Sim, ~30 seconds into coasting is apogee
    ppp.drogue();
    stateType coasting = ppp.getCurrentConditions();
    ppp.process(
        10);  // 10 seconds after that, rocket should definitely be coming down
    stateType drogue = ppp.getCurrentConditions();
    REQUIRE(coasting[2] >
            drogue[2]);  // y_pos while coasting > y_pos during drogue
    REQUIRE(coasting[3] >
            drogue[3]);  // y_vel while coasting > y_vel during drogue

    ppp.process(100);
    stateType drogue2 = ppp.getCurrentConditions();

    REQUIRE(drogue[2] > drogue2[2]);  // 110 seconds after drogue, rocket should
                                      // be closer to the ground
    REQUIRE(abs(drogue[3]) >
            abs(drogue2[3]));  // 110 seconds after drogue, rocket should be
                               // slower than 10 seconds after drogue

    ppp.process(0.01);
    stateType drogue3 = ppp.getCurrentConditions();

    REQUIRE(drogue2[2] >
            drogue3[2]);  // 110.01 seconds after drogue, rocket should be
                          // closer to the ground than 110 seconds after drogue
    REQUIRE(abs(drogue2[3]) >
            abs(drogue3[3]));  // 110.01 seconds after drogue, rocket should be
                               // slower than 110 seconds after drogue
}
// (10.0)
TEST_CASE("Testing Maximum Deployment Speed for Drogue")
{
    PhoenixPositionProvider ppp{};
    ppp.ignite();
    ppp.process(16.48);
    ppp.process(10);  // 10 seconds after engine cutoff, velocity should be too
                      // great for drogue deployment
    REQUIRE_THROWS_AS(ppp.drogue(), std::runtime_error);

    // do not need to test for Main Chute Deployment Speed
    // Drogue MUST be deployed before Main can be deployed
    // if speed is too fast, then Drogue will not deploy anyways
    // drogue and main have the same max deployment speed
}

// (11.0)
TEST_CASE("Testing Deployment Order")
{
    // ignition must happen before drogue
    PhoenixPositionProvider ppp1{};
    REQUIRE_THROWS_AS(ppp1.drogue(), std::runtime_error);

    // ignition must happen before main chute
    PhoenixPositionProvider ppp2{};
    REQUIRE_THROWS_AS(ppp2.chute(), std::runtime_error);

    // drogue must happen before main chute
    PhoenixPositionProvider ppp3{};
    ppp3.ignite();
    REQUIRE_THROWS_AS(ppp3.chute(), std::runtime_error);
}

/**
 * LinearInterpolatePropulsion.cpp Testing
 */

// (12.0)
//checks that the csv correctly is output and has the right values
TEST_CASE(){
    //checks if the function exits successfully
    double stepSize = 0.1;
    int test = start_csv(stepSize);
    REQUIRE(test == 0);
    std::string filename = "discrete_data_" + std::to_string(stepSize) +".csv";
    std::ifstream file(filename);
    //checks if file is open
    REQUIRE(file.is_open() == true);
    
    //checks that each line has the right number of values and correct step size
    std::string line;
    double step = 0;
    while (std::getline(file, line)) {
        std::vector<double> row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            row.push_back(stod(cell));
        }
        REQUIRE(row[0] == Catch::Approx(step));
        REQUIRE(row.size() == Catch::Approx(3));
        step += stepSize;
    }
    file.close();
}
    
// (13.0)
//checks the math behind the interpolation function
TEST_CASE("Testing interpolate function") {
    REQUIRE(interpolate(0.0, 10.0, 0.0) == Catch::Approx(0.0));
    REQUIRE(interpolate(0.0, 10.0, 1.0) == Catch::Approx(10.0));
    REQUIRE(interpolate(0.0, 10.0, 0.5) == Catch::Approx(5.0));
    REQUIRE(interpolate(-5.0, 5.0, 0.5) == Catch::Approx(0.0));
    REQUIRE(interpolate(2.0, 8.0, 0.25) == Catch::Approx(3.5));
}

// (14.0)
//Tests the math behind the linearInterpolate function
TEST_CASE("Testing linearInterpolate function") {
    std::vector<double> start = {0.0, 1.0, 100.0};
    std::vector<double> end = {10.0, 3.0, 200.0};
    
    std::vector<double> result = linearInterpolate(start, end, 5.0);
    
    REQUIRE(result[0] == Catch::Approx(5.0));
    REQUIRE(result[1] == Catch::Approx(2.0));
    REQUIRE(result[2] == Catch::Approx(150.0)); 
    
    result = linearInterpolate(start, end, 0.0);
    REQUIRE(result[1] == Catch::Approx(1.0));
    REQUIRE(result[2] == Catch::Approx(100.0));
    
    result = linearInterpolate(start, end, 10.0);
    REQUIRE(result[1] == Catch::Approx(3.0));
    REQUIRE(result[2] == Catch::Approx(200.0));
}

// ------------------------------
// Tests for addNoise function
// ------------------------------
// (15.0)
TEST_CASE("addNoise returns original value when noise factor is zero", "[Physics]") {
    double value = 10.0;
    double noiseFactor = 0.0;
    double result = Physics::addNoise(value, noiseFactor);
    // With zero noise factor, the value should remain unchanged.
    REQUIRE(result == Catch::Approx(value));
}

// (16.0)
TEST_CASE("addNoise with value zero always returns zero", "[Physics]") {
    double value = 0.0;
    double noiseFactor = 0.1;
    double result = Physics::addNoise(value, noiseFactor);
    REQUIRE(result == Catch::Approx(0.0));
}

// (17.0)
TEST_CASE("addNoise returns value within relative bounds", "[Physics]") {
    double value = 20.0;
    double noiseFactor = 0.1;
    double result = Physics::addNoise(value, noiseFactor);
    // the formula is: result = value + (value * noiseFactor * noise)
    // with noise in [-1,1], so the minimum is value*(1 - noiseFactor)
    // and maximum is value*(1 + noiseFactor)
    double lowerBound = value * (1 - noiseFactor);
    double upperBound = value * (1 + noiseFactor);
    INFO("Result: " << result << ", Expected between " << lowerBound << " and " << upperBound);
    REQUIRE(result >= lowerBound);
    REQUIRE(result <= upperBound);
}

// ------------------------------
// Tests for updateState function
// ------------------------------
// (18.0)
TEST_CASE("updateState with zero dt returns same state", "[Physics]") {
    Physics::XY_State initState;
    initState.position = Vector3(1.0, 2.0, 3.0);
    initState.velocity = Vector3(4.0, 5.0, 6.0);
    
    double dt = 0.0;
    double sensorAcceleration = 10.0;
    double sensorAirDensity = 1.0;  // Not used in integration.
    
    Physics::XY_State newState = Physics::updateState(initState, dt, sensorAcceleration, sensorAirDensity);
    
    //with dt=0, both position and velocity should remain unchanged
    REQUIRE(newState.position.x == Catch::Approx(initState.position.x));
    REQUIRE(newState.position.y == Catch::Approx(initState.position.y));
    REQUIRE(newState.position.z == Catch::Approx(initState.position.z));
    
    REQUIRE(newState.velocity.x == Catch::Approx(initState.velocity.x));
    REQUIRE(newState.velocity.y == Catch::Approx(initState.velocity.y));
    REQUIRE(newState.velocity.z == Catch::Approx(initState.velocity.z));
}

// (19.0)
TEST_CASE("updateState updates vertical state within expected range", "[Physics]") {
    // starting from a zero state
    Physics::XY_State initState;
    initState.position = Vector3(0, 0, 0);
    initState.velocity = Vector3(0, 0, 0);
    
    double dt = 1.0;
    double sensorAcceleration = 10.0;  // m/s^2 from CSV.
    double sensorAirDensity = 1.0;       // not used.
    
    Physics::XY_State newState = Physics::updateState(initState, dt, sensorAcceleration, sensorAirDensity);
    
    // the update uses: newVelocity.y = 0 + (noisyAcceleration * dt)
    // where noisyAcceleration = sensorAcceleration * (1 + noiseFactor * noise)
    // with noiseFactor = 0.1 and noise in [-1,1], newVelocity.y should be between:
    double expected = sensorAcceleration * dt; // 10.0
    double lowerBound = expected * 0.9;          // 9.0
    double upperBound = expected * 1.1;          // 11.0
    
    INFO("newState.velocity.y: " << newState.velocity.y);
    REQUIRE(newState.velocity.y >= lowerBound);
    REQUIRE(newState.velocity.y <= upperBound);
    
    // since newState.position.y = 0 + newVelocity.y * dt, it should equal newState.velocity.y
    REQUIRE(newState.position.y == Catch::Approx(newState.velocity.y));
}

// (20.0)
TEST_CASE("updateState works with non-zero initial state", "[Physics]") {
    // set an initial state with non-zero position and velocity
    Physics::XY_State initState;
    initState.position = Vector3(5.0, 5.0, 5.0);
    initState.velocity = Vector3(1.0, 1.0, 1.0);
    
    double dt = 2.0;
    double sensorAcceleration = 8.0; 
    double sensorAirDensity = 1.0;
    
    Physics::XY_State newState = Physics::updateState(initState, dt, sensorAcceleration, sensorAirDensity);
    
    // calculate expected vertical velocity bounds:
    // newVelocity.y = initState.velocity.y + sensorAcceleration * dt * (1 + noiseFactor * noise)
    // with noiseFactor = 0.1, the increment should be between 8*2*0.9 and 8*2*1.1
    double lowerIncrement = sensorAcceleration * dt * 0.9; // 14.4
    double upperIncrement = sensorAcceleration * dt * 1.1; // 17.6
    double expectedInitial = initState.velocity.y;         // 1.0
    double newVelY = newState.velocity.y;
    
    INFO("newState.velocity.y: " << newVelY);
    REQUIRE(newVelY >= expectedInitial + lowerIncrement);
    REQUIRE(newVelY <= expectedInitial + upperIncrement);
    
    // newState.position.y should be initState.position.y + newState.velocity.y * dt
    double expectedPositionY = initState.position.y + newState.velocity.y * dt;
    REQUIRE(newState.position.y == Catch::Approx(expectedPositionY));
}