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
		REQUIRE(fs.process(solenoid_timer, target), )
		solenoid_timer++;
	}
}


