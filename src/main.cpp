
// #include "boost_1_82_0/boost/numeric/odeint.hpp"
#include "PhoenixPositionProvider.h"

// typedef boost::array<double, 4> stateType;

// void createDE1(const stateType& q, stateType& dqdt, const double t) {
//     dqdt[0] = q[1];
//     dqdt[1] = 1.0 / mass(t) * WindLoad(q[2]);
//     dqdt[2] = q[3];
//     dqdt[3] = 1.0 / mass(t) * (Thrust(q[2]) - mass(t) * g - RocketDrag(q[2], q[3]));
// }


int main(){
    

    //cout << "finish" << end;
    // srand(time(NULL)); // seed random generator

    // stateType initialConditionsDE1 = {0.0, 0.0, 0.0, 0.0};

    // integrate(createDE1, initialConditionsDE1, start_t, end_t, 0.1, [](const auto& q, const auto t){ 
    //     cout << t << "\t" << q[0] << "\t" << q[1] << "\t" << q[2] << "\t" << q[3] << endl;
    // });

    PhoenixPositionProvider ppp;
}

