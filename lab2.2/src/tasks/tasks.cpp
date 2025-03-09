#include "tasks.h"
#include "../button/button.h"
#include "../led/led.h"

SemaphoreHandle_t buttonSemaphore;
QueueHandle_t dataQueue;
static uint8_t counter = 0;

static SemaphoreHandle_t serialMutex;
static SemaphoreHandle_t queueMutex;

void tasksInit()
{
    buttonInit(BUTTON_PIN);
    ledInit(RED_LED_PIN);
    ledInit(GREEN_LED_PIN);

    buttonSemaphore = xSemaphoreCreateBinary();
    dataQueue = xQueueCreate(QUEUE_SIZE, sizeof(uint8_t));

    if (buttonSemaphore == NULL || dataQueue == NULL) {
        Serial.println("Error creating FreeRTOS objects!");
        return;
    }

    serialMutex = xSemaphoreCreateMutex();
    queueMutex = xSemaphoreCreateMutex();

    if (serialMutex == NULL || queueMutex == NULL) {
        Serial.println("Error creating mutexes!");
        return;
    }

    BaseType_t taskCreated;

    taskCreated = xTaskCreate(
        buttonLedTask,
        "ButtonLed",
        configMINIMAL_STACK_SIZE + 50,
        NULL,
        BUTTON_TASK_PRIORITY,
        NULL);

    if (taskCreated != pdPASS) {
        Serial.println("Failed to create button task!");
        return;
    }

    taskCreated = xTaskCreate(
        syncTask,
        "Sync",
        configMINIMAL_STACK_SIZE + 50,
        NULL,
        SYNC_TASK_PRIORITY,
        NULL);

    if (taskCreated != pdPASS) {
        Serial.println("Failed to create sync task!");
        return;
    }

    taskCreated = xTaskCreate(
        asyncTask,
        "Async",
        configMINIMAL_STACK_SIZE + 50,
        NULL,
        ASYNC_TASK_PRIORITY,
        NULL);

    if (taskCreated != pdPASS) {
        Serial.println("Failed to create async task!");
        return;
    }

    Serial.println("All tasks created successfully");
}

void buttonLedTask(void* pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();

    if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
        xSemaphoreGive(serialMutex);
    }

    for (;;) {
        if (isButtonPressed(BUTTON_PIN)) {
            if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
                Serial.println("\n[Button] Pressed");
                xSemaphoreGive(serialMutex);
            }

            xSemaphoreGive(buttonSemaphore);

            ledTurnOn(RED_LED_PIN);
            vTaskDelay(pdMS_TO_TICKS(1000));
            ledTurnOff(RED_LED_PIN);
        }
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(BUTTON_TASK_PERIOD_MS));
    }
}

void syncTask(void* pvParameters)
{
    if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
        xSemaphoreGive(serialMutex);
    }

    for (;;) {
        if (xSemaphoreTake(buttonSemaphore, portMAX_DELAY) == pdTRUE) {
            if (!isLedBlinking(GREEN_LED_PIN)) {
                // Protect counter increment
                taskENTER_CRITICAL();
                counter++;
                uint8_t currentCount = counter;
                taskEXIT_CRITICAL();

                if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
                    Serial.print("[Sync] Sequence: ");
                    xSemaphoreGive(serialMutex);
                }

                if (xSemaphoreTake(queueMutex, portMAX_DELAY) == pdTRUE) {
                    // Clear queue
                    uint8_t dummy;
                    while (xQueueReceive(dataQueue, &dummy, 0) == pdTRUE) { }

                    // Send sequence using SendToFront as required
                    for (uint8_t i = currentCount; i >= 1; i--) {
                        xQueueSendToFront(dataQueue, &i, portMAX_DELAY);
                        if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
                            Serial.print(i);
                            Serial.print(" ");
                            xSemaphoreGive(serialMutex);
                        }
                        vTaskDelay(pdMS_TO_TICKS(SYNC_TASK_PERIOD_MS)); // 50ms delay as required
                    }

                    // Send end marker
                    uint8_t endMarker = 0;
                    xQueueSendToFront(dataQueue, &endMarker, portMAX_DELAY);
                    xSemaphoreGive(queueMutex);
                }

                if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
                    Serial.print("[Sync] Blinking ");
                    Serial.print(currentCount);
                    Serial.println(" times");
                    xSemaphoreGive(serialMutex);
                }

                ledBlinkNTimes(GREEN_LED_PIN, currentCount, 300, 500);

                if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
                    Serial.println("[Sync] Blink complete");
                    xSemaphoreGive(serialMutex);
                }
            } else {
                // Give back semaphore if we can't process now
                xSemaphoreGive(buttonSemaphore);
            }
        }
    }
}

void asyncTask(void* pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;) {
        if (xSemaphoreTake(queueMutex, portMAX_DELAY) == pdTRUE) {
            uint8_t receivedByte;
            static bool newSequence = true;

            while (xQueueReceive(dataQueue, &receivedByte, 0) == pdTRUE) {
                if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
                    if (newSequence) {
                        Serial.print("\n[Async] Data: ");
                        newSequence = false;
                    }

                    if (receivedByte == 0) {
                        Serial.println();
                        newSequence = true;
                    } else {
                        Serial.print(receivedByte);
                        Serial.print(" ");
                    }
                    xSemaphoreGive(serialMutex);
                }
            }
            xSemaphoreGive(queueMutex);
        }
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(ASYNC_TASK_PERIOD_MS));
    }
}
