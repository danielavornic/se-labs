#ifndef MOTOR_H
#define MOTOR_H

#include "../globals/globals.h"
#include <Arduino.h>

#define MOTOR_ENABLE_PIN 3
#define MOTOR_IN1_PIN 5
#define MOTOR_IN2_PIN 4

void initMotor();
void applyMotorOutput();

#endif
