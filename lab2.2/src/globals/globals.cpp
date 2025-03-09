#include "globals.h"
#include "config/config.h"

SemaphoreHandle_t buttonSemaphore = NULL;
QueueHandle_t dataQueue = NULL;
SemaphoreHandle_t nMutex = NULL;
SemaphoreHandle_t serialMutex = NULL;
uint8_t N = 0;

void initGlobals()
{
    buttonSemaphore = xSemaphoreCreateBinary();
    dataQueue = xQueueCreate(QUEUE_SIZE, sizeof(uint8_t));
    nMutex = xSemaphoreCreateMutex();
    serialMutex = xSemaphoreCreateMutex();
    N = 0;
}