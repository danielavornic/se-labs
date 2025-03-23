#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

struct JoystickReadings {
    float rawX;
    float rawY;
    float filteredX;
    float filteredY;
    float voltageX;
    float voltageY;
    bool button;
};

extern JoystickReadings sharedJoystick;
extern SemaphoreHandle_t serialMutex;
extern SemaphoreHandle_t joystickMutex;

void initGlobals();

#endif