#include "tasks/tasks.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

void setup()
{
    Serial.begin(9600);

    while (!Serial) {
        ; // wait for serial port to connect
    }

    Serial.println(F("FreeRTOS Task Management Demo"));
    Serial.println(F("-------------------------------"));

    tasksInit();

    vTaskStartScheduler();

    // should never get here
    Serial.println("Scheduler failed to start!");
}

void loop()
{
    // Empty. Things are done in Tasks.
}
