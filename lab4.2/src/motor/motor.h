#ifndef MOTOR_H
#define MOTOR_H

#include "../config/config.h"
#include <Arduino.h>

void motorInit();
void motorSetSpeed(int8_t speed);
void motorStop();
int8_t motorGetSpeed();
void motorIncrement();
void motorDecrement();
void motorSetMax();

#endif