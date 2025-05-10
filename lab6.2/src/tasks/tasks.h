#ifndef TASKS_H
#define TASKS_H

#include "../button/button.h"
#include "../config.h"
#include "../globals/globals.h"
#include "../state_actions/state_actions.h"
#include <Arduino_FreeRTOS.h>

void createTasks();

void vTrafficLightTask(void* pvParameters);
void vButtonCheckTask(void* pvParameters);
void vStateUpdateTask(void* pvParameters);

#endif