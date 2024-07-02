/**
 * @file AQI.hpp
 * @author mira
 * @brief Takes the raw data from the gas sensor and prints that measurement to the Serial
 * @version 0.1
 * @date 2024-07-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef AQI_HPP
#define AQI_HPP
#include "Adafruit_SGP40.h"
#include "Adafruit_SHT31.h"
Adafruit_SGP40 sgp;
Adafruit_SHT31 sht31;
namespace AQI{
    void init() {
        Serial.begin(115200);
        while (!Serial) { delay(10); } // Wait for serial console to open!
        Serial.println("SGP40 test");
        if (! sgp.begin()){
            Serial.println("SGP40 sensor not found :(");
            while (1);
        }
        Serial.print("Found SGP40 serial #");
        Serial.print(sgp.serialnumber[0], HEX);
        Serial.print(sgp.serialnumber[1], HEX);
        Serial.println(sgp.serialnumber[2], HEX);
    }

    int counter = 0;
    void display() {
        uint16_t raw;
        raw = sgp.measureRaw();
        Serial.print("Measurement: ");
        Serial.println(raw);
        delay(1000);
    }
}
#endif // AQI_HPP