//Arduino application for sending and receive serial data
#ifndef serial_send
#define serial_send
#include "rpl_sim_comm.h"
using namespace std;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect
  }
}

void loop() {
  //Sending serial data through struct
  Serial.write()



  //Receieving serial data
  if (Serial.available()) {
    int inByte = Serial.read();
    Serial.write(inByte, DEC);
  }





}
#endif serial_send