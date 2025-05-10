#ifndef GLOBALS_H
#define GLOBALS_H

#include "../fsm/fsm.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>

extern SemaphoreHandle_t stateMutex;
extern QueueHandle_t buttonEventQueue;

extern volatile FSMState currentState;
extern volatile unsigned long stateStartTime;

void initGlobals();

#endif