#pragma once

#include "math.h"
#include "pinouts.h"

const int cSensorSensitivities[5] = {-2, -1, 0, 1, 2};

void initTrackSensors() {
  for (uint8_t i = 0; i < 5; i++) {
    pinMode(PINOUT_TRACK_SENSORS[i], INPUT);
  }
}

// Read digital status (0 / 1) back from a given sensor value
// DEBUG_MODE: white/near active
int getSensorValFromInput(int i) { return digitalRead(PINOUT_TRACK_SENSORS[i]); }

// USE_THIS: black/far active
int getSensorValFromInputInvert(int i) { return 1 - digitalRead(PINOUT_TRACK_SENSORS[i]); }

// Get sensor out (linear)
int getSensorDifferentialVal() {
  int finalVal = 0;

  for (int i = 0; i < 5; i++) {
    finalVal += cSensorSensitivities[i] * getSensorValFromInputInvert(i);
  }

  return clamp(finalVal, -2, 2);
}

int getLitSensorNum() {
  int finalVal = 0;
  for (int i = 0; i < 5; i++) {
    finalVal += getSensorValFromInput(i);
  }

  return finalVal;
}

int getDimSensorNum() {
  int finalVal = 0;
  for (int i = 0; i < 5; i++) {
    finalVal += getSensorValFromInputInvert(i);
  }

  return finalVal;
}

bool allSensorsAreLit() { return getDimSensorNum() == 0 ? true : false; }

bool allSensorsAreDim() { return getLitSensorNum() == 0 ? true : false; }

bool sensorIsBalanced() { return getSensorDifferentialVal() == 0; }