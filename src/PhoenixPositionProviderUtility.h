#ifndef PHOENIX_POSITION_PROVIDER_UTILITY_H
#define PHOENIX_POSITION_PROVIDER_UTILITY_H
#include "boost_1_82_0/boost/numeric/odeint.hpp"
#include <cmath>
#include <vector>
#include<sstream>
#include <iostream>
#include<fstream>
using namespace std;



// CONSTANTS

const float g = 9.81; // m/s

// rocket body parameters
const float DryMass = 54.4218; //kg  (126 lbs)
const float FuelMass = 20.72917; //kg  (45.7 lbs)
const float Rocket_Diameter = 0.206756; //m  (8.14 in)
const float Rocket_Height = 4.64; //m (165 in)
const float Rocket_WindloadArea = Rocket_Diameter * Rocket_Height;
const float Rocket_Cross_Section_Area = 3.14159265358979323846 * pow(Rocket_Diameter / 2, 2);

// Drogue parameters
const float DrogueCd = 2.2;
const float Drogue_Diameter = 1.524;
const float Drogue_Area = 3.14159265358979323846 * pow(Drogue_Diameter / 2, 2);

// Main parachute parameters
const float MainCd = 2.2;
const float Main_Diameter = 4.8768;
const float Main_Area = 3.14159265358979323846 * pow(Main_Diameter / 2, 2);

// rocket fuel parameters
const float m_dot = 1.2579; // kg/s, mass flow rate of fuel
const float BurnTime = FuelMass / m_dot; // 13.4308 seconds
const double start_t = 0.0;
const double end_t = BurnTime;

// wind parameters
const float AvgWindSpeed = 10; // m/s, average speed of wind of FAR site


// FUNCTION DECLARATIONS

float mass(float t);
float TempWindLoad(float y);
float WindLoad(float y);
float Thrust(float y);
float RocketCd(float vy);
float RocketDrag(float y, float vy);
float DrogueDrag(float y, float vy);
float MainDrag(float y, float vy);
vector<vector<float>> parseFile(const string& filename);
float linearInterp(float x, vector<float> all_x, vector<float> all_y);
float AirDensityFromAltitude(float x);


typedef boost::array<double, 4> stateType;



void createDE1(const stateType& q, stateType& dqdt, const double t);
void createDE2(const stateType& q, stateType& dqdt, const double t);
void createDE3(const stateType& q, stateType& dqdt, const double t);
void createDE4(const stateType& q, stateType& dqdt, const double t);

#endif