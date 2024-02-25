/* Name: rpl_sim_host.h
 * Descriptoion: interface for sim software that host the virtual states
 */
#ifndef COMM_H_
#define COMM_H_
namespace Rocket
{
  //State - These read state from the hardware (or sim)
  long millis(); // Returns milliseconds since flight computer startup
  long micros(); // Returns microseconds since flight computer startup

  //Position provider
  double* curr_coords();

  //BMP readings
  float get_bmp_pressure();
  float get_bmp_altitude();
  float get_bmp_temperature();

  //SD card status
  //sd_card_begin: true: hardware init success, false: init fail 
  bool get_sd_card_begin();
  //sd_card_open: true: file open success, false: file open false
  bool get_sd_card_open();

  //Xbee radio module
  // TODO: sending and receiving data through radio

  //Get solenoid state: true: open false: close
  bool get_solenoid_state1();
  bool get_solenoid_state2();

  //Get pressure transducer readings
  double get_pressure_transducer1();
  double get_pressure_transducer2();

  typedef struct{
  //Current xyz coordinates
  double curr_coords[3];

  //BMP readings
  float bmp_pressure;
  float bmp_altitude;
  float bmp_temperature;

  //SD card status
  bool sd_card_begin;
  bool sd_card_open;
  //Ematch status
  bool Ematch_state;

  //Solenoid state
  bool solenoid1_state; 
  bool solenoid2_state;

  //Pressure transducer readings
  double pressure_transducer1;
  double pressure_transducer2;
  }sim_struct;
}
#endif
// TO BE DETERMINED
//    File System + File object needs to be wrapped.
//    This might be hard.
// void cmd_fs_begin();
// bool cmd_fs_exists(String path);
// int cmd_fs_mkdir(String path);
// int cmd_fs_remove(String path);
// int cmd_fs_rmdir(String path);

  //RocketFile cmd_fs_open(String path, FileMode mode);
  // class RocketFile {
  //   // TODO: Wrap file object API: (https://www.arduino.cc/reference/en/libraries/sd/)
  // };