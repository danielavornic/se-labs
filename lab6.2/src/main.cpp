#include "button/button.h"
#include "globals/globals.h"
#include "led/led.h"
#include "serial_comm/serial_comm.h"
#include "tasks/tasks.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

void setup()
{
    initSerial();
    initLeds();
    initButtons();
    initGlobals();

    createTasks();
    vTaskStartScheduler();
}

void loop() { }