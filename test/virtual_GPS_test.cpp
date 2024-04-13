#include <catch2/catch_test_macros.hpp>
#include "../src/virtual_GPS.hpp"

//(1.0) 
TEST_CASE("virtual GPS Test", "(0,0,0), rate 1, err 1m, seed 1"){

	virtual_GPS GPS(0,0,0,1,20,1)
	REQUIRE(GPS.process((1,1,1),0.1));

}