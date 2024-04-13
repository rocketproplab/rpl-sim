#ifndef PHOENIX_POSITION_PROVIDER_H
#define PHOENIX_POSITION_PROVIDER_H
#include <time.h> // for seeind rand
#include <stdlib.h> // for rand
#include "PhoenixPositionProviderUtility.h"
#include "Vector3.hpp"

using namespace boost::numeric::odeint;

// asked recovery, they said 100ft/s (seems kinda slow but ig)
const float drogueMaxDeploymentSpeed = 30.48; // m/s, ask recovery people about this
const float chuteMaxDeploymentSpeed = 30.48; // and this


class PhoenixPositionProvider
{
    public:
        enum class State {
            PRE_FLIGHT,
            BURN,
            COAST,
            DROGUE,
            CHUTE
        };

    private:
        const double dt = 0.01; // must be a double for odeint to work

        // x, y, z position
        Vector3 position;
        
        double ignitionTime;
        runge_kutta4<stateType> stepper;
        stateType currentConditions;
        std::vector<stateType> allPositions;
        std::vector<double> times;
        double currentTime;
        State rocketState;
        
        bool didIgniteFlag;
        bool didChuteFlag;
        bool didDrogueFlag;

    public:
        
        PhoenixPositionProvider();

        void process(double deltaTime);
        Vector3 getPosition();
        void ignite();
        void drogue();
        void chute();

        bool didIgnite(); // Returns true if ignite() was called once, false otherwise.
                          // Pretty much used only for testing.
        bool didChute();
        bool didDrogue();

        State getFlightState();
        stateType getCurrentConditions();

        void readOut();
};

#endif