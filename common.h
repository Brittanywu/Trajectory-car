#pragma once

#include "math.h"

inline void log(const char* c) { Serial.println(c); }

inline void checkpoint(int i = 0) {
  Serial.print("Checkpoint: ");
  Serial.println(i);
}