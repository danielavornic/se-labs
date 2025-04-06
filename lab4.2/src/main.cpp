#include "config/config.h"
#include "motor/motor.h"
#include "serial_comm/serial_comm.h"
#include "tasks/tasks.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

void setup()
{
    initSerial();
    motorInit();
    createTasks();

    vTaskStartScheduler();
}

void loop() { }