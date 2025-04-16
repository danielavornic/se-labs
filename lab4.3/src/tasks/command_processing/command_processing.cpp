#include "command_processing.h"
#include "../../config/config.h"
#include "../../globals/globals.h"
#include "../../motor/motor.h"
#include <Arduino.h>
#include <stdio.h>
#include <string.h>

// Task responsible for processing commands received via serial input
void commandProcessingTask(void* pvParameters)
{
    char command[MAX_COMMAND_LENGTH];
    int value;
    MotorCommand motorCmd;

    if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
        printf("\r\nPosition Control with Hysteresis Ready\n");
        printf("Current Position: %d, Setpoint: %d, Hysteresis: %d\n",
            motorGetPosition(), motorGetSetpoint(), motorGetHysteresis());
        printf("Commands:\n");
        printf("  setpoint [value] - Set target position\n");
        printf("  hysteresis [value] - Set hysteresis band\n");
        printf("  status - Show current status\n");
        printf("  stop - Stop the motor\n");
        printf("Position is automatically read from potentiometer \n");
        xSemaphoreGive(serialMutex);
    }

    while (1) {
        // Read command from serial input
        if (scanf(" %31s", command) == 1) {
            if (strcmp(command, "setpoint") == 0) {
                if (scanf("%d", &value) == 1) {
                    if (value >= 0 && value <= 100) {
                        // Send setpoint command to motor control task
                        motorCmd.type = MOTOR_SET_SETPOINT;
                        motorCmd.value = value;
                        xQueueSend(motorCommandQueue, &motorCmd, portMAX_DELAY);
                    } else {
                        if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
                            printf("Error: Setpoint must be between 0 and 100\n");
                            xSemaphoreGive(serialMutex);
                        }
                    }
                } else {
                    if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
                        printf("Error: Invalid setpoint value\n");
                        xSemaphoreGive(serialMutex);
                    }
                }
            } else if (strcmp(command, "hysteresis") == 0) {
                if (scanf("%d", &value) == 1) {
                    if (value > 0 && value <= 50) {
                        // Send hysteresis command to motor control task
                        motorCmd.type = MOTOR_SET_HYSTERESIS;
                        motorCmd.value = value;
                        xQueueSend(motorCommandQueue, &motorCmd, portMAX_DELAY);
                    } else {
                        if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
                            printf("Error: Hysteresis must be between 1 and 50\n");
                            xSemaphoreGive(serialMutex);
                        }
                    }
                } else {
                    if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
                        printf("Error: Invalid hysteresis value\n");
                        xSemaphoreGive(serialMutex);
                    }
                }
            } else if (strcmp(command, "stop") == 0) {
                // Send stop command to motor control task
                motorCmd.type = MOTOR_STOP;
                motorCmd.value = 0;
                xQueueSend(motorCommandQueue, &motorCmd, portMAX_DELAY);
            } else if (strcmp(command, "status") == 0) {
                // Print current status
                if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
                    printf("Current Position: %d, Setpoint: %d, Hysteresis: %d\n",
                        motorGetPosition(), motorGetSetpoint(), motorGetHysteresis());
                    xSemaphoreGive(serialMutex);
                }
            } else {
                // Handle unknown command
                if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
                    printf("Error: Unknown command '%s'\n", command);
                    printf("Available commands: setpoint, hysteresis, status, stop\n");
                    xSemaphoreGive(serialMutex);
                }
            }
        }
        // Small delay to prevent busy-waiting
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}