/* TO DO
- make a linear interpolation function
- make air density a function of altitude (using interpolation or something)
*/
# include "PhoenixPositionProvider.h"


vector<stateType> allPositions;

PhoenixPositionProvider::PhoenixPositionProvider() {
    cout << "finish" << endl;
    srand(time(NULL)); // seed random generator
    
    stateType initialConditions = {0.0, 0.0, 0.0, 0.0};

    //Integrate the differential equations using ODEint
    integrate(createDE1, initialConditions, start_t, BurnTime, 0.1, [](const auto& q, const auto t){ 
        //cout << t << "\t" << q[0] << "\t" << q[1] << "\t" << q[2] << "\t" << q[3] << endl;
    });
    cout << initialConditions[0] << "\t" << initialConditions[1] << "\t" << initialConditions[2] << "\t" << initialConditions[3] << endl;

    integrate(createDE2, initialConditions, BurnTime, BurnTime+30, 0.1, [](const auto& q, const auto t){ 
        //cout << t << "\t" << q[0] << "\t" << q[1] << "\t" << q[2] << "\t" << q[3] << endl;
    });

    cout << initialConditions[0] << "\t" << initialConditions[1] << "\t" << initialConditions[2] << "\t" << initialConditions[3] << endl;

    integrate(createDE3, initialConditions, BurnTime+30, BurnTime+430, 0.1, [](const auto& q, const auto t){ 
        //cout << t << "\t" << q[0] << "\t" << q[1] << "\t" << q[2] << "\t" << q[3] << endl;
    });

    cout << initialConditions[0] << "\t" << initialConditions[1] << "\t" << initialConditions[2] << "\t" << initialConditions[3] << endl;

    // integrate(createDE4, initialConditions, BurnTime +430 , BurnTime+1030, 0.1, [](const auto& q, const auto t){ 
    //     cout << t << "\t" << q[0] << "\t" << q[1] << "\t" << q[2] << "\t" << q[3] << endl;
    // });
    // cout << initialConditions[0] << "\t" << initialConditions[1] << "\t" << initialConditions[2] << "\t" << initialConditions[3] << endl;
}

void PhoenixPositionProvider::process(long simTime, long deltaTime){
    return;
}

int* PhoenixPositionProvider::getPosition(){
    return currCoords;
}
