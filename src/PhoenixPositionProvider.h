#ifndef PHOENIX_POSITION_PROVIDER_H
#define PHOENIX_POSITION_PROVIDER_H
#include <time.h> // for seeind rand
#include <stdlib.h> // for rand
#include "PhoenixPositionProviderUtility.h"


using namespace boost::numeric::odeint;


const float drogueMaxDeploymentSpeed = 1000; // units *should be* m/s, ask recovery people about this
const float chuteMaxDeploymentSpeed = 1000; // and this


class PhoenixPositionProvider{
    private:
        const double dt = 0.01; // must be a double for odeint to work

        // x, y, z position
        double currCoords[3] = {0, 0, 0};
        int previousRotState;
        int updatedRotState;
        int chuteCounter;
        int drogueCounter;
        int destroyed;
        runge_kutta4<stateType> stepper;
        stateType currentConditions;

    public:
        int igniteCounter;
        
        enum class State {
            PRE_FLIGHT,
            BURN,
            COAST,
            DROGUE,
            CHUTE
        };

        PhoenixPositionProvider();
        void process(double simTime, double deltaTime);
        double* getPosition();
        void ignite();
        void chute();
        void drogue();
        double currentTime;
        State rocketState;
        vector<double> times;
        vector<stateType> allPositions;
        State getStatus();
};

#endif