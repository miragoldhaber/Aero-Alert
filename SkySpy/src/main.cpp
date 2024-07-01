#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>
#include <gps.hpp>

void setup() {
  // put your setup code here, to run once:
  gps::gps_setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  gps::gps_loop();
}
