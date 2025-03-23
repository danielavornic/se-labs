#include "config/config.h"
#include "globals/globals.h"
#include "joystick/joystick.h"
#include "led/led.h"
#include "serial_comm/serial_comm.h"
#include "tasks/tasks.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

void setup()
{
    initSerial();
    initLED();
    initJoystick();
    initGlobals();

    xTaskCreate(displayTask, "DisplayTask", DISPLAY_TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    xTaskCreate(joystickTask, "JoystickTask", JOYSTICK_TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    vTaskStartScheduler();
}

void loop() { }