#ifndef MOTOR_H
#define MOTOR_H

#include "../config/config.h"
#include <Arduino.h>

#define MOTOR_POWER 50
#define DEFAULT_SETPOINT 0
#define DEFAULT_HYSTERESIS 5

void motorInit();
void motorUpdatePosition(int position);
void motorSetSetpoint(int setpoint);
void motorStop();
int motorGetPosition();
int motorGetSetpoint();
void motorSetHysteresis(int value);
int motorGetHysteresis();

#endif