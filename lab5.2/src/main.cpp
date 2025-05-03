#include "button/button.h"
#include "globals/globals.h"
#include "motor/motor.h"
#include "potentiometer/potentiometer.h"
#include "serial_comm/serial_comm.h"
#include "tasks/tasks.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

void setup()
{
    initSerial();
    initButtons();
    initPotentiometer();
    initMotor();
    initGlobals();
    createTasks();

    vTaskStartScheduler();
}

void loop() { }