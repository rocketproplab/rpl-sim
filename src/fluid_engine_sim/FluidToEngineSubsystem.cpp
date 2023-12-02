#include "FluidToEngineSubsystem.h"

enum FluidToEngineStatus {WAITING_FOR_LAUNCH_COMMAND, SOLENOIDS_OPEN_FUEL_FLOWING, ENGINE_RUNNING, BURNOUT};

class FluidToEngineSubsystem {
    public:
        FluidToEngineSubsystem ():status {WAITING_FOR_LAUNCH_COMMAND}
        {};

        int LNG_solenoid = 0; // index for solenoid from Liquid Nitrogen tank to combustion chamber
        int LOX_solenoid = 1; // index for solenoid from Liquid Oxygen tank to combustion chamber
        
        // called once per simulation step
        void process();
        // if (true){ //solenoid in wrong state
        //     abort();
        // }

        // set solenoid state
        void setSolenoidState(int index, bool isOpen);

        // simulates ignition firing
        void ignite();

        void setStatus(int new_status);

        int getStatus();

    private:
        int status;
        std::vector<bool> solenoids = {false, false};
};

// process loop; if something goes wrong, catch error and crash program
void FluidToEngineSubsystem::process() {
    try {
        double solenoid_to_engine_run_timer = 0.0;
        double target = 300; // placeholder value right now
        if (getStatus() == WAITING_FOR_LAUNCH_COMMAND) {
            setSolenoidState(LNG_solenoid, true);
            setSolenoidState(LOX_solenoid, true);
            setStatus(SOLENOIDS_OPEN_FUEL_FLOWING);
        }

        if (getStatus() == SOLENOIDS_OPEN_FUEL_FLOWING) {
            if (solenoid_to_engine_run_timer > target) {
                throw std::runtime_error("Window closed");
            }
        }

        if (status == ENGINE_RUNNING) {
            if (solenoids[LNG_solenoid] == false || solenoids[LOX_solenoid] == false) {
                throw std::runtime_error("Attempted to close solenoid while engine running"); 
            }
        }

        solenoid_to_engine_run_timer++;
    }catch(exception& e) {
        std::abort();

    }
}

void FluidToEngineSubsystem::setSolenoidState(int index, bool isOpen) {
    solenoids[index] = isOpen;
}

void FluidToEngineSubsystem::setStatus(int new_status) {
    status = new_status;
}

void FluidToEngineSubsystem::ignite() {
    if (status != SOLENOIDS_OPEN_FUEL_FLOWING) {
        throw std::runtime_error("Attempted ignition with solenoids closed"); 
    }

    if (solenoids[LNG_solenoid] == false || solenoids[LOX_solenoid] == false) {
        throw std::runtime_error("Attempted ignition with solenoids closed and status falsely set"); 
    }

    setStatus(ENGINE_RUNNING);
}

int FluidToEngineSubsystem::getStatus() {
    return status;
}