#include "catch2/catch_test_macros.hpp"
#include "../src/fluid_engine_sim/FluidToEngineSubsystem.cpp"

// Checking to see default construtor sets status appropriately
TEST_CASE("WAITING FOR LAUNCH COMMAND", "NORMAL") {
	FluidToEngineSubsystem fs {};
	REQUIRE( fs.getStatus() == FluidToEngineStatus::WAITING_FOR_LAUNCH_COMMAND);
}

// Status set incorrectly, solenoids weren't opened
TEST_CASE("Ignite Bad Status", "Unexpected Status: WAITING FOR LAUNCH COMMAND") {
	FluidToEngineSubsystem fs {};
	REQUIRE_THROWS_AS(fs.ignite(), std::runtime_error);
}

// Status set correctly, solenoids weren't opened
TEST_CASE("Ignite Closed Solenoids", "CLOSED SOLENIDS") {
	FluidToEngineSubsystem fs {};
	fs.setStatus(FluidToEngineStatus::SOLENOIDS_OPEN_FUEL_FLOWING);
	REQUIRE_THROWS_AS(fs.ignite(), std::runtime_error);
}

TEST_CASE("Process Loop Run Normal", "Normal") {
	FluidToEngineSubsystem fs {};
	double solenoid_timer {0.0};
	double target {300.0};
	while (solenoid_timer < 201) {
		REQUIRE_NOTHROW([&](){ // C++ anonymous function
			if (solenoid_timer == 200) {
				fs.ignite();
			}else {
				fs.process(solenoid_timer, target);
			}
		}()); // make sure to actually call lambda function immediately lolz
		solenoid_timer++;
	}
	while (solenoid_timer < target) {
		REQUIRE(fs.getStatus() == FluidToEngineStatus::ENGINE_RUNNING);
		REQUIRE(fs.getSolenoidState(Solenoid::LNG_solenoid) == true);
		REQUIRE(fs.getSolenoidState(Solenoid::LOX_solenoid) == true);

		solenoid_timer++;
	}
}

TEST_CASE("Process Loop Run Bad Engine", "Engine never ignites") {
	FluidToEngineSubsystem fs {};
	double solenoid_timer {301.0};
	double target {300.0};
	CHECK_THROWS_AS(fs.process(solenoid_timer, target), std::runtime_error);
}

TEST_CASE("Process Loop Run Explode", "Engine explodes cuz someone closed solenoid while it was running") {
	FluidToEngineSubsystem fs {};
	double solenoid_timer {0.0};
	double target {300.0};
	fs.process(solenoid_timer, target);
	fs.ignite();
	fs.setSolenoidState(Solenoid::LNG_solenoid, false);
	CHECK_THROWS_AS(fs.process(solenoid_timer, target), std::runtime_error);
}
