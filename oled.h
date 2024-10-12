#pragma once

#include "libraries/Adafruit_SSD1306/Adafruit_SSD1306.h"

Adafruit_SSD1306 display(-1);
const int cLineSpacing(8);

void initOled() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.clearDisplay();
  display.display();

  display.setTextColor(WHITE, BLACK);
  display.setCursor(0, 0);
  display.println("setup-ed!");
  display.display();
}

// clear buffer
void oledClear() { display.clearDisplay(); }

/// Print functions: save text into temp buffer
// Print plain text into a certain row
void oledPrint(const char* str, const int row = 0) {
  display.setCursor(0, cLineSpacing * row);
  display.println(str);
}

// Print num with hint (or without)
void oledPrint(const int val, const char* hint = nullptr, const int row = 0) {
  display.setCursor(0, cLineSpacing * row);
  char str[100];
  if (hint)
    sprintf(str, "%s: %d", hint, val);
  else
    sprintf(str, "%d", val);
  display.println(str);
}

// FIXME: floating num won't show up!
// Print num with hint (or without)
void oledPrint(const float val, const char* hint = nullptr, const int row = 0) {
  display.setCursor(0, cLineSpacing * row);
  char str[100];
  if (hint)
    sprintf(str, "%s: %.2f", hint, val);
  else
    sprintf(str, "%.2f", val);
  display.println(str);
}

// Dump buffer to screen (the only real function)
void oledFlush() { display.display(); }

void examples() {
  // Print a smiling face on the first row
  oledClear();
  oledPrint(":)", 0);
  oledFlush();
  delay(1000);

  // Print der's birthday on the second row
  oledClear();
  oledPrint(716, "birthday", 1);
  oledFlush();
  delay(1000);

  // Print der's birthday without hint
  oledClear();
  oledPrint(716, nullptr, 2); // or oledPrint(716);
  oledFlush();
  delay(1000);
}

// Function to ensure the oled is working properly
void testOled() {
  for (int n = 0; n < 3; n++) {
    oledClear();
    oledPrint(n + 1, "testing", 1);
    oledFlush();
    delay(500);
  }
}