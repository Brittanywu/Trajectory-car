#pragma once

// This servo lib has some minor twicks made by der
#include "libraries/Servo/src/Servo.h"
#include "pinouts.h"

Servo verticalServo, horizontalServo;

void initServo() {
  verticalServo.attach(PINOUT_SERVO_VERT, -70, -100);
  horizontalServo.attach(PINOUT_SERVO_HORI, 60, 60);

  verticalServo.write(0);
  horizontalServo.write(90);
}

void servoTest() {
  for (int angle = 0; angle <= 180; angle++) {
    verticalServo.write(angle);
    delay(15);
  }

  for (int angle = 180; angle >= 0; angle--) {
    verticalServo.write(angle);
    delay(15);
  }
}

void servoPopup() { verticalServo.write(90); }

void servoLay() { verticalServo.write(0); }
