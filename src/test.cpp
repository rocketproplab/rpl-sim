#include "Catch2-devel/src/catch2/catch_test_macros.hpp"
#include <FluidToEngineSubsystem.h>

// Checking to see default construtor sets status appropriately
TEST_CASE("WAITING FOR LAUNCH COMMAND", "NORMAL") {
	FluidToEngineSubsystem fs {};
	REQUIRE( fs.getStatus() == FluidToEngineStatus::WAITING_FOR_LAUNCH_COMMAND)
}

// Status set incorrectly, solenoids weren't opened
TEST_CASE("IGNITE", "Unexpected Status: WAITING FOR LAUNCH COMMAND") {
	FluidToEngineSubsystem fs {};
	REQUIRE_THROWS_AS(fs.ignite(), std::runtime_error);
}

// Status set correctly, solenoids weren't opened
TEST_CASE("IGNITE", "CLOSED SOLENIDS") {
	FluidToEngineSubsystem fs {};
	fs.setStatus(FluidToEngineStatus::SOLENOIDS_OPEN_FUEL_FLOWING);
	REQUIRE_THROWS_AS(fs.ignite(), std::runtime_error);
}

TEST_CASE("Process Loop Run", "Normal") {
	FluidToEngineSubsystem fs {};
	double solenoid_timer {0.0};
	double target {300.0};
	while (true) {
		REQUIRE_NOTHROW([&](){ // C++ anonymous function
			fs.process(solenoid_timer, target);
			solenoid_timer++;
			if (solenoid_timer == 200.0) fs.ignite();
		})
	}
}

TEST_CASE("Process Loop Run", "Engine never ignites") {
	FluidToEngineSubsystem fs {};
	double solenoid_timer {0.0};
	double target {300.0};
	while (true) {
		CHECK_THROWS_AS(fs.process(solenoid_timer, target), std::runtime_error)
		solenoid_timer++;
	}
}

TEST_CASE("Process Loop Run", "Engine explodes cuz someone closed solenoid while it was running") {
	FluidToEngineSubsystem fs {};
	double solenoid_timer {0.0};
	double target {300.0};
	while (true) {
		REQUIRE_NOTHROW([&](){ // C++ anonymous function
			fs.process(solenoid_timer, target);
			solenoid_timer++;
			if (solenoid_timer == 200.0) fs.ignite();
		})
	}

	fs.setSolenoidState(Solenoid::LNG_solenoid, false)
	CHECK_THROWS_AS(fs.process(), std::runtime_error)
}
