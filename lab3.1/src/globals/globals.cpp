#include "globals.h"
#include "config/config.h"

float sharedDistance = 0.0;
SemaphoreHandle_t serialMutex = NULL;
SemaphoreHandle_t distanceMutex = NULL;

void initGlobals()
{
    serialMutex = xSemaphoreCreateMutex();
    distanceMutex = xSemaphoreCreateMutex();
}