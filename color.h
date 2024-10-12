#pragma once

#include "common.h"
#include "math.h"
#include "oled.h"
#include "pinouts.h"
#include <Wire.h>

#define COLOR_RED 0
#define COLOR_GREEN 1
#define COLOR_BLUE 2
#define COLOR_YELLOW 3
#define COLOR_EMPTY 4
#define COLOR_INVALID 5

const char* colorLookupArray[6] = {"RED", "GREEN", "BLUE", "YELLOW", "EMPTY", "INVALID"};

const uint8_t colorSensorAddr  = 0x5a;
const uint8_t colorBufferAddr  = 0x00;
const long minimumSamplingTime = 100;

uint8_t buff[6];
uint16_t rgb[3];
int usingRgb[3];

uint16_t blankRGB[3];

TwoWire* wire = &Wire;

void setBrightness(uint8_t);
bool requestBuffer(uint8_t deviceAddr, uint8_t bufferAddr, uint8_t* buffer, uint8_t bufferSize);
int parseColor();
void getColor();
int getRGB();

void initColor() {
  pinMode(PINOUT_COLOR_SENSOR_ENABLE, OUTPUT);
  digitalWrite(PINOUT_COLOR_SENSOR_ENABLE, HIGH);
  setBrightness(0);
}

void setupBlankColor() {

  while (true) {
    getColor();
    if (!(rgb[0] == 0 && rgb[1] == 0 && rgb[2] == 0))
      break;
    delay(100);
  }

  // Save value
  memcpy(blankRGB, rgb, sizeof(rgb[0]) * 3);

  oledClear();
  oledPrint(static_cast<int>(blankRGB[0]), "rawR", 0);
  oledPrint(static_cast<int>(blankRGB[1]), "rawG", 1);
  oledPrint(static_cast<int>(blankRGB[2]), "rawB", 2);
  oledFlush();
}

// Write communication test
void testColor() {
  for (int b = 0; b <= 10; b++) {
    setBrightness(b);
    delay(200);
  }
}

// (0 -> 10) (dim -> light)
void setBrightness(uint8_t brightness) {
  clamp(brightness, static_cast<uint8_t>(0), static_cast<uint8_t>(10));

  brightness            = 10 - brightness; // invert brightness to meet the module's need :(
  uint8_t configCommand = 0x00;

  configCommand |= brightness << 4;

  wire->beginTransmission(colorSensorAddr); // Call device
  wire->write(0x10);                        // Ask to Config
  wire->write(configCommand);               // Actural command
  wire->endTransmission();                  // Stop transmission
}

void getColor() {
  memset(buff, 0, 6);

  for (uint8_t i = 0; i < 6; i++) {
    requestBuffer(colorSensorAddr, colorBufferAddr + i, buff + i, 1);
    delay(10);
  }

  for (int i = 0; i < 3; i++) {
    rgb[i] = (*(buff + i * 2) << 8) & 0xff00;
    rgb[i] |= *(buff + i * 2 + 1);
  }
}

bool requestBuffer(uint8_t deviceAddr, uint8_t bufferAddr, uint8_t* buffer, uint8_t bufferSize) {
  wire->beginTransmission(deviceAddr); // Call device
  wire->write(bufferAddr);             // Ask to Config
  wire->endTransmission(false);        // Stop transmission

  wire->requestFrom(deviceAddr, bufferSize);
  wire->readBytes(buffer, bufferSize);

  wire->endTransmission(); // Stop transmission

  return true;
}

int getRGB() {
  getColor();

  for (int i = 0; i < 3; i++) {
    usingRgb[i] = (static_cast<int>(rgb[i]) - static_cast<int>(blankRGB[i]) > 0)
                      ? (static_cast<int>(rgb[i]) - static_cast<int>(blankRGB[i]))
                      : 0;
  }

  int colorGot = parseColor();

  oledClear();
  oledPrint(static_cast<int>(usingRgb[0]), "R", 0);
  oledPrint(static_cast<int>(usingRgb[1]), "G", 1);
  oledPrint(static_cast<int>(usingRgb[2]), "B", 2);
  oledPrint(colorLookupArray[colorGot], 3);
  oledFlush();

  return colorGot;
}

int parseColor() {
  uint16_t maxVal  = 0;
  uint16_t largest = 0;

  for (int i = 0; i < 3; i++) {
    if (usingRgb[i] > maxVal) {
      maxVal  = usingRgb[i];
      largest = i;
    }
  }

  if (maxVal < 100)
    return COLOR_EMPTY;

  switch (largest) {
  case 0:
    if ((float)usingRgb[1] / (float)maxVal > 0.8f)
      return COLOR_YELLOW;
    return COLOR_RED;
  case 1:
    if ((float)usingRgb[0] / (float)maxVal > 0.8f)
      return COLOR_YELLOW;
    return COLOR_GREEN;
  case 2:
    return COLOR_BLUE;
  }
}