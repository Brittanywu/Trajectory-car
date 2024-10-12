// Hotkeys
// Ctrl Alt U       Upload
// Ctrl Shift P     Config

// Config commands:
// Arduino: Upload
// Arduino: Open / Close Serial Monitor
// Arduino: Send Text To Serial Port

// Car Battery MUST be on to upload program
// Press S1 button to start navigation, press again to finish

#include "bluetooth.h"
#include "button.h"
#include "carControlAdvanced.h"
#include "color.h"
#include "common.h"
#include "lcd.h"
#include "oled.h"
#include "pinouts.h"
#include "trackSensors.h"

// #include "libraries/SoftwareSerial/SoftwareSerial.h"

//////////// Global vals

bool naviOn = false;

void pinInit() {
  initTrackSensors();
  initWheels();
  initButtons();
  pinMode(12, OUTPUT);
}

void setup() {
  Serial.begin(9600); // Default value of VSCode
  Serial.println("hello!");

  pinInit();

  // This initialization inherently begins wire communication, which the color sensor also uses
  initOled();
  delay(200);
  // Color sensor must NOT be detected during oled initilization
  initColor();
  delay(200);

  oledClear();
  oledPrint("Good evening!");
  oledFlush();
  delay(1000);

  setBrightness(10);
  delay(100);
  setupBlankColor();
  setBrightness(0);
}

char val;

void readTtl() {
  char command = ' ';
  if (Serial.available()) //检测：【蓝牙】如果数据写入，则执行
  {
    command = Serial.read();
    if ((int)command == 13 || (int)command == 10) { // 排除干扰（换行符）
      command = ' ';
    }
  } else {
    command = ' ';
  }

  if (command != ' ') {
    Serial.println((int)command); // 打印
    // universalCommand = command;   // 刷新指令
  }
}

void loop() {
  while (!naviOn) {
    val = Serial.read();

    setBrightness(10);

    // navigation not started, get button -> start navigation
    if (getButtonHigh("-> TRACKING MODE")) {
      digitalWrite(12, HIGH);
      naviOn = true;

      oledClear();
      oledPrint("TRACKING MODE");
      oledFlush();
      delay(400);

      break;
    }

    getRGB();
    testSend();
  }

  while (naviOn) {
    // during navigation, get button -> stop navigation
    if (getButtonHigh("-> COLOR DETECTION")) {
      digitalWrite(12, LOW);
      stop(); // a stop command must be given
      naviOn = false;
      break;
    }

    navigation();
  }
}