#include "commands.h"
#include "../config/config.h"
#include "../motor/motor.h"
#include <Arduino.h>
#include <stdio.h>
#include <string.h>

static void handleSetCommand(void)
{
    int value;
    if (scanf("%d", &value) != 1) {
        printf("Error: Missing speed value. Usage: motor set [-100..100]\n");
        return;
    }

    if (value < -100 || value > 100) {
        printf("Error: Speed must be between -100 and 100\n");
        return;
    }

    motorSetSpeed(value);
    printf("Motor Speed: %d%%\n", motorGetSpeed());
}

static void handleIncrementCommand(void)
{
    int8_t currentSpeed = motorGetSpeed();
    if (currentSpeed >= 100) {
        printf("Error: Already at maximum speed (100%%)\n");
        return;
    }

    motorIncrement();
    printf("Motor Speed: %d%%\n", motorGetSpeed());
}

static void handleDecrementCommand(void)
{
    int8_t currentSpeed = motorGetSpeed();
    if (currentSpeed <= -100) {
        printf("Error: Already at minimum speed (-100%%)\n");
        return;
    }

    motorDecrement();
    printf("Motor Speed: %d%%\n", motorGetSpeed());
}

void printHelp(void)
{
    printf("Available commands:\n");
    printf("  motor set [-100..100] - Set motor speed and direction\n");
    printf("  motor stop          - Stop the motor\n");
    printf("  motor max           - Set maximum speed in current direction\n");
    printf("  motor inc           - Increase speed by 10%%\n");
    printf("  motor dec           - Decrease speed by 10%%\n");
    printf("  motor status        - Show detailed motor status\n");
    printf("  motor help          - Show this help message\n");
}

void processMotorCommand(const char* subcommand)
{
    if (strcmp(subcommand, "set") == 0) {
        handleSetCommand();
    } else if (strcmp(subcommand, "stop") == 0) {
        motorStop();
        printf("Motor stopped. Speed: 0%%\n");
    } else if (strcmp(subcommand, "max") == 0) {
        motorSetMax();
        printf("Motor set to maximum speed: %d%%\n", motorGetSpeed());
    } else if (strcmp(subcommand, "inc") == 0) {
        handleIncrementCommand();
    } else if (strcmp(subcommand, "dec") == 0) {
        handleDecrementCommand();
    } else if (strcmp(subcommand, "help") == 0) {
        printHelp();
    } else {
        printf("Error: Unknown command '%s'\n", subcommand);
        printf("Type 'motor help' for available commands\n");
    }
}