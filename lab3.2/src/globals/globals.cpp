#include "globals.h"
#include "config/config.h"

JoystickReadings sharedJoystick = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, false };
SemaphoreHandle_t serialMutex = NULL;
SemaphoreHandle_t joystickMutex = NULL;

void initGlobals()
{
    serialMutex = xSemaphoreCreateMutex();
    joystickMutex = xSemaphoreCreateMutex();
}