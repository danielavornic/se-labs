#include "globals.h"

QueueHandle_t motorCommandQueue;

void initGlobals(void)
{
    motorCommandQueue = xQueueCreate(5, sizeof(MotorCommand));
}