# pragma once
#ifndef PHOENIX_POSITION_PROVIDER_UTILITY_H
#define PHOENIX_POSITION_PROVIDER_UTILITY_H
#include "boost_1_82_0/boost/numeric/odeint.hpp"
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;


// CONSTANTS

const float g = 9.81; // m/s

// rocket body parameters
const float DryMass = 54.4218; //kg  (126 lbs)
const float FuelMass = 20.72917; //kg  (45.7 lbs)
const float Rocket_Diameter = 0.206756; //m  (8.14 in)
const float Rocket_Height = 4.64; //m (165 in)
const float Rocket_WindloadArea = Rocket_Diameter * Rocket_Height;

// rocket fuel parameters
const float m_dot = 1.2579; // kg/s, mass flow rate of fuel
const float BurnTime = FuelMass / m_dot; // 13.4308 seconds
const double start_t = 0.0;
const double end_t = BurnTime;

// wind parameters
const float AvgWindSpeed = 10; // m/s, average speed of wind of FAR site

const float rho = 0.7637; // using air density as a constant for now

// FUNCTION DECLARATIONS

float mass(float t);
float WindLoad(float y);
float Thrust(float y);
float RocketCd(float vy);
float RocketDrag(float y, float vy);
float DrogueDrag(float y, float vy);
float MainDrag(float y, float vy);

typedef boost::array<double, 4> stateType;



void createDE1(const stateType& q, stateType& dqdt, const double t);
void createDE2(const stateType& q, stateType& dqdt, const double t);
void createDE3(const stateType& q, stateType& dqdt, const double t);
void createDE4(const stateType& q, stateType& dqdt, const double t);

#endif