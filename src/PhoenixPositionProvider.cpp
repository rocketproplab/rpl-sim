/*
WHAT WE CURRENTLY UNDERSTAND:
    - There is an update loop being called in another file
    - The process function in our file will be called at each step in the loop
    - 
*/
// Define your differential equations

/* TO DO
- make a linear interpolation function
- make air density a function of altitude (using interpolation or something)
*/

# include "PhoenixPositionProvider.h"



PhoenixPositionProvider::PhoenixPositionProvider() {
    cout << "finish" << endl;
    srand(time(NULL)); // seed random generator

    

    
    stateType initialConditionsDE1 = {0.0, 0.0, 0.0, 0.0};


    //Integrate the differential equations using ODEint
    integrate(createDE1, initialConditionsDE1, start_t, end_t, 0.1, [](const auto& q, const auto t){ 
        cout << t << "\t" << q[0] << "\t" << q[1] << "\t" << q[2] << "\t" << q[3] << endl;
    });


}




void PhoenixPositionProvider::process(long simTime, long deltaTime){
    return;
}

int* PhoenixPositionProvider::getPosition(){
    return currCoords;
}
