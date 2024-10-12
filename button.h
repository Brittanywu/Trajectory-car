#include "oled.h"
#include "pinouts.h"

void initButtons() { pinMode(PINOUT_BUTTON_1, INPUT); }

bool getButtonHigh(const char* hint = "RELEASE TO CONTINUE") {
  if (digitalRead(PINOUT_BUTTON_1)) {
    delay(10);
    if (digitalRead(PINOUT_BUTTON_1)) {
      oledClear();
      oledPrint("BUTTON PRESSED", 1);
      oledPrint(hint, 2);
      oledFlush();
      while (digitalRead(PINOUT_BUTTON_1)) {
      }

      oledClear();
      oledFlush();
      return true;
    }
  }
  return false;
}

bool buttonPressed() { getButtonHigh(); }