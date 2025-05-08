#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>

struct PIDConfig {
    float kp;
    float ki;
    float kd;
    int minOutput;
    int maxOutput;
};

struct SystemState {
    int speed;
    int setpoint;
    int output;
    int lastError;
    long integralError;
};

extern PIDConfig pidConfig;
extern SystemState state;

#endif
