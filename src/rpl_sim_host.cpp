/* Name: rpl_sim_host.cpp
 * Descriptoion: implmentation of the rpl host
 */
#include "rpl_sim_host.h" 

// State - These read state from the hardware (or sim)

// Returns milliseconds since flight computer startup
namespace Rocket
{

long millis() {
    return 0;
}

// Returns microseconds since flight computer startup
long micros() {
    return 0;
}

//BMP readings
float get_bmp_pressure() {


    return 0;
}
float get_bmp_altitude() {
    return 0;
}
float get_bmp_temperature(){
    return 0;
}

//Xbee radio module
//TODO: sending and receiving data through radio

//Get solenoid(1) state: true: open false: close
bool get_solenoid_state1() {
    return false;
}
//Get solenoid(2) state: true: open false: close
bool get_solenoid_state2() {
    return false;
}

//Get pressure transducer(1) readings
double get_pressure_transducer1() {
    return 0;
}
//Get pressure transducer(2) readings
double get_pressure_transducer2() {
    return 0;
}



}
// TO BE DETERMINED
//    File System + File object needs to be wrapped.
//    This might be hard.
// void cmd_fs_begin();
// bool cmd_fs_exists(String path);
// int cmd_fs_mkdir(String path);
// int cmd_fs_remove(String path);
// int cmd_fs_rmdir(String path);