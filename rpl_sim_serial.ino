/* Name: rpl_sim_serial.ino
 * Descriptoion: Arduino application for sending and receive serial data
 */
#ifndef serial_send
#define serial_send
#include "C:/Users/Mark/Documents/GitHub/rpl-sim/rpl_sim_comm.h"
using namespace Rocket;

byte counter;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect

  counter = sizeof(sim);  
  }

}

void loop() {
  //Updating the struct

  //BMP readings
  sim.bmp_pressure = get_bmp_pressure();
  sim.bmp_altitude = get_bmp_altitude();
  sim.bmp_temperature = get_bmp_temperature();

  //SD card status
  sim.sd_card_begin = get_sd_card_begin();
  sim.sd_card_open = get_sd_card_open();

  //Ematch status
  sim.Ematch_state = get_Ematch_state();

  //Solenoid state
  sim.solenoid1_state = get_solenoid_state1();
  sim.solenoid2_state = get_solenoid_state2();

  //Pressure transducer readings
  sim.pressure_transducer1 = get_pressure_transducer1();
  sim.pressure_transducer2 = get_pressure_transducer2();

  //Sending serial data through struct by byte

  byte *str_ptr;
  str_ptr = (byte*) &sim;
  for (int i = 0; i < counter; ++i) {
    Serial.write(*str_ptr);
    str_ptr ++;
  }
  
  //End of sending packet

  //Receieving serial data
  // if (Serial.available()) {
  //   int inByte = Serial.read();
  // }

}
#endif serial_send