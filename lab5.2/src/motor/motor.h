#ifndef MOTOR_H
#define MOTOR_H

#include "../globals/globals.h"
#include <Arduino.h>

#define MOTOR_IN1_PIN 3
#define MOTOR_IN2_PIN 4
#define MOTOR_ENA_PIN 5

#define MOTOR_MIN_PWM 40
#define MOTOR_MAX_PWM 255

#define MOTOR_DIR_CW 1
#define MOTOR_DIR_CCW 2
#define MOTOR_DIR_STOP 0

#define KP_DEFAULT 0.7
#define KI_DEFAULT 0.02
#define KD_DEFAULT 0.2

#define INTEGRAL_MIN -30.0f
#define INTEGRAL_MAX 30.0f
#define PID_OUTPUT_MIN -100.0f
#define PID_OUTPUT_MAX 100.0f
#define PID_OUTPUT_THRESHOLD 1.0f

#define INTEGRAL_RESET_THRESHOLD 20 // Reset integral when position error exceeds this value

void initMotor();
void motorUpdatePosition(int position);
void motorSetSetpoint(int setpoint);
void motorUpdatePID();
int motorGetSetpoint();
double motorGetPIDOutput();

#endif