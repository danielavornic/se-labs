#include "globals.h"

QueueHandle_t motorCommandQueue;
SemaphoreHandle_t serialMutex;

void initGlobals(void)
{
    motorCommandQueue = xQueueCreate(5, sizeof(MotorCommand));
    serialMutex = xSemaphoreCreateMutex();
}