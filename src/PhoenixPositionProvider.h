#ifndef PHOENIX_POSITION_PROVIDER_H
#define PHOENIX_POSITION_PROVIDER_H
#include "boost_1_82_0/boost/numeric/odeint.hpp"
#include <vector>
#include <time.h> // for seeind rand
#include <stdlib.h> // for rand
#include <cmath> // for pow
#include "PhoenixPositionProviderUtility.h"

using namespace std;
using namespace boost::numeric::odeint;


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



        typedef boost::array<double, 4> stateType;

        vector<stateType> allPositions;


        void createDE1(const stateType& q, stateType& dqdt, const double t);
    public:
        PhoenixPositionProvider();
        void process(long simTime, long deltaTime);
        int* getPosition();
};

#endif