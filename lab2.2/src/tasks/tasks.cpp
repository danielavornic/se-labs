#include "tasks.h"
#include "../button/button.h"
#include "../config/config.h"
#include "../globals/globals.h"
#include "../led/led.h"
#include "../serial_comm/serial_comm.h"
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include <stdio.h>
#include <task.h>

void buttonLedTask(void* pvParameters)
{
    // the last time the task was woken up to check the button state
    TickType_t xLastWakeTime = xTaskGetTickCount();
    // the frequency of the task
    // convert milliseconds to ticks
    const TickType_t xFrequency = pdMS_TO_TICKS(BUTTON_TASK_FREQUENCY_MS);

    while (1) {
        if (isButtonPressed()) {
            setLED1(true);
            xSemaphoreGive(buttonSemaphore);
            vTaskDelay(pdMS_TO_TICKS(LED1_ON_TIME_MS));
            setLED1(false);
        }

        // wait for the next cycle
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void syncTask(void* pvParameters)
{
    while (1) {
        if (xSemaphoreTake(buttonSemaphore, portMAX_DELAY)) {
            // lock the mutex before accessing N
            if (xSemaphoreTake(nMutex, portMAX_DELAY) == pdTRUE) {
                N++;
                xSemaphoreGive(nMutex); // unlock the mutex
            }

            for (uint8_t i = 1; i <= N; i++) {
                xQueueSendToFront(dataQueue, &i, portMAX_DELAY);
            }

            // blink LED2 N times
            for (uint8_t i = 0; i < N; i++) {
                setLED2(true);
                vTaskDelay(pdMS_TO_TICKS(LED2_ON_TIME_MS));
                setLED2(false);
                vTaskDelay(pdMS_TO_TICKS(LED2_OFF_TIME_MS));
            }

            // 50ms delay
            vTaskDelay(pdMS_TO_TICKS(SYNC_TASK_DELAY_MS));
        }
    }
}

void asyncTask(void* pvParameters)
{
    uint8_t receivedData;

    while (1) {
        if (xQueueReceive(dataQueue, &receivedData, portMAX_DELAY)) {
            // lock the mutex before using Serial
            if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
                printf("%d ", receivedData);
                if (receivedData == 1) {
                    printf("%c", 0);
                }
                xSemaphoreGive(serialMutex);
            }
        }

        // 200ms delay
        vTaskDelay(pdMS_TO_TICKS(ASYNC_TASK_DELAY_MS));
    }
}