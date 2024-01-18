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
    srand(time(NULL)); // seed random generator

    

    
    stateType initialConditionsDE1 = {0.0, 0.0, 0.0, 0.0};


    // Integrate the differential equations using ODEint
    integrate(createDE1, initialConditionsDE1, t_start, t_end, 0.1, [](const auto& q, const auto t){ 
        cout << t << "\t" << q[0] << "\t" << q[1] << "\t" << q[2] << "\t" << q[3] << endl;
    });

}


void PhoenixPositionProvider::createDE1(const stateType& q, stateType& dqdt, const double t) {
    dqdt[0] = q[1];
    dqdt[1] = 1.0 / mass(t) * WindLoad(q[2]);
    dqdt[2] = q[3];
    dqdt[3] = 1.0 / mass(t) * (Thrust(q[2]) - mass(t) * g - RocketDrag(q[2], q[3]));
}

// define De2, de3, de4
void PhoenixPositionProvider::createDE2(const stateType& q, stateType& dqdt, const double t) {
    dqdt[0] = q[1];
    dqdt[1] = 1.0 / DryMass * WindLoad(q[2]);
    dqdt[2] = q[3];
    dqdt[3] = 1.0 / DryMass * (-DryMass * g - RocketDrag(q[2], q[3]));
}

void PhoenixPositionProvider::createDE3(const stateType& q, stateType& dqdt, const double t) {
    dqdt[0] = q[1];
    dqdt[1] = 1.0 / DryMass * WindLoad(q[2]);
    dqdt[2] = q[3];
    dqdt[3] = 1.0 / DryMass * (RocketDrag(q[2], q[3]) + DrogueDrag(q[2], q[3]) - DryMass*g);
}

void PhoenixPositionProvider::createDE4(const stateType& q, stateType& dqdt, const double t) {
    dqdt[0] = q[1];
    dqdt[1] = 1.0 / DryMass * WindLoad(q[2]);
    dqdt[2] = q[3];
    dqdt[3] = 1.0 / DryMass * (RocketDrag(q[2], q[3]) + MainDrag(q[2], q[3]) - DryMass*g);
}


void PhoenixPositionProvider::process(long simTime, long deltaTime){
    return;
}

int* PhoenixPositionProvider::getPosition(){
    return currCoords;
}
