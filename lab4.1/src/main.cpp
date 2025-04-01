#include "config/config.h"
#include "globals/globals.h"
#include "relay/relay.h"
#include "serial_comm/serial_comm.h"
#include "tasks/tasks.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

void setup()
{
    initSerial();
    initRelay();
    initGlobals();

    printf("System initialized. Available commands:\n");
    printf("relay on  - Turn relay ON\n");
    printf("relay off - Turn relay OFF\n");

    createTasks();
    vTaskStartScheduler();
}

void loop() { }