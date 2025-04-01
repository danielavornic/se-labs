#ifndef GLOBALS_H
#define GLOBALS_H

#include "../config/config.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

struct Command {
    char command[MAX_COMMAND_LENGTH];
    char modifier[MAX_COMMAND_LENGTH];
};

extern SemaphoreHandle_t serialMutex;

void initGlobals();

#endif