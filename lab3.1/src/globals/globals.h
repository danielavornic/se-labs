#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

extern float sharedDistance;
extern SemaphoreHandle_t serialMutex;
extern SemaphoreHandle_t distanceMutex;

void initGlobals();

#endif