#include "commands.h"
#include "../config/config.h"
#include "../globals/globals.h"
#include "../motor/motor.h"
#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void sendMotorCommand(MotorCommandType type, int8_t speed)
{
    MotorCommand cmd;
    cmd.type = type;
    cmd.speed = speed;
    xQueueSend(motorCommandQueue, &cmd, portMAX_DELAY);
}

void printHelp(void)
{
    printf("Motor commands:\n");
    printf("- motor stop: stop the motor\n");
    printf("- motor inc: increment motor speed\n");
    printf("- motor dec: decrement motor speed\n");
    printf("- motor max: set motor to maximum speed\n");
    printf("- motor set X: set motor speed to X%% (-100 to 100)\n");
}

void processMotorCommand(const char* subcommand)
{
    char command[MAX_COMMAND_LENGTH];
    int speed;

    strncpy(command, subcommand, MAX_COMMAND_LENGTH - 1);
    command[MAX_COMMAND_LENGTH - 1] = '\0';
    for (int i = 0; command[i]; i++) {
        command[i] = tolower(command[i]);
    }

    if (strcmp(command, "stop") == 0) {
        sendMotorCommand(MOTOR_STOP, 0);
        return;
    }

    if (strcmp(command, "inc") == 0) {
        sendMotorCommand(MOTOR_INCREMENT, 0);
        return;
    }

    if (strcmp(command, "dec") == 0) {
        sendMotorCommand(MOTOR_DECREMENT, 0);
        return;
    }

    if (strcmp(command, "max") == 0) {
        sendMotorCommand(MOTOR_SET_MAX, 0);
        return;
    }

    if (strcmp(command, "set") == 0) {
        if (scanf("%d", &speed) != 1) {
            printf("Error: Missing speed value\n");
            return;
        }

        if (speed < -100 || speed > 100) {
            printf("Error: Speed must be between -100 and 100\n");
            return;
        }

        sendMotorCommand(MOTOR_SET_SPEED, speed);
        return;
    }

    printf("Error: Unknown subcommand '%s'\n", command);
    printHelp();
}