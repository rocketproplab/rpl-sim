#ifndef PHOENIX_POSITION_PROVIDER_H
#define PHOENIX_POSITION_PROVIDER_H
#include <time.h> // for seeind rand
#include <stdlib.h> // for rand
#include "PhoenixPositionProviderUtility.h"


using namespace boost::numeric::odeint;

extern vector<stateType> allPositions;

/*
process(long simTime, long deltaTime): This function is 
called once per simulation step.Use this function to update
 the internal position/rotation state.
*/
class PhoenixPositionProvider{
    private:
        const float dt = 0.001;

        int currCoords[3] = {0, 0, 0};
        int previousRotState;
        int updatedRotState;
        int igniteCounter;
        int destroyed;

    public:
        PhoenixPositionProvider();
        void process(long simTime, long deltaTime);
        int* getPosition();
};

#endif