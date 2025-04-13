#include "tasks.h"
#include "../config/config.h"
#include "../globals/globals.h"
#include "../motor/motor.h"
#include <Arduino.h>
#include <stdio.h>
#include <string.h>

void commandProcessingTask(void* pvParameters)
{
    char command[MAX_COMMAND_LENGTH];
    int value;
    MotorCommand motorCmd;

    printf("\nPosition Control with Hysteresis Ready\n");
    printf("Current Position: %d, Setpoint: %d, Hysteresis: %d\n",
        motorGetPosition(), motorGetSetpoint(), motorGetHysteresis());
    printf("Commands:\n");
    printf("  position [value] - Update current position\n");
    printf("  setpoint [value] - Set target position\n");
    printf("  hysteresis [value] - Set hysteresis band\n");
    printf("  status - Show current status\n");
    printf("  stop - Stop the motor\n");

    while (1) {
        if (scanf(" %31s", command) == 1) {
            if (strcmp(command, "position") == 0) {
                if (scanf("%d", &value) == 1) {
                    motorCmd.type = MOTOR_UPDATE_POSITION;
                    motorCmd.value = value;
                    xQueueSend(motorCommandQueue, &motorCmd, portMAX_DELAY);
                } else {
                    printf("Error: Invalid position value\n");
                }
            } else if (strcmp(command, "setpoint") == 0) {
                if (scanf("%d", &value) == 1) {
                    motorCmd.type = MOTOR_SET_SETPOINT;
                    motorCmd.value = value;
                    xQueueSend(motorCommandQueue, &motorCmd, portMAX_DELAY);
                } else {
                    printf("Error: Invalid setpoint value\n");
                }
            } else if (strcmp(command, "hysteresis") == 0) {
                if (scanf("%d", &value) == 1) {
                    motorCmd.type = MOTOR_SET_HYSTERESIS;
                    motorCmd.value = value;
                    xQueueSend(motorCommandQueue, &motorCmd, portMAX_DELAY);
                } else {
                    printf("Error: Invalid hysteresis value\n");
                }
            } else if (strcmp(command, "stop") == 0) {
                motorCmd.type = MOTOR_STOP;
                motorCmd.value = 0;
                xQueueSend(motorCommandQueue, &motorCmd, portMAX_DELAY);
            } else if (strcmp(command, "status") == 0) {
                printf("Current Position: %d, Setpoint: %d, Hysteresis: %d\n",
                    motorGetPosition(), motorGetSetpoint(), motorGetHysteresis());
            } else {
                printf("Error: Unknown command '%s'\n", command);
                printf("Available commands: position, setpoint, hysteresis, status, stop\n");
            }
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void motorControlTask(void* pvParameters)
{
    MotorCommand command;

    while (1) {
        if (xQueueReceive(motorCommandQueue, &command, portMAX_DELAY) == pdTRUE) {
            switch (command.type) {
            case MOTOR_UPDATE_POSITION:
                motorUpdatePosition(command.value);
                printf("Position updated to: %d\n", command.value);
                break;
            case MOTOR_SET_SETPOINT:
                motorSetSetpoint(command.value);
                printf("Setpoint updated to: %d\n", command.value);
                break;
            case MOTOR_SET_HYSTERESIS:
                motorSetHysteresis(command.value);
                printf("Hysteresis updated to: %d\n", command.value);
                break;
            case MOTOR_STOP:
                motorStop();
                printf("Motor stopped\n");
                break;
            }
        }
    }
}

void createTasks()
{
    xTaskCreate(
        commandProcessingTask,
        "CommandProcessing",
        256,
        NULL,
        COMMAND_TASK_PRIORITY,
        NULL);

    xTaskCreate(
        motorControlTask,
        "MotorControl",
        128,
        NULL,
        MOTOR_TASK_PRIORITY,
        NULL);
}