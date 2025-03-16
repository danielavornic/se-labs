#include "tasks.h"
#include "../config/config.h"
#include "../globals/globals.h"
#include "../led/led.h"
#include "../ultrasonic/ultrasonic.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <stdio.h>
#include <task.h>

void ultrasonicTask(void* pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(ULTRASONIC_TASK_FREQUENCY_MS);

    while (1) {
        float distance = getDistance();

        if (xSemaphoreTake(distanceMutex, portMAX_DELAY) == pdTRUE) {
            sharedDistance = distance;
            xSemaphoreGive(distanceMutex);
        }

        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void displayTask(void* pvParameters)
{
    float distance;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(DISPLAY_TASK_FREQUENCY_MS);

    while (1) {
        if (xSemaphoreTake(distanceMutex, portMAX_DELAY) == pdTRUE) {
            distance = sharedDistance;
            xSemaphoreGive(distanceMutex);
        }

        if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
            printf("Distance: %d cm | ", (int)distance);

            if (distance < DISTANCE_THRESHOLD_CM) {
                setLED(true);
                printf("Status: ALERT\n");
            } else {
                setLED(false);
                printf("Status: NORMAL\n");
            }

            xSemaphoreGive(serialMutex);
        }

        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}