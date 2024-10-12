#pragma once

#include "math.h"
#include "pinouts.h"
#include "trackSensors.h"

const int cPowerStart       = 200;
const int cMaxSpeedStraight = 80;
const int cMaxSpeedTurn     = 100;

void stop();

// Controls 4 motor's direction and speed
// The range of power is from 0 to 255
void motorControl(bool lForward, bool rForward, int lPower, int rPower) {
  clamp(lPower, 0, 255);
  clamp(rPower, 0, 255);

  if (lForward)
    digitalWrite(PINOUT_MOTOR_L_DIR, LOW);
  else
    digitalWrite(PINOUT_MOTOR_L_DIR, HIGH);

  if (rForward)
    digitalWrite(PINOUT_MOTOR_R_DIR, LOW);
  else
    digitalWrite(PINOUT_MOTOR_R_DIR, HIGH);

  // Power start for DC motor
  if (lPower > 0)
    analogWrite(PINOUT_MOTOR_L_SPD, cPowerStart);
  if (rPower > 0)
    analogWrite(PINOUT_MOTOR_R_SPD, cPowerStart);
  // delay(5);

  analogWrite(PINOUT_MOTOR_L_SPD, lPower);
  analogWrite(PINOUT_MOTOR_R_SPD, rPower);
}

void initWheels() {
  pinMode(PINOUT_MOTOR_L_DIR, OUTPUT); // PIN 8 8脚无PWM功能
  pinMode(PINOUT_MOTOR_R_DIR, OUTPUT); // PIN 11 (PWM)
  pinMode(PINOUT_MOTOR_L_SPD, OUTPUT); // PIN 9 (PWM)
  pinMode(PINOUT_MOTOR_R_SPD, OUTPUT); // PIN 10 (PWM)

  stop();
}

void goStraight() { motorControl(true, true, cMaxSpeedStraight, cMaxSpeedStraight); }

void goStraightBackwards() { motorControl(false, false, cMaxSpeedStraight, cMaxSpeedStraight); }

void spinLeft() { motorControl(false, true, cMaxSpeedTurn, cMaxSpeedTurn); }

void spinRight() { motorControl(true, false, cMaxSpeedTurn, cMaxSpeedTurn); }

void stop() { motorControl(true, true, 0, 0); }

// Deprecated: Differential control
// Speed: 0 - 255; Direction: -255 - 255
// void goForward(int direction, int speed = cMaxSpeed) {
//   int lPwmVal = 0;
//   int rPwmVal = 0;

//   digitalWrite(PINOUT_MOTOR_L_DIR, LOW); // 左电机前进
//   digitalWrite(PINOUT_MOTOR_R_DIR, LOW); // 右电机前进

//   if (direction < 0) {
//     rPwmVal = 255 - direction;
//     lPwmVal = 255 + direction;
//   }

//   if (direction >= 0) {
//     lPwmVal = 255 + direction;
//     rPwmVal = 255 - direction;
//   }

//   lerp(lPwmVal, speed);
//   lerp(rPwmVal, speed);

//   Serial.print(lPwmVal);
//   Serial.print(" ");
//   Serial.print(rPwmVal);
//   Serial.println();

//   analogWrite(PINOUT_MOTOR_L_SPD, lPwmVal);
//   analogWrite(PINOUT_MOTOR_R_SPD, rPwmVal);
// }