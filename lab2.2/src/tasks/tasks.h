#ifndef TASKS_H
#define TASKS_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>

// Pin definitions
#define BUTTON_PIN 2
#define RED_LED_PIN 12
#define GREEN_LED_PIN 13

// Task priorities
#define BUTTON_TASK_PRIORITY 3
#define SYNC_TASK_PRIORITY 2
#define ASYNC_TASK_PRIORITY 1

// Task periods
#define BUTTON_TASK_PERIOD_MS 10
#define SYNC_TASK_PERIOD_MS 50
#define ASYNC_TASK_PERIOD_MS 200

// Stack sizes
#define TASK_STACK_SIZE 256

// Buffer size for communication
#define QUEUE_SIZE 10

// External declarations
extern SemaphoreHandle_t buttonSemaphore;
extern QueueHandle_t dataQueue;

void tasksInit();
void buttonLedTask(void* pvParameters);
void syncTask(void* pvParameters);
void asyncTask(void* pvParameters);

#endif // TASKS_H