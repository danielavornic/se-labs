#ifndef TASKS_H
#define TASKS_H

#include <Arduino_FreeRTOS.h>

#define POTENTIOMETER_TASK_PRIORITY 2
#define MOTOR_TASK_PRIORITY 3
#define BUTTON_TASK_PRIORITY 2
#define STATUS_REPORTER_TASK_PRIORITY 1

void createTasks();

#endif