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
    // ASSUMES FILES EXIST
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

    this->_altitudeData = initAltitudesVector();
}

double airDensityFromAltitude(double x)
{
    return linearInterp(x, this->_altitudeData, this->_rhoData);
}

double RocketFlightProperties::calcMass(double t)
{
    return this->_dryMass + this->_fuelMass - this->_m_dot*t;
}

double RocketFlightProperties::calcWindLoadX(double y)
{
    double a = linearInterp(y, this->_altitudes);
    return a;
}
double RocketFlightProperties::calcWindLoadZ(double y)
{
    double a = linearInterp(y, this->_altitudes);
    return a;
}

double RocketFlightProperties::calcRocketCoefficientOfDrag(double vy)
{
    return linearInterp(vy, this->_machNumData, this->_dragCoeffData);
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
double RocketFlightProperties::calcRocketCoefficientDrag(double vy)
{

}