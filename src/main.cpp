#include "PhoenixPositionProvider.h"
// #include "boost_1_82_0/boost/numeric/odeint.hpp"
// #include "PhoenixPositionProviderUtility.h"
#include <iostream>
using namespace std;
using namespace boost::numeric::odeint;

typedef boost::array<double, 4> stateType;


float mass(float t) {
    return DryMass + FuelMass - m_dot * t;
}
// calculate the mass of rocket at time t

float WindLoad(float y) {
    int WindOffset = (rand() % 7) - 3; // force range to [-3, 3]
    return 1 / 2 * rho * pow(AvgWindSpeed + WindOffset, 2) * Rocket_WindloadArea;
}

float Thrust(float y) {
    return 1;
}

float RocketCd(float vy) {
    return 1;
}


float RocketDrag(float y, float vy) {
    return 1;
}

float DrogueDrag(float y, float vy) {
    return 1;
}

float MainDrag(float y, float vy) {
    return 1;
}

void createDE1(const stateType& q, stateType& dqdt, const double t) {
    dqdt[0] = q[1];
    dqdt[1] = 1.0 / mass(t) * WindLoad(q[2]);
    dqdt[2] = q[3];
    dqdt[3] = 1.0 / mass(t) * (Thrust(q[2]) - mass(t) * g - RocketDrag(q[2], q[3]));
}


int main(){
    

    //cout << "finish" << end;
    srand(time(NULL)); // seed random generator

    stateType initialConditionsDE1 = {0.0, 0.0, 0.0, 0.0};

    integrate(createDE1, initialConditionsDE1, start_t, end_t, 0.1, [](const auto& q, const auto t){ 
        cout << t << "\t" << q[0] << "\t" << q[1] << "\t" << q[2] << "\t" << q[3] << endl;
    });
}

