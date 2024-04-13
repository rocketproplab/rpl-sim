#include "PhoenixPositionProvider.h"

using std::stof;
using std::string;

using std::runtime_error;

using std::cout;
using std::endl;

// TODO
// - confirm maxDeploymentSpeeds (defined in .h) with Recovery people
// change coordinate system to right-handed
// - test!!!

PhoenixPositionProvider::PhoenixPositionProvider()
{
    // x pos, x vel, y pos, y vel, z pos, z vel
    currentConditions = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    position = Vector3(0, 0, 0);

    didIgniteFlag = false;
    didChuteFlag = false;
    didDrogueFlag = false;

    rocketState = State::PRE_FLIGHT;
}

void PhoenixPositionProvider::process(double deltaTime)
{
    cout << "--------------" << endl;
    cout << "current internal time is " << currentTime << endl;
    // do the integration, based on the current stage

    if (rocketState == State::PRE_FLIGHT) {
        cout << "in PRE_FLIGHT stage" << endl;
        allPositions.push_back(currentConditions);

    } else if (rocketState == State::BURN) {
        cout << "in BURN stage" << endl;

        if (ignitionTime + burnTime < currentTime + deltaTime) {
            double step1 = ignitionTime + burnTime - currentTime;
            double step2 = deltaTime - step1;

            cout << "BURN stage: " << currentTime << " -> "
                 << currentTime + step1 << endl;

            // use DE1 till fuel runs out
            integrate_const(stepper, createDE1, currentConditions, currentTime,
                            currentTime + step1, dt,
                            push_back_state_and_time(allPositions, times));

            currentConditions = allPositions[allPositions.size() - 1];
            cout << "fuel ran out!\n";

            // switch state to COAST
            rocketState = State::COAST;
            cout << "switching state to COAST!\n";
            cout << "COAST stage: " << currentTime + step1 << " -> "
                 << currentTime + step1 + step2 << endl;

            // use DE2, since fuel is run out
            integrate_const(stepper, createDE2, currentConditions,
                            currentTime + step1, currentTime + step1 + step2,
                            dt, push_back_state_and_time(allPositions, times));
        } else {
            // use DE1 (burn stage system of equation)
            integrate_const(stepper, createDE1, currentConditions, currentTime,
                            currentTime + deltaTime, dt,
                            push_back_state_and_time(allPositions, times));
        }

        // update currentConditions for next integration
        currentConditions = allPositions[allPositions.size() - 1];

    } else if (rocketState == State::COAST) {
        cout << "in COAST stage" << endl;
        integrate_const(stepper, createDE2, currentConditions, currentTime,
                        currentTime + deltaTime, dt,
                        push_back_state_and_time(allPositions, times));
        // update currentConditions for next integration
        currentConditions = allPositions[allPositions.size() - 1];

    } else if (rocketState == State::DROGUE) {
        cout << "in DROGUE CHUTE stage" << endl;
        integrate_const(stepper, createDE3, currentConditions, currentTime,
                        currentTime + deltaTime, dt,
                        push_back_state_and_time(allPositions, times));
        // update currentConditions for next integration
        currentConditions = allPositions[allPositions.size() - 1];
    } else if (rocketState == State::CHUTE) {
        cout << "in MAIN CHUTE stage" << endl;
        integrate_const(stepper, createDE4, currentConditions, currentTime,
                        currentTime + deltaTime, dt,
                        push_back_state_and_time(allPositions, times));
        // update currentConditions for next integration
        currentConditions = allPositions[allPositions.size() - 1];
    }

    currentTime += deltaTime;
    cout << "new internal time is " << currentTime << "\n" << endl;

    // update currCoords
    position.x = currentConditions[0];
    position.y = currentConditions[2];
    position.z = currentConditions[4];

    readOut();

    // terminate program when rocket has crashed
    if (position.y <= 0 && rocketState != State::PRE_FLIGHT) {
        readOut();
        // TODO: Add rocket state and Y velocity to error message so we can see
        // if it was a crash or landing
        throw runtime_error(
            "Rocket Y position <= 0. Rocket has landed (hopefully), or "
            "crashed.");
    }
}

Vector3 PhoenixPositionProvider::getPosition() { return this->position; }

PhoenixPositionProvider::State PhoenixPositionProvider::getFlightState()
{
    return this->rocketState;
}

void PhoenixPositionProvider::ignite()
{
    if (didIgniteFlag) {
        throw runtime_error(
            "Error: PhoenixPositionProvider::ignite() was called twice.");
    }
    didIgniteFlag = true;
    rocketState = State::BURN;
    ignitionTime = currentTime;
    // cout << "------ Rocket Ignition! ------" << endl;
    // cout << "ignition time: " << ignitionTime << "\n" << endl;
}

bool PhoenixPositionProvider::didIgnite() { return this->didIgniteFlag; }

void PhoenixPositionProvider::drogue()
{
    if (!didIgniteFlag) {
        throw runtime_error("Error: Drogue deployment before ignition");
    }

    if (didDrogueFlag) {
        throw runtime_error(
            "Error: PhoenixPositionProvider::drogue() was called twice.");
    }

    if (abs(currentConditions[3]) > drogueMaxDeploymentSpeed) {
        readOut();
        throw runtime_error(
            "Error: Drogue deployment speed was too fast. Chute ripped.");
    }
    didDrogueFlag = true;
    rocketState = State::DROGUE;
    cout << "------ Drogue Chute Deployment! ------" << endl;
}

bool PhoenixPositionProvider::didDrogue() { return this->didDrogueFlag; }

void PhoenixPositionProvider::chute()
{
    if (!didIgniteFlag) {
        throw runtime_error("Error: Chute deployed before main ignition.");
    }
    if (!didDrogueFlag) {
        throw runtime_error("Error: Chute deployed before drogue deployment");
    }
    if (didChuteFlag) {
        throw runtime_error(
            "Error: PhoenixPositionProvider::chute() was called twice.");
    }

    if (abs(currentConditions[3]) > chuteMaxDeploymentSpeed) {
        readOut();
        throw runtime_error(
            "Error: Chute deployment speed was too fast. Chute ripped.");
    }
    didChuteFlag = true;
    rocketState = State::CHUTE;
    cout << "------ Main Chute Deployment! ------" << endl;
}

bool PhoenixPositionProvider::didChute() { return this->didChuteFlag; }

stateType PhoenixPositionProvider::getCurrentConditions()
{
    return currentConditions;
}

void PhoenixPositionProvider::readOut()
{
    cout << "[Rocket Telemetry]\n"
         << "x_pos: " << currentConditions[0]
         << ", x_vel: " << currentConditions[1]
         << "\ny_pos: " << currentConditions[2]
         << ", y_vel: " << currentConditions[3]
         << "\nz_pos: " << currentConditions[4]
         << ", z_vel: " << currentConditions[5] << endl;
}
