#include "motor_control.h"
#include "../../globals/globals.h"
#include "../../motor/motor.h"
#include <stdio.h>

// Task responsible for controlling the motor based on commands received
void motorControlTask(void* pvParameters)
{
    MotorCommand command;

    while (1) {
        // Wait indefinitely for a command from the queue
        if (xQueueReceive(motorCommandQueue, &command, portMAX_DELAY) == pdTRUE) {
            switch (command.type) {
            case MOTOR_UPDATE_POSITION:
                // Update motor position based on potentiometer reading
                motorUpdatePosition(command.value);
                break;
            case MOTOR_SET_SETPOINT:
                // Set a new target position (setpoint)
                motorSetSetpoint(command.value);
                if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
                    printf("Setpoint updated to: %d\n", command.value);
                    xSemaphoreGive(serialMutex);
                }
                break;
            case MOTOR_SET_HYSTERESIS:
                // Set a new hysteresis value
                motorSetHysteresis(command.value);
                if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
                    printf("Hysteresis updated to: %d\n", command.value);
                    xSemaphoreGive(serialMutex);
                }
                break;
            case MOTOR_STOP:
                // Stop the motor immediately
                motorStop();
                if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
                    printf("Motor stopped\n");
                    xSemaphoreGive(serialMutex);
                }
                break;
            }
        }
    }
}