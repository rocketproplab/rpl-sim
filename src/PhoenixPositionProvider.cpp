
#include "PhoenixPositionProvider.h"

using namespace std;

PhoenixPositionProvider::PhoenixPositionProvider() {
    // srand(time(NULL)); // seed random generator
    
    // // x pos, x vel, y pos, y vel
    // currentConditions = {0.0, 0.0, 0.0, 0.0};

    // igniteCounter = 0;
    // chuteCounter = 0;
    // drogueCounter = 0;

    rocketState = State::PRE_FLIGHT;
    
}

void PhoenixPositionProvider::process(double simTime, double deltaTime){
    if(rocketState == State::PRE_FLIGHT){
        rocketState = State::BURN;
    }
    else if(rocketState == State::BURN){
        rocketState = State::COAST;
    }
    else if(rocketState == State::COAST){
        rocketState = State::DROGUE;
    }
    else if(rocketState == State::DROGUE){
        rocketState = State::CHUTE;
    }
    currCoords[2]++;
}

double* PhoenixPositionProvider::getPosition(){
    return currCoords;
}