#include "button/button.h"
#include "config/config.h"
#include "globals/globals.h"
#include "motor/motor.h"
#include "serial_comm/serial_comm.h"
#include "tasks/tasks.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

void setup()
{
    initSerial();
    initButtons();
    initMotor();
    initGlobals();
    createTasks();

    printf("Motor Control Initialized\n");

    vTaskStartScheduler();
}

void loop() { }