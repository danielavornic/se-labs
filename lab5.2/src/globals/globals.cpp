#include "globals.h"

PIDConfig pidConfig = {
    .kp = 0.06f,
    .ki = 0.00008f,
    .kd = 0.0059f,
    .minOutput = 5,
    .maxOutput = 255
};

SystemState state = {
    .speed = 0,
    .setpoint = 0,
    .output = 10,
    .lastError = 0,
    .integralError = 0
};
