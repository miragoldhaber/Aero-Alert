/**
 * @file tempsensor.hpp
 * @author mira
 * @brief This sets up the temperature sensor, and makes it so that the temperature, humidity, and gas levels are printed onto the microcontroller screen every 30 seconds.
 * @version 0.1
 * @date 2024-06-28
 * @copyright Copyright (c) 2024
 */
#ifndef TEMPSENSOR_HPP
#define TEMPSENSOR_HPP
#include <screen.hpp>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
Adafruit_BME680 bme;
namespace temperature{
  void prepare() {
    initialize();
    while (!Serial);
    Serial.println(F("BME680 async test"));
    if (!bme.begin()) {
      screen.println(F("Could not find a valid BME680 sensor, check wiring!"));
      while (1);
    }
    // Set up oversampling and filter initialization
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150); // 320*C for 150 ms
  }
  void display() {
    clear();
    if (! bme.performReading()) {
      screen.println("Failed to perform reading :(");
      return;
    }
    screen.print("Temperature = ");
    screen.print(bme.temperature);
    screen.println(" *C");
    screen.print("Temperature = ");
    screen.print((bme.temperature)*(1.8) + 32);
    screen.println(" *F");
    screen.print("Humidity = ");
    screen.print(bme.humidity);
    screen.println(" %");
    screen.print("Gas = ");
    screen.print(bme.gas_resistance / 1000.0);
    screen.println(" KOhms");
    screen.println();
    delay(30000);
  }
}
#endif //TEMPSENSOR_HPP