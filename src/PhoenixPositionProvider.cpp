# include "PhoenixPositionProvider.h"
// TODO
// - confirm maxDeploymentSpeeds (defined in .h) with Recovery people
// change coordinate system to right-handed
// - test!!!

PhoenixPositionProvider::PhoenixPositionProvider() {
    
    // x pos, x vel, y pos, y vel, z pos, z vel
    currentConditions = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

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
        
        if (ignitionTime + burnTime < currentTime + deltaTime) {
            double step1 = ignitionTime + burnTime;
            double step2 = currentTime + deltaTime - step1;

            cout << step1 << endl;
            cout << step2 << endl;

            // use DE1 till fuel runs out
            integrate_const(
                stepper, createDE1, currentConditions, currentTime, currentTime + step1, dt, push_back_state_and_time(allPositions, times)
            );
            cout << "fuel ran out!";

            // switch state to COAST
            rocketState = State::COAST;
            cout << "in COAST stage";
            // use DE2, since fuel is run out
            integrate_const(
                stepper, createDE2, currentConditions, currentTime + step1, currentTime + step1 + step2, dt, push_back_state_and_time(allPositions, times)
            );
        } else {
            // use DE1 (burn stage system of equation)
            integrate_const(
                stepper, createDE1, currentConditions, currentTime, currentTime + deltaTime, dt, push_back_state_and_time(allPositions, times)
            );
        }
        
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
    currCoords[1] = currentConditions[2]; // not updating y since its not added yet
    currCoords[2] = currentConditions[4];
    
    // cout << "Rocket Y position is: " << currCoords[2] << endl;
    cout << "last position: " << allPositions[allPositions.size() - 1][0] << "\t" << allPositions[allPositions.size() - 1][1] << "\t" << allPositions[allPositions.size() - 1][2] << "\t" << allPositions[allPositions.size() - 1][4] << "\t" <<allPositions[allPositions.size() - 1][5] << endl;

    // terminate program when rocket has crashed
    if (currCoords[1] <= 0 && rocketState != State::PRE_FLIGHT) {
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
    ignitionTime = currentTime;
    cout << "------ Rocket Ignition! ------" << endl;
    cout << "ignition time" << ignitionTime << endl;
}

void PhoenixPositionProvider::drogue(){
    if (drogueCounter != 0) {
        throw runtime_error("Error: PhoenixPositionProvider::drogue() was called twice.");
    }
    
    if (currentConditions[5] > drogueMaxDeploymentSpeed) {
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
    
    if (currentConditions[5] > chuteMaxDeploymentSpeed) {
        throw runtime_error("Error: Chute deployment speed was too fast. Chute ripped.");
    }
    chuteCounter = 1;
    rocketState = State::CHUTE;
    cout << "------ Main Chute Deployment! ------" << endl;
}

