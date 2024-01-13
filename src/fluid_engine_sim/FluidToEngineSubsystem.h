#include <iostream>
#include <exception>
#include <thread>
#include <chrono>

enum class FluidToEngineStatus {WAITING_FOR_LAUNCH_COMMAND, SOLENOIDS_OPEN_FUEL_FLOWING, ENGINE_RUNNING, BURNOUT};

enum class Solenoid {LNG_solenoid, LOX_solenoid};

class FluidToEngineSubsystem {
    public:
        FluidToEngineSubsystem ():status {FluidToEngineStatus::WAITING_FOR_LAUNCH_COMMAND}
        {};
        
        // called once per simulation step
        void process(double solenoid_to_engine_run_timer, double target);
        // if (true){ //solenoid in wrong state
        //     abort();
        // }

        // set solenoid state
        void setSolenoidState(Solenoid s, bool isOpen);

        // simulates ignition firing
        void ignite();

        void setStatus(FluidToEngineStatus new_status);

        FluidToEngineStatus getStatus();

    private:
        FluidToEngineStatus status;
        std::vector<bool> solenoids = {false, false};
};
