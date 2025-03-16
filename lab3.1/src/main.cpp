#include "config/config.h"
#include "globals/globals.h"
#include "led/led.h"
#include "serial_comm/serial_comm.h"
#include "tasks/tasks.h"
#include "ultrasonic/ultrasonic.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

void setup()
{
    initSerial();
    initLED();
    initUltrasonic();
    initGlobals();

    xTaskCreate(ultrasonicTask, "UltrasonicTask", ULTRASONIC_TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    xTaskCreate(displayTask, "DisplayTask", DISPLAY_TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);

    vTaskStartScheduler();
}

void loop() { }