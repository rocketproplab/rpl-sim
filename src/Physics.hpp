#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "Vector3.hpp"

namespace Physics {

    // Holds the current state of the rocket (position and velocity)
    struct XY_State {
        Vector3 position;
        Vector3 velocity;
    };

    /**
     * Update the state of the rocket using sensor data.
     *
     * The state is updated as:
     *   velocity_new = velocity_old + (noisy_acceleration * dt)
     *   position_new = position_old + (velocity_new * dt)
     *
     * @param currentState The current state (position and velocity).
     * @param dt Time step (in seconds).
     * @param sensorAcceleration The measured acceleration (m/s^2) from the CSV.
     * @param sensorAirDensity The measured air density (kg/m^3) from the CSV (read but not used).
     * @return XY_State The new state after dt seconds.
     */
    XY_State updateState(const XY_State& currentState, double dt, double sensorAcceleration, double sensorAirDensity);

    /**
     * @brief Adds relative noise to a sensor value.
     *
     * The noise amplitude is scaled relative to the magnitude of the input value.
     * For example, for a value of 10 and noiseFactor 0.1, noise will be in the range ±1.
     *
     * @param value The original sensor value.
     * @param noiseFactor The relative noise factor (e.g., 0.1 for 10% noise).
     * @return double The sensor value with noise added.
     */
    double addNoise(double value, double noiseFactor)
}

#endif
