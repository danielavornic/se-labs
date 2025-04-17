#ifndef GLOBALS_H
#define GLOBALS_H

#include "../config/config.h"
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>

extern QueueHandle_t motorCommandQueue;

typedef struct {
    int currentPosition;
    int targetPosition;
} SystemStatus;

extern SystemStatus g_systemStatus;

extern SemaphoreHandle_t g_statusMutex;

void initGlobals(void);

#endif