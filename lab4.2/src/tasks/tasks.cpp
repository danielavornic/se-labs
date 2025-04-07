#include "tasks.h"
#include "../commands/commands.h"
#include "../config/config.h"
#include "../globals/globals.h"
#include "../motor/motor.h"
#include <Arduino.h>
#include <stdio.h>
#include <string.h>

void commandProcessingTask(void* pvParameters)
{
    char command[MAX_COMMAND_LENGTH];
    char subcommand[MAX_COMMAND_LENGTH];

    printf("Motor Control Ready\n");
    printf("Motor Speed: 0%%\n");

    while (1) {
        if (scanf(" %31s %31s", command, subcommand) == 2) {
            if (strcmp(command, "motor") == 0) {
                processMotorCommand(subcommand);
            } else {
                printf("Error: Unknown command '%s'\n", command);
                printf("Type 'motor help' for available commands\n");
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
            case MOTOR_SET_SPEED:
                motorSetSpeed(command.speed);
                printf("Motor Speed: %d%%\n", motorGetSpeed());
                break;
            case MOTOR_STOP:
                motorStop();
                printf("Motor Speed: 0%%\n");
                break;
            case MOTOR_INCREMENT:
                motorIncrement();
                printf("Motor Speed: %d%%\n", motorGetSpeed());
                break;
            case MOTOR_DECREMENT:
                motorDecrement();
                printf("Motor Speed: %d%%\n", motorGetSpeed());
                break;
            case MOTOR_SET_MAX:
                motorSetMax();
                printf("Motor Speed: %d%%\n", motorGetSpeed());
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