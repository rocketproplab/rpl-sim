#include "FluidToEngineSubsystem.h"

// process loop; if something goes wrong, catch error and crash program
void FluidToEngineSubsystem::process(double solenoid_to_engine_run_timer, double target) {

    //this is for dummy sim purposes
    if (getStatus() == FluidToEngineStatus::SOLENOIDS_OPEN_FUEL_FLOWING) {
        ignite();
    }
    // try { // DO not want to catch errors yet, or even here. Want to catch errors in calling function.
    if (getStatus() == FluidToEngineStatus::WAITING_FOR_LAUNCH_COMMAND) {
        setSolenoidState(Solenoid::LNG_solenoid, true);
        setSolenoidState(Solenoid::LOX_solenoid, true);
        setStatus(FluidToEngineStatus::SOLENOIDS_OPEN_FUEL_FLOWING);
    }

    if (getStatus() == FluidToEngineStatus::SOLENOIDS_OPEN_FUEL_FLOWING) {
        if (solenoid_to_engine_run_timer > target) {
            throw std::runtime_error("Window closed");
        }
    }

    if (status == FluidToEngineStatus::ENGINE_RUNNING) {
        if (solenoids[(int)Solenoid::LNG_solenoid] == false || solenoids[(int)Solenoid::LOX_solenoid] == false) {
            throw std::runtime_error("Attempted to close solenoid while engine running"); 
        }
    }
    // }catch(exception& e) {
    //     std::abort();

    // } 
}

void FluidToEngineSubsystem::setSolenoidState(Solenoid s, bool isOpen) {
    solenoids[(int)s] = isOpen;
}

bool FluidToEngineSubsystem::getSolenoidState(Solenoid s) {
    if ((int)s >= solenoids.size()) throw std::out_of_range("Index out of bounds exception");
    return (solenoids[int(s)]);
}

void FluidToEngineSubsystem::setStatus(FluidToEngineStatus new_status) {
    status = new_status;
}

void FluidToEngineSubsystem::ignite() {
    if (status != FluidToEngineStatus::SOLENOIDS_OPEN_FUEL_FLOWING) {
        throw std::runtime_error("Attempted ignition with solenoids closed"); 
    }

    if (solenoids[(int)Solenoid::LNG_solenoid] == false || solenoids[(int)Solenoid::LOX_solenoid] == false) {
        throw std::runtime_error("Attempted ignition with solenoids closed and status falsely set"); 
    }

    setStatus(FluidToEngineStatus::ENGINE_RUNNING);
}

FluidToEngineStatus FluidToEngineSubsystem::getStatus() {
    return status;
}