#ifndef ROCKET_FLIGHT_PROPERTIES_H
#define ROCKET_FLIGHT_PROPERTIES_H

class RocketFlightProperties
{
    private:

        // rocket body parameters
        const double _dryMass = 54.4218; //kg  (126 lbs)
        const double _fuelMass = 20.72917; //kg  (45.7 lbs)
        const double _rocketDiameter = 0.206756; //m  (8.14 in)
        const double _rocketHeight = 4.64; //m (165 in)
        const double _rocketWindloadArea = 0;
        const double _rocketCrossSectionArea = 0;

        // Drogue parameters
        const double _drogueCd = 2.2;
        const double _drogueDiameter = 1.524;
        const double _drogueArea = 0;

        // Main parachute parameters
        const double _mainCd = 2.2;
        const double _mainDiameter = 4.8768;
        const double _mainArea = PI * pow(Main_Diameter / 2, 2);

        // rocket fuel parameters
        const double _m_dot = 1.2579; // kg/s, mass flow rate of fuel
        const double _burnTime = 16.48; //FuelMass / m_dot ~= 16.479 seconds, rounded to make math cleaner

        // wind parameters
        const double _avgWindSpeed = 10; // m/s, average speed of wind of FAR site

        // Wind Load
        std::vector<double> _windLoadX;
        std::vector<double> _windLoadY;

        // Atmospheric Data
        std::vector<double> _temperatureData;
        std::vector<double> _speedOfSoundData;
        std::vector<double> _pressureData;
        std::vector<double> _rhoData;

        // Other Data
        std::vector<double> _altitudeData;
        std::vector<double> _machNumData;
        std::vector<double> _dragCoeffData;
        std::vector<double> _heightData;
        std::vector<double> _thrustData;

        // Helper functions
        airDensityFromAltitude(double x);

    public:
        RocketFlightProperties();

        double calcMass(double t); // ✔

        double calcWindLoadX(double y); //
        double calcWindLoadZ(double y); //

        double calcRocketCoefficientOfDrag(double vy); // ✔
        double calcRocketDrag(double y, double vy);    // ✔
        double calcDrogueDrag(double y, double vy);    // ✔
        double calcMainDrag(double y, double vy);      // ✔

        double calcThrust(double y);                   // ✔
}

#endif /* ROCKET_FLIGHT_PROPERTIES_H */