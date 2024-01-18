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