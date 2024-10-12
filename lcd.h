#pragma once

#include "common.h"
#include "libraries/LiquidCrystal_I2C1602V1/LiquidCrystal_I2C.h"
LiquidCrystal_I2C myLcd(0x27, 16, 2);

void initLcd() {
  myLcd.begin();
  checkpoint(9);
}

void lcdTestFunction1() {
  checkpoint(10);
  myLcd.noBacklight();
  delay(1000);
  myLcd.backlight();
  delay(1000);
}

void lcdTestFunction2() {
  checkpoint(11);
  myLcd.print("Hello, world!");
  delay(1000);
}