#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>

extern SemaphoreHandle_t buttonSemaphore;
extern QueueHandle_t dataQueue;
extern SemaphoreHandle_t nMutex;
extern SemaphoreHandle_t serialMutex;

extern uint8_t N;

void initGlobals();

#endif