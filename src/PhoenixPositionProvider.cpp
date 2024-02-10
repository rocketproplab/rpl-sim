/* TO DO
- make a linear interpolation function
- make air density a function of altitude (using interpolation or something)
*/
# include "PhoenixPositionProvider.h"


// vector<vector<stateType>> allPositions;

PhoenixPositionProvider::PhoenixPositionProvider() {
    srand(time(NULL)); // seed random generator
    
    // x pos, x vel, y pos, y vel
    initialConditions = {0.0, 0.0, 0.0, 0.0};

    igniteCounter = 0;

    rocketState = State::PRE_FLIGHT;
    
}

void PhoenixPositionProvider::process(double simTime, double deltaTime){
    cout << "--------------" << endl;
    cout << "current internal time is " << currentTime << endl;
    // do the integration, based on the current stage

    if (rocketState == State::PRE_FLIGHT) {
        cout << "in PRE_FLIGHT stage" << endl;
        allPositions.push_back(initialConditions);
    } else if (rocketState == State::BURN) {
        cout << "in BURN stage" << endl;

        // use DE1 (burn stage system of equation)
        integrate_const(stepper, createDE1, initialConditions, currentTime, currentTime + deltaTime, dt, push_back_state_and_time(allPositions, times));
        // cout << "last position: " << allPositions[allPositions.size() - 1][0] << "\t" << allPositions[allPositions.size() - 1][1] << "\t" << allPositions[allPositions.size() - 1][2] << "\t" << allPositions[allPositions.size() - 1][3] << endl;
        
        // update initialConditions for next integration
        initialConditions = allPositions[allPositions.size() - 1];
    }

    currentTime += deltaTime;
    cout << "new internal time is " << currentTime << endl;

    // update currCoords
    currCoords[0] = initialConditions[0];
    // currCoords[1] = initialConditions[0]; // not updating y since its not added yet
    currCoords[2] = initialConditions[2];
    
    // cout << "Rocket Y position is: " << currCoords[2] << endl;
    cout << "last position: " << allPositions[allPositions.size() - 1][0] << "\t" << allPositions[allPositions.size() - 1][1] << "\t" << allPositions[allPositions.size() - 1][2] << "\t" << allPositions[allPositions.size() - 1][3] << endl;

    // terminate program when rocket has crashed
    if (currCoords[2] <= 0 && rocketState != State::PRE_FLIGHT) {
        throw runtime_error("Rocket Y position <= 0. Rocket has landed (hopefully), or crashed.");
    }




        //Integrate the differential equations using ODEint
    // integrate_const(stepper, createDE1, initialConditions, start_t, BurnTime, timestep, [](const auto& q, const auto t){ 
    //     cout << t << "\t" << q[0] << "\t" << q[1] << "\t" << q[2] << "\t" << q[3] << endl;
    // });
    // cout << initialConditions[0] << "\t" << initialConditions[1] << "\t" << initialConditions[2] << "\t" << initialConditions[3] << endl;

    // integrate_const(stepper, createDE2, initialConditions, BurnTime, BurnTime+30, timestep, [](const auto& q, const auto t){ 
    //     cout << t << "\t" << q[0] << "\t" << q[1] << "\t" << q[2] << "\t" << q[3] << endl;
    // });

    // // // cout << initialConditions[0] << "\t" << initialConditions[1] << "\t" << initialConditions[2] << "\t" << initialConditions[3] << endl;

    // integrate_const(stepper, createDE3, initialConditions, BurnTime+30, BurnTime+430, timestep, [](const auto& q, const auto t){ 
    //     cout << t << "\t" << q[0] << "\t" << q[1] << "\t" << q[2] << "\t" << q[3] << endl;
    // });

    // // // cout << initialConditions[0] << "\t" << initialConditions[1] << "\t" << initialConditions[2] << "\t" << initialConditions[3] << endl;

    // integrate_const(stepper, createDE4, initialConditions, BurnTime +430 , BurnTime+608, timestep, [](const auto& q, const auto t){ 
    //     cout << t << "\t" << q[0] << "\t" << q[1] << "\t" << q[2] << "\t" << q[3] << endl;
    // });
    // cout << "done" << endl;
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
