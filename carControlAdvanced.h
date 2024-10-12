#pragma once

#include "bluetooth.h"
#include "carControlBasic.h"
#include "color.h"
#include "colourSensor.h"
#include "oled.h"
#include "trackSensors.h"

bool isOnCourse               = false;
bool inBusStop                = false;                     // Unused
const int cDirectionOffset[5] = {-200, -100, 0, 100, 200}; // Unused

int countColorA = 0;
int countColorB = 0;
int R;
int G;
int B;
int count    = 0;
int location = 0;

// byte temperturechar[8]={
//   0b10000,
//   0b00110,
//   0b01001,
//   0b01000,
//   0b01000,
//   0b01001,
//   0b00110,
//   0b00000,
// };

void detectionPlan() {
  location++; // location starts from 1

  oledClear();
  oledPrint("STOPPED", 0);
  oledFlush();
  delay(1000);

  setBrightness(10);

  oledClear();
  oledPrint("STOPPED", 0);
  oledPrint("DETECTING.", 1);
  oledFlush();
  delay(500);

  oledClear();
  oledPrint("STOPPED", 0);
  oledPrint("DETECTING..", 1);
  oledFlush();
  delay(500);

  oledClear();
  oledPrint("STOPPED", 0);
  oledPrint("DETECTING...", 1);
  oledFlush();
  delay(500);

  int colorGot = getRGB();
  setBrightness(0);
  sendInfo(colorGot, location);
  delay(2000);

  oledClear();
  oledPrint(location, "LOCATION", 1);
  oledFlush();
  delay(200);

  oledClear();
  oledPrint("STOPPED", 0);
  oledPrint("INFO SAVED", 1);
  oledFlush();
  delay(2000);
}

void navigation() {
  if (allSensorsAreDim()) {
    isOnCourse = false;
    inBusStop  = true;

    stop();

    detectionPlan();

    // Leaving the bug stop
    while (allSensorsAreDim()) {
      goStraight();
    }

    inBusStop = false;
    return;
  }

  if (allSensorsAreLit()) {
    isOnCourse = false;
    goStraightBackwards();
    return;
  }

  if (sensorIsBalanced()) {
    isOnCourse = true;
    goStraight();
    return;
  }

  // Off course status is detected, we stop the car first
  if (isOnCourse == true) {
    stop();
    delay(200);
  }
  isOnCourse = false;

  int sensorDifferentialVal = getSensorDifferentialVal();
  if (sensorDifferentialVal < 0) {
    spinLeft();
    return;
  }
  if (sensorDifferentialVal > 0) {
    spinRight();
    return;
  }
}
