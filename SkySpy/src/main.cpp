#include <Arduino.h>
#include <tempsensor.hpp>
#include <adafruit_io.hpp>
#include <screen.hpp>
#include <GPS.hpp>
#include <coords.hpp>
#include <AQI.hpp>

void setup(){
  Serial.begin(115200);
  while(!Serial);
  temperature::prepare();
  gps::setup();
  AQI::init();
  adafruit_io::attempt_connection();
}
void loop() {
  gps::loop();
  temperature::display();
  AQI::display();
  adafruit_io::run();
  delay(5000);

  if (adafruit_io::IO_connected) {
  adafruit_io::save_to_IOT();
  }

  // if time add feed for the date
  // see if they can be connected -- make sure they aren't all just individual
  //figure out all of coordinates stuff once i have megans code
  // maybe make this in another file (io save or smth), bc main is getting long
}
