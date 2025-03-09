#ifndef CONFIG_H
#define CONFIG_H

#define BUTTON_PIN 2
#define LED1_PIN 12
#define LED2_PIN 13

#define BUTTON_TASK_STACK_SIZE 128
#define SYNC_TASK_STACK_SIZE 128
#define ASYNC_TASK_STACK_SIZE 128
#define TASK_PRIORITY 1

#define BUTTON_TASK_FREQUENCY_MS 10
#define LED1_ON_TIME_MS 1000
#define LED2_ON_TIME_MS 300
#define LED2_OFF_TIME_MS 500
#define SYNC_TASK_DELAY_MS 50
#define ASYNC_TASK_DELAY_MS 200

#define QUEUE_SIZE 20

#endif