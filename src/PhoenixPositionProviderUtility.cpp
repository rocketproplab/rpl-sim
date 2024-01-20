# include "PhoenixPositionProviderUtility.h"


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

// define De2, de3, de4
void createDE2(const stateType& q, stateType& dqdt, const double t) {
    dqdt[0] = q[1];
    dqdt[1] = 1.0 / DryMass * WindLoad(q[2]);
    dqdt[2] = q[3];
    dqdt[3] = 1.0 / DryMass * (-DryMass * g - RocketDrag(q[2], q[3]));
}

void createDE3(const stateType& q, stateType& dqdt, const double t) {
    dqdt[0] = q[1];
    dqdt[1] = 1.0 / DryMass * WindLoad(q[2]);
    dqdt[2] = q[3];
    dqdt[3] = 1.0 / DryMass * (RocketDrag(q[2], q[3]) + DrogueDrag(q[2], q[3]) - DryMass*g);
}

void createDE4(const stateType& q, stateType& dqdt, const double t) {
    dqdt[0] = q[1];
    dqdt[1] = 1.0 / DryMass * WindLoad(q[2]);
    dqdt[2] = q[3];
    dqdt[3] = 1.0 / DryMass * (RocketDrag(q[2], q[3]) + MainDrag(q[2], q[3]) - DryMass*g);
}