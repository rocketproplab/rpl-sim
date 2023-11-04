#include <iostream>
#include <vector>

class FluidToEngineSubsystem {
    public:
        // called once per simulation step
        void process() {
            // TODO: this function will check timestamps and make sure sstuff isnt breaking

        }

        // thing for actuating solenoids; are we going to make a seperate type here for solenoids? Is there a solenoid library we're using?
        bool openSolenoid(int index, bool isOpen) {
            if (index < solenoids.size()) {
                solenoids[index] = isOpen;
            }
            return solenoids[index];
        }

        bool getSolenoidState(int index) {
            return solenoids[index];
        }




    private:
        // vector; has solenoids for liquid oxygen solenoid and liquid oxidizer solenoid
        // TODO: make constants outside of this class in order to name our indices
        std::vector<bool> solenoids = {false, false};

        // simulates ignition firing
        void ignite() {
            // TODO
        }
    
};