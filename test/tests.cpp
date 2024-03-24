#include <catch2/catch_test_macros.hpp>
#include "../src/PhoenixPositionProvider.h"

//(1.0) 
TEST_CASE("In pre-flight stage", "Pre-flight"){
	PhoenixPositionProvider ppp {};
	REQUIRE(ppp.rocketState == PhoenixPositionProvider::State::PRE_FLIGHT);
}

// (2.0) 
TEST_CASE("Ignite working normally", "Ignite"){
	PhoenixPositionProvider ppp {};
	ppp.ignite();
	REQUIRE( ppp.rocketState == PhoenixPositionProvider::State::BURN );
	REQUIRE( ppp.igniteCounter == 1 );
	// error if called twice
	REQUIRE_THROWS_AS(ppp.ignite(), std::runtime_error);
}

// (3.0) 
TEST_CASE("Drogue stage okay", "Drogue"){
	PhoenixPositionProvider ppp {};
	REQUIRE_THROWS_AS(ppp.drogue(), std::runtime_error);
	ppp.ignite();
	ppp.drogue();
	// error if called twice
	REQUIRE_THROWS_AS(ppp.drogue(), std::runtime_error);
	REQUIRE(ppp.rocketState == PhoenixPositionProvider::State::DROGUE);
}

// (4.0) 
TEST_CASE("Chute stage okay", "Chute"){
	PhoenixPositionProvider ppp {};
	REQUIRE_THROWS_AS(ppp.chute(), std::runtime_error);
	ppp.ignite();
	ppp.drogue();
	ppp.chute();
	// error if called twice
	REQUIRE_THROWS_AS(ppp.chute(), std::runtime_error);
	REQUIRE(ppp.rocketState == PhoenixPositionProvider::State::CHUTE);
}

// (5.0) 
TEST_CASE("Rocket State Transitions to BURN to COAST after Fuel Cutoff") {
    PhoenixPositionProvider ppp {};
    ppp.ignite();
    ppp.process(16.47);
    REQUIRE(ppp.rocketState == PhoenixPositionProvider::State::BURN);
    ppp.process(0.03);
    REQUIRE(ppp.rocketState == PhoenixPositionProvider::State::COAST);
}

// (6.0) 
TEST_CASE("Rocket State Will Remain BURN if currentTime is == BurnTime + IgnitionTime") {
    PhoenixPositionProvider ppp {};
    ppp.ignite();
    ppp.process(16.47);
    REQUIRE(ppp.rocketState == PhoenixPositionProvider::State::BURN);
    ppp.process(0.01);
    // currentTime is 16.48 at this point, which is == to BurnTime
    REQUIRE(ppp.rocketState == PhoenixPositionProvider::State::BURN);
    ppp.process(0.01);
    // after this, currentTime is 16.49, which should transition rocket to COAST 
    REQUIRE(ppp.rocketState == PhoenixPositionProvider::State::COAST);
}

// (7.0) 
TEST_CASE("Testing State Transition, but with ignitionTime != 0") {
    PhoenixPositionProvider ppp {};
    ppp.process(0.5);
    ppp.ignite();
    ppp.process(16.47);
    REQUIRE(ppp.rocketState == PhoenixPositionProvider::State::BURN);
    ppp.process(0.01);
    // currentTime is 16.48 at this point, which is == to BurnTime
    REQUIRE(ppp.rocketState == PhoenixPositionProvider::State::BURN);
    ppp.process(0.01);
    // after this, currentTime is 16.49, which should transition rocket to COAST 
    REQUIRE(ppp.rocketState == PhoenixPositionProvider::State::COAST);
}


// (8.0) 
TEST_CASE("Testing if y-vel decreases && y-pos increases in COAST stage") {
    PhoenixPositionProvider ppp {};
    ppp.process(0.5);
    ppp.ignite();
    ppp.process(16.48);
    stateType burning = ppp.getCurrentConditions();
    ppp.process(0.01);
    stateType coasting = ppp.getCurrentConditions();

    REQUIRE(burning[2] < coasting[2]); // y_pos while burn < y_pos during coast
    REQUIRE(burning[3] > coasting[3]); // y_vel while burn > y_vel during coast
}

