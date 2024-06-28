/**
 * @file screen.hpp
 * @author mira
 * @brief This file creates code to initialize & clear the microcontroller screen so that it can be used for the rest of the program.
 * @version 0.1
 * @date 2024-06-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef SCREEN_HPP
#define SCREEN_HPP
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
Adafruit_ST7789 screen = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
void initialize();
void clear();
void initialize(){
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  delay(10);
  screen.init(135,240);
  screen.setRotation(3);
  clear();
  screen.setTextSize(2.5);
  screen.setTextColor(ST77XX_MAGENTA);
}

void clear() {
  screen.fillScreen(ST77XX_BLACK);
  screen.setCursor(0,10);
}
#endif // SCREEN_HPP