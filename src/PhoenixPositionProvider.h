#ifndef PHOENIX_POSITION_PROVIDER_H
#define PHOENIX_POSITION_PROVIDER_H
#include <time.h> // for seeind rand
#include <stdlib.h> // for rand
#include "PhoenixPositionProviderUtility.h"


using namespace boost::numeric::odeint;


/*
process(long simTime, long deltaTime): This function is 
called once per simulation step.Use this function to update
 the internal position/rotation state.
*/
class PhoenixPositionProvider{
    private:
        const double dt = 0.01; // must be a double for odeint to work

        // x, y, z position
        double currCoords[3] = {0, 0, 0};
        int previousRotState;
        int updatedRotState;
        int igniteCounter;
        int destroyed;
        runge_kutta4<stateType> stepper;
        stateType initialConditions;


    public:
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
        double currentTime;
        State rocketState;
        vector<double> times;
        vector<stateType> allPositions;
};

#endif