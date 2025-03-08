#include "Physics.hpp"
#include "Vector3.hpp"


namespace Physics {

    // adds relative noise to the given value
    double addNoise(double value, double noiseFactor) {
        //random noise generator, we can modify this as needed
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-1.0, 1.0);
        double noise = dis(gen);
        return value + (value * noiseFactor * noise);
    }

    // Its assumed that the acceleration from the CSV is already "complete" (i.e. all effects are included)
    // We update only the vertical (y) component using this acceleration
    Physics::XY_State updateState(const XY_State& currentState, double dt, double sensorAcceleration, double sensorAirDensity) {
        // add noise to sensor readings (using 10% relative noise as an example)
        double noisyAcceleration = addNoise(sensorAcceleration, 0.1);
        // sensorAirDensity is read but not used further in the integration
        double noisyAirDensity = addNoise(sensorAirDensity, 0.1);

        // Update velocity: assume acceleration is vertical (y axis) only.
        Vector3 newVelocity = currentState.velocity + Vector3(0, noisyAcceleration * dt, 0);
        // Update position using the new velocity.
        Vector3 newPosition = currentState.position + newVelocity * dt;

        return { newPosition, newVelocity };
    }
}
