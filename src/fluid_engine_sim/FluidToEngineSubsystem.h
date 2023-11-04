#include <iostream>

class FluidToEngineSubsystem {
    public:
        // called once per simulation step
        void process() {
            // TODO

        }

        // thing for actuating solenoids; are we going to make a seperate type here for solenoids? Is there a solenoid library we're using?
        void setSolenoidState(int index, bool isOpen) {
            // TODO
            solenoids[index] = isOpen;
        }


    private:
        // Honestly not sure how we're implementing this, but a vector makes sense to me here.
        // If we got the vector route, we need to include the standard library vector. 
        // I'm not doing it right now because I do not want to push a build task with the paths from my own system to the repo
        std::vector<bool> solenoids;

        // simulates ignition firing
        void ignite() {
            // TODO
        }
    
};