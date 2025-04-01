#include "globals.h"
#include "config/config.h"

SemaphoreHandle_t serialMutex = NULL;

void initGlobals()
{
    serialMutex = xSemaphoreCreateMutex();
}