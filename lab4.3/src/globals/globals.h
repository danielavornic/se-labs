#ifndef GLOBALS_H
#define GLOBALS_H

#include "../config/config.h"
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>

extern QueueHandle_t motorCommandQueue;
extern SemaphoreHandle_t serialMutex;

void initGlobals(void);

#endif