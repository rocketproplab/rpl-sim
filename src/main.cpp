#include "PhoenixPositionProvider.h"

int main(){
    PhoenixPositionProvider ppp;
    ppp.process(0, 0.0001);
    ppp.process(0.0001, 0.5);
    ppp.ignite();
    ppp.process(0.5001, 10);
    // for (int i = 0; i < 10; i++) {
    //     cout << -1 + 2 * (rand() / static_cast<double>(RAND_MAX)) << endl;
    // }

    // vector<float> abc = GenerateWindLoadData();
    // cout << abc[1] << endl;
    // cout << abc[2] << endl;
    // // for (int i = 10; i < 21; i++) {
    // //     cout << WindLoad(float(i/10)) << endl;
    // // }

    // cout << AirDensityFromAltitude(300.454) << endl;
    // cout << AirDensityFromAltitude(5003.863) << endl;
    // cout << AirDensityFromAltitude(7381.836) << endl;

    // cout << Thrust(300.454) << endl;
    // cout << Thrust(53.863) << endl;
    // cout << Thrust(10.263) << endl;


    // cout << RocketCd(101.454) << endl;
    // cout << RocketCd(53.863) << endl;
    // cout << RocketCd(10.263) << endl;

    // cout << RocketDrag(3003.1, 378.8) << endl;
    // cout << RocketDrag(2541.2, 356.5) << endl;
    // cout << RocketDrag(2.0, 9.2) << endl;

    // stateType testConditions = {6.03593, -0.010735, 8225.07, 4.90564};

    // integrate(createDE3, testConditions, BurnTime+30, BurnTime+430, 0.1, [](const auto& q, const auto t){ 
    //     cout << t << "\t" << q[0] << "\t" << q[1] << "\t" << q[2] << "\t" << q[3] << endl;
    // });

    // vector<float> a = getAltitudes();
    // vector<float> b = getAltitudes();

    // cout << linearInterp(-1, a, b) << endl;
}



