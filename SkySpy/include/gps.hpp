/**
 * @file gps.hpp
 * @author Megan
 * @brief Allows the device to locate itself and obtain the most accurate weather results, which is then transmitted to the user's mobile devices
 * @date 2024-06-26
 * @copyright Copyright (c) 2024
 */
#ifndef GPS_HPP
#define GPS_HPP

#include <Adafruit_GPS.h>
#include <coord.hpp>

namespace gps{
  #define GPSECHO false

  Adafruit_GPS GPS(&Wire);

  uint32_t timer = millis();


  void setup(){
    while (!Serial);  //only runs when the serial is ready 
    Serial.begin(115200);
    Serial.println("Adafruit I2C GPS library basic test!");

    GPS.begin(0x10);  
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
    GPS.sendCommand(PGCMD_ANTENNA);

    delay(1000);

    GPS.println(PMTK_Q_RELEASE);
  }

  void loop() {
    char c = GPS.read();
    if (GPSECHO)
      if (c) Serial.print(c);
    if (GPS.newNMEAreceived()) {
      Serial.println(GPS.lastNMEA()); 
    }

    if (millis() - timer > 2000) {
      timer = millis(); 
      Serial.print("\nTime: ");
      if (GPS.hour < 10) { Serial.print('0'); }
      Serial.print(GPS.hour, DEC); Serial.print(':');
      if (GPS.minute < 10) { Serial.print('0'); }
      Serial.print(GPS.minute, DEC); Serial.print(':');
      if (GPS.seconds < 10) { Serial.print('0'); }
      Serial.print(GPS.seconds, DEC); Serial.print('.');
      if (GPS.milliseconds < 10) {
        Serial.print("00");
      } else if (GPS.milliseconds > 9 && GPS.milliseconds < 100) {
        Serial.print("0");
      }
      Serial.println(GPS.milliseconds);
      Serial.print("Date: ");
      Serial.print(GPS.day, DEC); Serial.print('/');
      Serial.print(GPS.month, DEC); Serial.print("/20");
      Serial.println(GPS.year, DEC);
      Serial.print("Fix: "); Serial.print((int)GPS.fix);
      Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
      if (GPS.fix) {
        Serial.print("Location: ");
        Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
        Serial.print(", ");
        Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
        Serial.print("Speed (knots): "); Serial.println(GPS.speed);
        Serial.print("Angle: "); Serial.println(GPS.angle);
        Serial.print("Altitude: "); Serial.println(GPS.altitude);
        Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
      }
    }
  }

  coord query_GPS(){
  return{GPS.latitude, GPS.lat, GPS.longitude, GPS.lon, GPS.altitude};
  }
}
  #endif //GPS_HPP
