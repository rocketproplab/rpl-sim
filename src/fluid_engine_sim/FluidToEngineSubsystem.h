#include <iostream>

class FluidToEngineSubsystem {
    public:
        // called once per simulation step
        void process() {
            // TODO

        }



    private:
        // simulates ignition firing
        void ignite() {
            // TODO
        }

        // thing for actuating solenoids; are we going to make a seperate type here for solenoids? Is there a solenoid library we're using?
        void setSolenoidState(int index, bool isOpen) {
            // TODO
        }

    
};