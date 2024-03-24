#ifndef PHOENIX_POSITION_PROVIDER_H
#define PHOENIX_POSITION_PROVIDER_H
#include <time.h> // for seeind rand
#include <stdlib.h> // for rand
#include "PhoenixPositionProviderUtility.h"


using namespace boost::numeric::odeint;

// asked recovery, they said 100ft/s (seems kinda slow but ig)
const float drogueMaxDeploymentSpeed = 30.48; // m/s, ask recovery people about this
const float chuteMaxDeploymentSpeed = 30.48; // and this


class PhoenixPositionProvider{
    private:
        const double dt = 0.01; // must be a double for odeint to work

        // x, y, z position
        double currCoords[3] = {0, 0, 0};
        int chuteCounter;
        int drogueCounter;
        double ignitionTime;
        runge_kutta4<stateType> stepper;
        stateType currentConditions;

    public:
        
        enum class State {
            PRE_FLIGHT,
            BURN,
            COAST,
            DROGUE,
            CHUTE
        };

        PhoenixPositionProvider();
        int igniteCounter;
        State rocketState;
        vector<double> times;
        vector<stateType> allPositions;
        void process(double deltaTime);
        double* getPosition();
        void ignite();
        void drogue();
        void chute();
        double currentTime;
        State getStatus();
        stateType getCurrentConditions();
        void setRocketParameters(float x_pos, float x_vel, float y_pos, float y_vel, float z_pos, float z_vel, State state, double time);
        void readOut();
};

#endif