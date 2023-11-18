//Interface for Arduino communication layer

namespace Rocket // TODO: Better Namespace name.
{
  // State - These read state from the hardware (or sim)
  long millis(); // Returns milliseconds since flight computer startup
  long micros(); // Returns microseconds since flight computer startup

  //BMP readings
  float state_get_bmp_pressure();
  float state_get_bmp_altitude();
  float state_get_bmp_temperature();

  //SD card status
  //sd_card_begin: true: hardware init success, false: init fail 
  bool sd_card_begin();
  //sd_card_open: true: file open success, false: file open false
  bool sd_card_open();

  //Ematch status: true: high, false: low
  bool Ematch_state();

  //Servo readings


  // ... and so on.

  // Commands - These tell the hardware (or sim) to DO something
  void cmd_set_solenoid_actuation(int index, bool isOpen);
  void cmd_ingite_parachute_ematch();

  //    File System + File object needs to be wrapped.
  //    This might be hard.
  void cmd_fs_begin();
  bool cmd_fs_exists(String path);
  int cmd_fs_mkdir(String path);
  int cmd_fs_remove(String path);
  int cmd_fs_rmdir(String path);
  RocketFile cmd_fs_open(String path, FileMode mode);

  class RocketFile {
    // TODO: Wrap file object API: (https://www.arduino.cc/reference/en/libraries/sd/)

  };

  struct {
    //BMP readings
    float bmp_pressure = state_get_bmp_pressure();
    float bmp_altitude = state_get_bmp_altitude();
    float bmp_temperature = state_get_bmp_temperature();

    //SD card status
    bool sd_card_begin = sd_card_begin();
    bool sd_card_open = sd_card_open();

    //Ematch status
    bool Ematch_state;

    //Servos





  } sim_struct;


}