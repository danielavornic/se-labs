#pragma once

#include <Arduino_FreeRTOS.h>

void createTasks();
void serialCommandHandler(void* pvParameters);
