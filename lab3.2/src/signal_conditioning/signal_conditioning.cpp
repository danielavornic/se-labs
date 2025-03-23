#include "signal_conditioning.h"
#include "../config/config.h"
#include <Arduino.h>

static float previousValues[AXIS_COUNT][WINDOW_SIZE] = { { 0 } };
static int currentIndex[AXIS_COUNT] = { 0 };
static bool bufferFilled[AXIS_COUNT] = { false };
static float lastValidValues[AXIS_COUNT] = { 0 };

float saltAndPepperFilter(float value, int axis)
{
    if (lastValidValues[axis] == 0) {
        lastValidValues[axis] = value;
        return value;
    }

    if (value >= JOYSTICK_MAX_ANGLE - 5.0f || value <= JOYSTICK_MIN_ANGLE + 5.0f) {
        lastValidValues[axis] = value;
        return value;
    }

    float difference = abs(value - lastValidValues[axis]);

    if (difference > SALT_AND_PEPPER_FILTER_THRESHOLD) {
        // if the new value is between min and max angles, it might be valid
        if (value >= JOYSTICK_MIN_ANGLE && value <= JOYSTICK_MAX_ANGLE) {
            lastValidValues[axis] = value;
            return value;
        }
        return lastValidValues[axis];
    }

    lastValidValues[axis] = value;
    return value;
}

float weightedAverageFilter(float value, int axis)
{
    previousValues[axis][currentIndex[axis]] = value;
    currentIndex[axis] = (currentIndex[axis] + 1) % WINDOW_SIZE;

    if (currentIndex[axis] == 0)
        bufferFilled[axis] = true;

    if (!bufferFilled[axis])
        return value;

    float sum = 0;
    for (int i = 0; i < WINDOW_SIZE; i++) {
        sum += previousValues[axis][i];
    }

    return sum / WINDOW_SIZE;
}

float applyPhysicalLimits(float value, float minValue, float maxValue)
{
    if (value < minValue)
        return minValue;
    if (value > maxValue)
        return maxValue;
    return value;
}