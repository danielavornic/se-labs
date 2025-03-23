#ifndef CONVERSION_H
#define CONVERSION_H

#include <Arduino.h>

float adcToVoltage(int adcValue, float vRef, float adcResolution);

float voltageToAngle(float voltage, float vRef, float minAngle, float maxAngle);
float angleToVoltage(float angle, float vRef, float minAngle, float maxAngle);

#endif 