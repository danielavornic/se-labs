#ifndef GLOBALS_H
#define GLOBALS_H

#include "../config/config.h"
#include <Arduino_FreeRTOS.h>
#include <queue.h>

extern QueueHandle_t motorCommandQueue;

void initGlobals(void);

#endif