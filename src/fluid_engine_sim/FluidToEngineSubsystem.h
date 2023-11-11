#include <iostream>
enum FluidToEngineStatus {WAITING_FOR_LAUNCH_COMMAND, SOLENOIDS_OPEN_FUEL_FLOWING, ENGINE_RUNNING, BURNOUT};
class FluidToEngineSubsystem {
    public:
        FluidToEngineStatus status;
        
        // called once per simulation step
        void process();

        // set LNGSolenoid state
        void setLNGSolenoid(bool isOpen);

        // set LOXSolenoid state
        void setLOXSolenoid(bool isOpen);

        // simulates ignition firing
        void ignite();

        /*
            Returns the current status of this task (WAITING_FOR_LAUNCH_COMMAND, SOLENOIDS_OPEN_FUEL_FLOWING, ENGINE_RUNNING, BURNOUT)
            If the status changed, this function should reflect the current state as of the most recent loop.
        */
        FluidToEngineStatus getStatus();

    private:
        bool LNG_solenoid; // solenoid from Liquid Nitrogen tank to combustion chamber
        bool LOX_solenoid; // solenoid from Liquid Oxygen tank to combustion chamber

};