#include "tasks.h"
#include "../commands/commands.h"
#include "../motor/motor.h"
#include <Arduino.h>
#include <stdio.h>
#include <string.h>

void motorControlTask(void* pvParameters)
{
    char command[MAX_COMMAND_LENGTH];
    char subcommand[MAX_COMMAND_LENGTH];

    printf("Motor Control Ready\n");
    printf("Motor Speed: 0%%\n");
    printf("Type 'motor help' for available commands\n");

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

void createTasks()
{
    xTaskCreate(
        motorControlTask,
        "MotorControl",
        256,
        NULL,
        COMMAND_TASK_PRIORITY,
        NULL);
}