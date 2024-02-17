# include "PhoenixPositionProvider.h"
// TODO
// - add third dimension to currentConditions (x, vx, y, vy, z, vz)
// - confirm maxDeploymentSpeeds (defined in .h) with Recovery people
// - test!!!

PhoenixPositionProvider::PhoenixPositionProvider() {
    srand(time(NULL)); // seed random generator
    
    // x pos, x vel, y pos, y vel
    currentConditions = {0.0, 0.0, 0.0, 0.0};

    igniteCounter = 0;
    chuteCounter = 0;
    drogueCounter = 0;

    rocketState = State::PRE_FLIGHT;
    
}

void PhoenixPositionProvider::process(double simTime, double deltaTime){
    cout << "--------------" << endl;
    cout << "current internal time is " << currentTime << endl;
    // do the integration, based on the current stage

    if (rocketState == State::PRE_FLIGHT) {
        cout << "in PRE_FLIGHT stage" << endl;
        allPositions.push_back(currentConditions);

    } else if (rocketState == State::BURN) {
        cout << "in BURN stage" << endl;

        // use DE1 (burn stage system of equation)
        integrate_const(
            stepper, createDE1, currentConditions, currentTime, currentTime + deltaTime, dt, push_back_state_and_time(allPositions, times)
            );
        // cout << "last position: " << allPositions[allPositions.size() - 1][0] << "\t" << allPositions[allPositions.size() - 1][1] << "\t" << allPositions[allPositions.size() - 1][2] << "\t" << allPositions[allPositions.size() - 1][3] << endl;
        
        // update currentConditions for next integration
        currentConditions = allPositions[allPositions.size() - 1];

    } else if (rocketState == State::COAST) {
        cout << "in COAST stage" << endl;
        integrate_const(
            stepper, createDE2, currentConditions, currentTime, currentTime + deltaTime, dt, push_back_state_and_time(allPositions, times)
            );
        // update currentConditions for next integration
        currentConditions = allPositions[allPositions.size() - 1];

    } else if (rocketState == State::DROGUE) {
        cout << "in DROGUE CHUTE stage" << endl;
        integrate_const(
            stepper, createDE3, currentConditions, currentTime, currentTime + deltaTime, dt, push_back_state_and_time(allPositions, times)
            );
        // update currentConditions for next integration
        currentConditions = allPositions[allPositions.size() - 1];
    } else if (rocketState == State::CHUTE) {
        cout << "in MAIN CHUTE stage" << endl;
        integrate_const(
            stepper, createDE4, currentConditions, currentTime, currentTime + deltaTime, dt, push_back_state_and_time(allPositions, times)
            );
        // update currentConditions for next integration
        currentConditions = allPositions[allPositions.size() - 1];
    }

    currentTime += deltaTime;
    cout << "new internal time is " << currentTime << endl;

    // update currCoords
    currCoords[0] = currentConditions[0];
    // currCoords[1] = currentConditions[1]; // not updating y since its not added yet
    currCoords[2] = currentConditions[2];
    
    // cout << "Rocket Y position is: " << currCoords[2] << endl;
    cout << "last position: " << allPositions[allPositions.size() - 1][0] << "\t" << allPositions[allPositions.size() - 1][1] << "\t" << allPositions[allPositions.size() - 1][2] << "\t" << allPositions[allPositions.size() - 1][3] << endl;

    // terminate program when rocket has crashed
    if (currCoords[2] <= 0 && rocketState != State::PRE_FLIGHT) {
        // TODO: Add rocket state and Y velocity to error message so we can see if it was a crash or landing
        throw runtime_error("Rocket Y position <= 0. Rocket has landed (hopefully), or crashed.");
    }
}

double* PhoenixPositionProvider::getPosition(){
    return currCoords;
}

void PhoenixPositionProvider::ignite(){
    if (igniteCounter != 0) {
        throw runtime_error("Error: PhoenixPositionProvider::ignite() was called twice.");
    }
    igniteCounter = 1;
    rocketState = State::BURN;
    cout << "------ Rocket Ignition! ------" << endl;
}

void PhoenixPositionProvider::drogue(){
    if (drogueCounter != 0) {
        throw runtime_error("Error: PhoenixPositionProvider::drogue() was called twice.");
    }
    
    if (currentConditions[3] > drogueMaxDeploymentSpeed) {
        throw runtime_error("Error: Drogue deployment speed was too fast. Chute ripped.");
    }
    drogueCounter = 1;
    rocketState = State::DROGUE;
    cout << "------ Drogue Chute Deployment! ------" << endl;
}

void PhoenixPositionProvider::chute(){
    if (chuteCounter != 0) {
        throw runtime_error("Error: PhoenixPositionProvider::chute() was called twice.");
    }
    
    if (currentConditions[3] > chuteMaxDeploymentSpeed) {
        throw runtime_error("Error: Chute deployment speed was too fast. Chute ripped.");
    }
    chuteCounter = 1;
    rocketState = State::CHUTE;
    cout << "------ Main Chute Deployment! ------" << endl;
}

