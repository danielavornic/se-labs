#include "globals.h"

SemaphoreHandle_t stateMutex;
QueueHandle_t buttonEventQueue;

volatile FSMState currentState = STATE_EAST_GREEN;
volatile unsigned long stateStartTime = 0;

void initGlobals()
{
    stateMutex = xSemaphoreCreateMutex();
    buttonEventQueue = xQueueCreate(1, sizeof(ButtonPress));

    xSemaphoreGive(stateMutex);
    enterEastGreen();
    stateStartTime = millis();
}