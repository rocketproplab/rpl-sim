#include "FluidToEngineSubsystem.h"

enum FluidToEngineStatus {WAITING_FOR_LAUNCH_COMMAND, SOLENOIDS_OPEN_FUEL_FLOWING, ENGINE_RUNNING, BURNOUT};

class FluidToEngineSubsystem {
    public:
        FluidToEngineSubsystem ():status {WAITING_FOR_LAUNCH_COMMAND}
        {};
        
        // called once per simulation step
        void process();
        // if (true){ //solenoid in wrong state
        //     abort();
        // }

        // set LNGSolenoid state
        void setLNGSolenoid(bool isOpen);

        // set LOXSolenoid state
        void setLOXSolenoid(bool isOpen);

        // simulates ignition firing
        void ignite();

        void setStatus(int new_status);

        int getStatus();

    private:
        int status;
        bool LNG_solenoid = false;; // solenoid from Liquid Nitrogen tank to combustion chamber
        bool LOX_solenoid = false;; // solenoid from Liquid Oxygen tank to combustion chamber

};

// process loop; if something goes wrong, catch error and crash program
void FluidToEngineSubsystem::process() {
    try {
        if (getStatus() == WAITING_FOR_LAUNCH_COMMAND) ignite();
        // test conditionals that will blow up rocket

    }catch(exception& e) {
        std::abort();

    }
}

void FluidToEngineSubsystem::setLNGSolenoid(bool isOpen) {
    LNG_solenoid = isOpen;
}

void FluidToEngineSubsystem::setLOXSolenoid(bool isOpen) {
    LOX_solenoid = isOpen;
}

void FluidToEngineSubsystem::setStatus(int new_status) {
    status = new_status;
}

void FluidToEngineSubsystem::ignite() {
    setLNGSolenoid(true);
    setLOXSolenoid(true);

    setStatus(SOLENOIDS_OPEN_FUEL_FLOWING);

    // wait 0.02-0.1 seconds (not sure if I should include this sleep step)
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    setStatus(ENGINE_RUNNING);
}

int FluidToEngineSubsystem::getStatus() {
    return status;
}