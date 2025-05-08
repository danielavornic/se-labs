#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

#define ENCODER_A 2
#define ENCODER_CALIBRATION 19.1

void initEncoder();
int measureSpeed();

#endif
