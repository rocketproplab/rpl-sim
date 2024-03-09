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



// (6.0) 

// (7.0) 

// (8.0) 

// (9.0) 
