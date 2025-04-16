#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino_FreeRTOS.h>

// Function declaration for the motor control task
void motorControlTask(void* pvParameters);

#endif // MOTOR_CONTROL_H