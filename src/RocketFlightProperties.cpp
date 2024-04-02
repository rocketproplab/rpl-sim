#include "RocketFlightPropertiesUtils.hpp"

#include "math.h"

#define PI boost::math::constants::pi<double>()

RocketFlightProperties::RocketFlightProperties(
    
    // Rocket params
    const double dryMass,
    const double fuelMass,
    const double rocketDiameter,
    const double rocketHeight,

    // Drogue Chute Params
    const double drogueCd,
    const double drogueDiameter,

    // Main Parachute Params
    const double mainCd,
    const double mainDiameter,

    // Fuel parameters
    const double m_dot,
    const double burnTime,

    // Wind parameters
    const double avgWindSpeed,

    // Data Curve Paths
    const std::string atmosphereIsaPath,
    const std::string machDragDataPath,
    const std::string thrustCurvePath
)
{

    // MAIN PARAMS

    // Rocket Params
    this->_dryMass = dryMass;
    this->_fuelMass = fuelMass;
    this->_rocketDiameter = rocketDiameter;
    this->_rocketHeight = rocketHeight;
    this->_rocketWindloadArea = rocketDiameter * rocketHeight;
    this->_rocketCrossSectionArea = PI * (rocketDiameter / 2.0) * (rocketDiameter / 2.0);

    // Drogue Params
    this->_drogueCd = drogueCd;
    this->_drogueDiameter = drogueDiameter;
    this->_drogueArea = PI * (drogueDiameter / 2.0) * (drogueDiameter / 2.0);

    // Main Chute Params
    this->_mainCd = mainCd;
    this->_mainDiameter = mainDiameter;
    this->_mainArea = PI * (mainDiameter / 2.0) * (mainDiameter / 2.0);

    // Rocket Fuel Parameters
    this->_m_dot = m_dot;
    this->_burnTime = burnTime;

    // Wind parameters
    this->_avgWindSpeed = avgWindSpeed;

    // DATA CURVES
    this->_altitudeData = initAltitudesVector();

    // Assume below files exist.
    std::vector<std::vector<double>> atmosData = parseFile(atmosphereIsaPath);
    this->_temperatureData = atmosData[0];
    this->_speedOfSoundData = atmosData[1];
    this->_pressureData = atmosData[2];
    this->_rhoData = atmosData[3];

    std::vector<std::vector<double>> machDragData = parseFile(machDragDataPath);
    this->_machNum = convertToMs(machDragData[0]); // TODO convertToMs()
    this->_dragCoeffData = machDragData[1];

    std::vector<std::vector<double>> thrustCurve = parseFile(thrustCurvePath);
    this->_heightData = thrustCurve[0];
    this->_thrustData = thrustCurve[1];

    this->_windLoadX = this->generateWindLoadData();
    this->_windLoadZ = this->generateWindLoadData();
}

double airDensityFromAltitude(double x)
{
    return linearInterp(x, this->_altitudeData, this->_rhoData);
}




double RocketFlightProperties::calcMass(double t)
{
    return this->_dryMass + this->_fuelMass - this->_m_dot*t;
}
double RocketFlightProperties::calcRocketCoefficientOfDrag(double vy)
{
    return linearInterp(vy, this->_machNumData, this->_dragCoeffData);
}




// WIND STUFF

double RocketFlightProperties::tempWindLoad(double y)
{
    // TODO: Check this... seems like it isn't going to be smooth.
    // Consider Perlin Noise? I think that is what prop team did
    int windOffset = (rand() % 7) - 3; // force range to [-3, 3]
    return 0.5 * this->airDensityFromAltitude(y) * (this._avgWindSpeed + windOffset)*(this._avgWindSpeed + windOffset) * this._rocketWindloadArea;
}

std::vector<double> RocketFlightProperties::generateWindLoadData()
{
    std::vector<double> windloads;

    for (int alt = 0; alt < 10001; alt++) {
        double offset = -1 + 2 * (rand() / static_cast<double>(RAND_MAX));
        // cout << offset * TempWindLoad(alt) << endl;
        windloads.push_back(offset * this->tempWindLoad(alt));
    }

    return windloads;
}

