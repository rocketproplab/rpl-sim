#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"
// This is the one that uses ticks rather than timepoints

#include "PhoenixPositionProvider.h"
#include "FluidToEngineSubsystem.h"

using json = json;

const long MS_PER_TICK = 10; // arbitrary this should change to reflect a real 

int main(int argc, char **argv)
{
    /*
     * ARGUMENTS:
     *    Required:
     *    - file path where output file should be written
     *
     *    Optional
     *    - (-mt) sim mission time
     *    - (-et) sim end time
     */

    // parse args
    // handle no args passed in
    if(!(argc == 2 || argc == 4 || argc == 6)){
        help();
        return;
    }
    
    std::ofstream filePath(argv[1]);
    long endTime = -1;
    long missionTime = 0;
    try{
        for(int i = 3; i < argc; i+=2){
            if(argv[i-1] == "-et"){
                endTime = std::stol(argv[i]);
                if(endTime < 0){
                    help();
                    return;
                }
            }
            else if(argv[i-1] == "-mt"){
                missionTime = std::stol(argv[i]);
                if(missionTime < 0){
                    help();
                    return;
                }
            }
            else{
                help();
                return;
            }
        }
    }
    catch(std::invalid_argument const& ex){
        std::cout << "Please provide a valid argument" << std::endl;
        help();
        return;
    }
    catch(std::out_of_range const& ex){
        std::cout << "Argument value out of range" << std::endl;
        help();
        return;
    }
    
    if(!filePath){
        std::cout << "The file doesn't exist" << std::endl;
        return;
    }
    update(&filePath, msToTick(missionTime), msToTick(endTime));
}

void update(std::ofstream* filePath, long missionTime, long endTime)
{
    json j;

    PhoenixPositionProvider ppp;
    FluidToEngineSubsystem fs {};

    while (endTime < 0 || endTime > missionTime)
    {
        // TODO: insert process() from other tasks here
        ppp.process(tickToMs(missionTime), MS_PER_TICK);
        fs.process(0,0); //this is dummy arguments (double solenoid_to_engine_run_timer, double target)
        
        j = 
        {"tickheaderTODO",{
            {"PhoenixPositionProvider", {
                {"rocketstate", ppp.rocketState},
                {"currPos", ppp.getPosition()}
            }},
            {"FluidToEngineSubsystem", {
                {"status", fs.getStatus()},
                {"LNGsolenoidstate", fs.getSolenoidState(Solenoid::LNG_solenoid)},
                {"LOXsolenoidstate", fs.getSolenoidState(Solenoid::LOX_solenoid)},
            }}
        }};


        *filePath << j.dump(4);
        missionTime++;
    }
}

void help(){
    std::cout << "Runs RPL sim.\n sim [outputFilePath] -mt [simMissionTime = 0] -et [simEndTime = N/A]" << std::endl;
}

long msToTick(long ms){
    return ms / MS_PER_TICK;
}

long tickToMs(long tick){
    return tick * MS_PER_TICK;
}