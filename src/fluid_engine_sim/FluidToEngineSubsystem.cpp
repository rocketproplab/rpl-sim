#include "FluidToEngineSubsystem.h"

class FluidToEngineSubsystem {
    public:
        FluidToEngineStatus status;
        FluidToEngineSubsystem (){
            LNG_solenoid = false;
            LOX_solenoid = false;
            status = WAITING_FOR_LAUNCH_COMMAND;
        }
        
        // called once per simulation step
        void process() {
            // if (true){ //solenoid in wrong state
            //     abort();
            // }

        }

        // set LNGSolenoid state
        void setLNGSolenoid(bool isOpen) {
            LNG_solenoid = isOpen;
        }

        // set LOXSolenoid state
        void setLOXSolenoid(bool isOpen) {
            LOX_solenoid = isOpen;
        }

        // simulates ignition firing
        void ignite() {
            // TODO
        }

        FluidToEngineStatus getStatus() {
            return status;
        }

    private:
        bool LNG_solenoid; // solenoid from Liquid Nitrogen tank to combustion chamber
        bool LOX_solenoid; // solenoid from Liquid Oxygen tank to combustion chamber

};