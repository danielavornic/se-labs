#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

void formatFloat(char* buffer, float value);
void formatAngle(char* buffer, float angle);
void formatVoltage(char* buffer, float voltage);

#endif