double RocketFlightProperties::calcWindLoadX(double y)
{
    double a = linearInterp(y, this->_altitudes, this->_windLoadX);
    return a;
}
double RocketFlightProperties::calcWindLoadZ(double y)
{
    double a = linearInterp(y, this->_altitudes, this->_windLoadZ);
    return a;
}

double RocketFlightProperties::calcRocketDrag(double y, double vy)
{
    return 0.5 * AirDensityFromAltitude(y) * (vy*vy) * this->calcRocketCoefficientOfDrag(vy) * this->_rocketCrossSectionArea;
}
double RocketFlightProperties::calcDrogueDrag(double y, double vy)
{
    return 0.5 * this->airDensityFromAltitude(y) * (vy*vy) * this->_drogueCd * this._drogueArea;
}
double RocketFlightProperties::calcMainDrag(double y, double vy)
{
    return 0.5 * this->airDensityFromAltitude(y) * (vy*vy) * this->_mainCd * this->_mainArea;
}

double RocketFlightProperties::calcThrust(double y)
{
    return linearInterp(y, this->_heightData, this->_thrustData);
}


void RocketFlightProperties::createDE1(const stateType& q, stateType& dqdt, const double t) {
    // cout << "Stage 1: Lift off, Engine in operation..." << endl;
    dqdt[0] = q[1];
    dqdt[1] = 1.0 / mass(t) * WindLoad_x(q[2]);
    dqdt[2] = q[3];
    dqdt[3] = 1.0 / mass(t) * (Thrust(q[2]) - mass(t) * g - RocketDrag(q[2], q[3]));
    dqdt[4] = q[5];
    dqdt[5] = 1.0 / mass(t) * WindLoad_z(q[2]);
}

//
void RocketFlightProperties::createDE2(const stateType& q, stateType& dqdt, const double t) {
    //cout << "Stage 2: Engine turns off, continuing upward..." << endl;
    dqdt[0] = q[1];
    dqdt[1] = 1.0 / DryMass * WindLoad_x(q[2]);
    dqdt[2] = q[3];
    dqdt[3] = 1.0 / DryMass * (-DryMass * g - RocketDrag(q[2], q[3]));
    dqdt[4] = q[5];
    dqdt[5] = 1.0 / DryMass * WindLoad_z(q[2]);
}

void RocketFlightProperties::createDE3(const stateType& q, stateType& dqdt, const double t) {
    //cout << "Stage 3: Drogue parachute deploys at Apogee..." << endl;
    dqdt[0] = q[1];
    dqdt[1] = 1.0 / DryMass * WindLoad_x(q[2]);
    dqdt[2] = q[3];
    dqdt[3] = 1.0 / DryMass * (RocketDrag(q[2], abs(q[3])) + DrogueDrag(q[2], abs(q[3])) - DryMass*g);
    dqdt[4] = q[5];
    dqdt[5] = 1.0 / DryMass * WindLoad_z(q[2]);
}

void RocketFlightProperties::createDE4(const stateType& q, stateType& dqdt, const double t) {
    //cout << "Stage 4: Main parachute deploys..." <<endl;
    dqdt[0] = q[1];
    dqdt[1] = 1.0 / DryMass * WindLoad_x(q[2]);
    dqdt[2] = q[3];
    dqdt[3] = 1.0 / DryMass * (RocketDrag(q[2], abs(q[3])) + MainDrag(q[2], abs(q[3])) - DryMass*g);
    dqdt[4] = q[5];
    dqdt[5] = 1.0 / DryMass * WindLoad_z(q[2]);
}

push_back_state_and_time::push_back_state_and_time(vector<stateType>& states, vector<double>& times)
    : m_states(states), m_times(times) {}


void push_back_state_and_time::operator()(const stateType& x, double t)
{
    m_states.push_back(x);
    m_times.push_back(t);
}