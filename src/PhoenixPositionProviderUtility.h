#ifndef PHOENIX_POSITION_PROVIDER_UTILITY_H
#define PHOENIX_POSITION_PROVIDER_UTILITY_H
#include <boost/numeric/odeint.hpp>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "spline.h"

#define PI boost::math::constants::pi<double>()

// CONSTANTS

const float g = 9.81;  // m/s

// rocket body parameters
const float DryMass = 54.4218;           // kg  (126 lbs)
const float FuelMass = 20.72917;         // kg  (45.7 lbs)
const float Rocket_Diameter = 0.206756;  // m  (8.14 in)
const float Rocket_Height = 4.64;        // m (165 in)
const float Rocket_WindloadArea = Rocket_Diameter * Rocket_Height;
const float Rocket_Cross_Section_Area = PI * pow(Rocket_Diameter / 2, 2);

// Drogue parameters
const float DrogueCd = 2.2;
const float Drogue_Diameter = 1.524;
const float Drogue_Area = PI * pow(Drogue_Diameter / 2, 2);

// Main parachute parameters
const float MainCd = 2.2;
const float Main_Diameter = 4.8768;
const float Main_Area = PI * pow(Main_Diameter / 2, 2);

// rocket fuel parameters
const float m_dot = 1.2579;  // kg/s, mass flow rate of fuel
const double burnTime =
    16.48;  // FuelMass / m_dot ~= 16.479 seconds, rounded to make math cleaner

// wind parameters
const float AvgWindSpeed = 10;  // m/s, average speed of wind of FAR site

// FUNCTION DECLARATIONS

float mass(float t);
float TempWindLoad(float y);
std::vector<float> GenerateWindLoadData();
float WindLoad_x(float y);
float WindLoad_z(float y);
float Thrust(float y);
float RocketCd(float vy);
float RocketDrag(float y, float vy);
float DrogueDrag(float y, float vy);
float MainDrag(float y, float vy);
std::vector<std::vector<float>> parseFile(const std::string &filename);
std::vector<float> getAltitudes();
float linearInterp(float x, std::vector<float> all_x, std::vector<float> all_y);
float splineInterp(float x, std::vector<float> all_x, std::vector<float> all_y);
float AirDensityFromAltitude(float x);

typedef boost::array<double, 6> stateType;

void createDE1(const stateType &q, stateType &dqdt, const double t);
void createDE2(const stateType &q, stateType &dqdt, const double t);
void createDE3(const stateType &q, stateType &dqdt, const double t);
void createDE4(const stateType &q, stateType &dqdt, const double t);

struct push_back_state_and_time {
    std::vector<stateType> &m_states;
    std::vector<double> &m_times;

    push_back_state_and_time(std::vector<stateType> &states,
                             std::vector<double> &times);
    void operator()(const stateType &x, double t);
};

#endif