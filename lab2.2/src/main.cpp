#include "button/button.h"
#include "config/config.h"
#include "globals/globals.h"
#include "led/led.h"
#include "serial_comm/serial_comm.h"
#include "tasks/tasks.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

void setup()
{
    initSerial();
    initButton();
    initLEDs();
    initGlobals();

    xTaskCreate(buttonLedTask, "buttonLedTask", BUTTON_TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    xTaskCreate(syncTask, "syncTask", SYNC_TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    xTaskCreate(asyncTask, "asyncTask", ASYNC_TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);

    vTaskStartScheduler();
}

void loop()
{
    // empty bc of FreeRTOS
}