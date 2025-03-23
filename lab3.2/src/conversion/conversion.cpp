#include "conversion.h"

float adcToVoltage(int adcValue, float vRef, float adcResolution)
{
    return (adcValue * vRef) / adcResolution;
}

float voltageToAngle(float voltage, float vRef, float minAngle, float maxAngle)
{
    return ((voltage / vRef) * (maxAngle - minAngle)) + minAngle;
}

float angleToVoltage(float angle, float vRef, float minAngle, float maxAngle)
{
    // minAngle -> 0V
    // 0 degrees -> vRef/2
    // maxAngle -> vRef
    if (angle < 0)
        return (angle - minAngle) / (-minAngle) * (vRef / 2);

    return (vRef / 2) + (angle / maxAngle) * (vRef / 2);
}