// (9.0) 
TEST_CASE("Testing if y_pos/vel make sense in CHUTE stage") {
    PhoenixPositionProvider ppp {};
    ppp.ignite();
    ppp.process(16.48);
    ppp.process(30); // according to Yihong Sim, ~30 seconds into coasting is apogee
    ppp.drogue();
    stateType coasting = ppp.getCurrentConditions();
    ppp.process(10); // 10 seconds after that, rocket should definitely be coming down
    stateType drogue = ppp.getCurrentConditions();
    REQUIRE(coasting[2] > drogue[2]); // y_pos while coasting > y_pos during drogue
    REQUIRE(coasting[3] > drogue[3]); // y_vel while coasting > y_vel during drogue

    ppp.process(100); 
    stateType drogue2 = ppp.getCurrentConditions();

    REQUIRE(drogue[2] > drogue2[2]); // 110 seconds after drogue, rocket should be closer to the ground
    REQUIRE(abs(drogue[3]) > abs(drogue2[3])); // 110 seconds after drogue, rocket should be slower than 10 seconds after drogue

    ppp.process(0.01); 
    stateType drogue3 = ppp.getCurrentConditions();

    REQUIRE(drogue2[2] > drogue3[2]); // 110.01 seconds after drogue, rocket should be closer to the ground than 110 seconds after drogue
    REQUIRE(abs(drogue2[3]) > abs(drogue3[3])); // 110.01 seconds after drogue, rocket should be slower than 110 seconds after drogue
}
// (10.0)
TEST_CASE("Testing Maximum Deployment Speed for Drogue") {
    PhoenixPositionProvider ppp {};
    ppp.ignite();
    ppp.process(16.48);
    ppp.process(10); // 10 seconds after engine cutoff, velocity should be too great for drogue deployment
    REQUIRE_THROWS_AS(ppp.drogue(), std::runtime_error);

    // do not need to test for Main Chute Deployment Speed
    // Drogue MUST be deployed before Main can be deployed
    // if speed is too fast, then Drogue will not deploy anyways
    // drogue and main have the same max deployment speed
}

// (11.0)
TEST_CASE("Testing Deployment Order") {

    // ignition must happen before drogue
    PhoenixPositionProvider ppp1 {};
    REQUIRE_THROWS_AS(ppp1.drogue(), std::runtime_error);

    // ignition must happen before main chute
    PhoenixPositionProvider ppp2 {};
    REQUIRE_THROWS_AS(ppp2.chute(), std::runtime_error);

    // drogue must happen before main chute
    PhoenixPositionProvider ppp3 {};
    ppp3.ignite();
    REQUIRE_THROWS_AS(ppp3.chute(), std::runtime_error);

}

// (12.0)
TEST_CASE("Testing setRocketParameter") {

    // ignition must happen before drogue
    PhoenixPositionProvider ppp1 {};
    ppp1.ignite();
    ppp1.process(10);
    stateType ppp1_conditions = ppp1.getCurrentConditions();
    double ppp1_time = ppp1.currentTime;
    PhoenixPositionProvider::State ppp1_state = ppp1.getStatus();
    ppp1.process(20);
    stateType ppp1_final_conditions = ppp1.getCurrentConditions();

    // initializing ppp2 to be same state as ppp1 after 10 seconds
    PhoenixPositionProvider ppp2 {};
    ppp2.setRocketParameters(
        ppp1_conditions[0], ppp1_conditions[1],
        ppp1_conditions[2], ppp1_conditions[3],
        ppp1_conditions[4], ppp1_conditions[5],
        ppp1_state, ppp1_time
    );

    ppp2.process(20);

    REQUIRE(ppp1.getStatus() == ppp2.getStatus());
    REQUIRE(ppp1.currentTime == ppp2.currentTime);

    // it seems like there is some randomness in what values ODE comes up with between runs,
    // sanity check only checks up to the 1000th place, since that seems like good enough precision
    for (int i = 0; i < 6; i++) {
        int x = int(ppp1.getCurrentConditions()[i] * 100);
        int y = int(ppp2.getCurrentConditions()[i] * 100);
        REQUIRE(x == y);
    }

}

// (13.0)
TEST_CASE("General Sanity Checks of setRocketParameters() Function") {
    PhoenixPositionProvider ppp1 {};
    ppp1.setRocketParameters(0, 0, 0, 0, 0, 0, PhoenixPositionProvider::State::BURN, 0);
    REQUIRE_THROWS_AS(ppp1.chute(), std::runtime_error); // chute cannot be called before drogue
    
    PhoenixPositionProvider ppp2 {};
    ppp2.setRocketParameters(0, 0, 0, 0, 0, 0, PhoenixPositionProvider::State::BURN, 0);
    REQUIRE_THROWS_AS(ppp1.ignite(), std::runtime_error); // ignite cannot be called twice

    PhoenixPositionProvider ppp3 {};
    ppp3.setRocketParameters(0, 0, 0, 0, 0, 0, PhoenixPositionProvider::State::DROGUE, 0);
    REQUIRE_THROWS_AS(ppp3.drogue(), std::runtime_error); // drogue cannot be called twice

    PhoenixPositionProvider ppp4 {};
    ppp4.setRocketParameters(0, 0, 0, 0, 0, 0, PhoenixPositionProvider::State::CHUTE, 0);
    REQUIRE_THROWS_AS(ppp4.chute(), std::runtime_error); // chute cannot be called twice

    PhoenixPositionProvider ppp5 {};
    ppp5.setRocketParameters(0, 0, 0, -100, 0, 0, PhoenixPositionProvider::State::COAST, 0);
    REQUIRE_THROWS_AS(ppp5.drogue(), std::runtime_error); // velocity is too high for drogue to be called
}

// // (final boss) (takes around 3-4 minutes)
// TEST_CASE("Doing a whole run") {
//     PhoenixPositionProvider ppp {};
//     ppp.ignite();
//     ppp.process(16.48);
//     stateType burning = ppp.getCurrentConditions();
//     ppp.process(30);
//     stateType coasting = ppp.getCurrentConditions();
//     ppp.drogue();
//     ppp.process(400);
//     ppp.chute();
//     ppp.process(180); 
// }