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
  float temperature_farenheit = (bme.temperature)*(1.8) + 32;
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
    void warnings();
    delay(30000);
  }
  void warnings(){
    if(temperature_farenheit <= -20){
      Serial.println("Stay indoors and bundle up in layers to avoid frostbite and possible death.");
    }
    if(temperature_farenheit > -20 && temperature_farenheit <= -10){
      Serial.println("Limit outdoor activities and wear heavy winter gear.");
    }
    if(temperature_farenheit > -10 && temperature_farenheit <= 0){
      Serial.println("Keep exposed skin to a minimum and stay dry.");
    }
    if(temperature_farenheit > 0 && temperature_farenheit <= 10){
      Serial.println("Dress in layers and be cautious of icy surfaces.");
    }
    if(temperature_farenheit > 10 && temperature_farenheit <= 20){
      Serial.println("Wear hats, gloves, and scarves to stay warm..");
    }
    if(temperature_farenheit > 20 && temperature_farenheit <= 30){
      Serial.println("A good time for hot drinks and cozy blankets.");
    }
    if(temperature_farenheit > 30 && temperature_farenheit <= 40){
      Serial.println("Perfect for a light jacket or a heavy jacket.");
    }
    if(temperature_farenheit > 40 && temperature_farenheit <= 50){
      Serial.println("A great day for a walk, just wear a jacket.");
    }
    if(temperature_farenheit > 50 && temperature_farenheit <= 60){
      Serial.println("Enjoy the outdoors, but keep a light sweater handy.");
    }
    if(temperature_farenheit > 60 && temperature_farenheit <= 70){
      Serial.println("Ideal weather for any outdoor activity.");
    }
    if(temperature_farenheit > 70 && temperature_farenheit <= 80){
      Serial.println("Great for a picnic or a hike.");
    }
    if(temperature_farenheit > 80 && temperature_farenheit <= 90){
      Serial.println("Stay hydrated and wear sunscreen.");
    }
    if(temperature_farenheit > 90 && temperature_farenheit <= 100){
      Serial.println("Limit strenuous activities and seek shade.");
    }
    if(temperature_farenheit > 100 && temperature_farenheit <= 110){
      Serial.println("Stay indoors during peak heat and drink plenty of water.");
    }
    if(temperature_farenheit > 110 && temperature_farenheit <= 120){
      Serial.println("Avoid outdoor activities and use air conditioning if possible.");
   }
    if(temperature_farenheit > 120){
      Serial.println("Stay in cool places, avoid the sun, and drink lots of fluids.  Extreme risk of heatstroke and possible death for sensitive groups");
    }
}
  
}
#endif //TEMPSENSOR_HPP