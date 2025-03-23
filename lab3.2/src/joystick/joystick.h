#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>

struct JoystickData {
    float x_angle;
    float y_angle;
    bool button;
};

void initJoystick();
JoystickData getJoystickData();

#endif