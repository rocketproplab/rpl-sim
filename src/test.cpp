#include <iostream>
#include "Eigen/Dense"
#include "boost_1_82_0/boost/numeric/odeint.hpp"
#include "PhoenixPositionProvider.cpp"

using namespace std;
using Eigen::Vector3d;


// (1.0) 
TEST_CASE("In pre flight stage", "Normal"){
	PhoenixPositionProvider ppp {};
	REQUIRE(ppp.rocketState == PhoenixPositionProvider::State::PRE_FLIGHT);
}

// (2.0) 
TEST_CASE("Ignite working normally", "Ignite"){
	PhoenixPositionProvider ppp {};
	REQUIRE_THROWS_AS(ppp.ignite(), std::runtime_error);
}

// (3.0) 


// (4.0) 

// (5.0) 

// (6.0) 

// (7.0) 

// (8.0) 

// (9.0) 

