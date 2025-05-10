#include "tasks.h"
#include "../fsm/fsm.h"
#include <limits.h>

extern const StateConfig stateConfig[];

void createTasks()
{
    xTaskCreate(vTrafficLightTask, "TrafficLight", 128, NULL, 1, NULL);
    xTaskCreate(vButtonCheckTask, "ButtonCheck", 128, NULL, 2, NULL);
    xTaskCreate(vStateUpdateTask, "StateUpdate", 128, NULL, 1, NULL);
}

void vTrafficLightTask(void* pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (1) {
        if (xSemaphoreTake(stateMutex, portMAX_DELAY) == pdTRUE) {
            stateConfig[currentState].update();
            xSemaphoreGive(stateMutex);
        }
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(50));
    }
}

void vButtonCheckTask(void* pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (1) {
        ButtonPress buttonEvent = BUTTON_NONE;

        if (isButtonPressed()) {
            buttonEvent = BUTTON_NORTH;
        } else if (isNightModeButtonPressed()) {
            buttonEvent = BUTTON_NIGHT_MODE;
        }

        if (buttonEvent != BUTTON_NONE) {
            xQueueSend(buttonEventQueue, &buttonEvent, 0);
        }

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(50));
    }
}

void vStateUpdateTask(void* pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    ButtonPress buttonEvent;

    while (1) {
        bool timeExpired = false;
        ButtonPress receivedEvent = BUTTON_NONE;

        if (xQueueReceive(buttonEventQueue, &buttonEvent, 0) == pdTRUE) {
            receivedEvent = buttonEvent;
        }

        if (xSemaphoreTake(stateMutex, portMAX_DELAY) == pdTRUE) {
            timeExpired = (millis() - stateStartTime) >= stateConfig[currentState].duration;

            if (timeExpired || receivedEvent != BUTTON_NONE) {
                FSMState nextState = stateConfig[currentState].next[receivedEvent];
                if (nextState != currentState) {
                    stateConfig[nextState].enter();
                    currentState = nextState;
                    printf("State: %s\n", getStateName(nextState));
                    stateStartTime = millis();
                }
            }
            xSemaphoreGive(stateMutex);
        }

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(100));
    }
}