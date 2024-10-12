#pragma once

// Motor
const int PINOUT_MOTOR_L_DIR = 11; //左电机(IN3) 输出0  前进   输出1 后退
const int PINOUT_MOTOR_L_SPD = 10; //左电机PWM调速
const int PINOUT_MOTOR_R_DIR = 8;  // 右电机后退(IN1)  输出0  前进   输出1 后退
const int PINOUT_MOTOR_R_SPD = 9;  // 右电机PWM调速

// Track sensor
const int PINOUT_TRACK_SENSORS[5] = {13, 3, 6, 5, 4};

// Others
const int PINOUT_BUTTON_1 = A2; //定义按键 数字A2 接口
const int beep            = A3; //定义蜂鸣器 数字A3 接口

const int PINOUT_COLOR_SENSOR_ENABLE = 2;

const int PINOUT_SERVO_VERT = 12;
const int PINOUT_SERVO_HORI = 7;

// //colour
// #define s0 34
// #define s1 35
// #define s2 36
// #define s3 37
// #define sensorOut 00