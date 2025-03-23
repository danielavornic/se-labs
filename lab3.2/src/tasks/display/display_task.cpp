#include "display_task.h"
#include "../../config/config.h"
#include "../../display/display.h"
#include "../../globals/globals.h"
#include "../../led/led.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <stdio.h>
#include <task.h>

void displayTask(void* pvParameters)
{
    JoystickReadings joystick;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(DISPLAY_TASK_FREQUENCY_MS);
    char buffer[20];

    while (1) {
        if (xSemaphoreTake(joystickMutex, portMAX_DELAY) == pdTRUE) {
            joystick = sharedJoystick;
            xSemaphoreGive(joystickMutex);
        }

        if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
            printf("==== Joystick Report ====\n");

            formatAngle(buffer, joystick.rawX);
            printf("Raw X: %s\n", buffer);
            formatAngle(buffer, joystick.rawY);
            printf("Raw Y: %s\n", buffer);
            formatAngle(buffer, joystick.filteredX);
            printf("Filtered X: %s\n", buffer);
            formatAngle(buffer, joystick.filteredY);
            printf("Filtered Y: %s\n", buffer);
            printf("Button: %s\n", joystick.button ? "PRESSED" : "RELEASED");
            formatVoltage(buffer, joystick.voltageX);
            printf("X Voltage: %s\n", buffer);
            formatVoltage(buffer, joystick.voltageY);
            printf("Y Voltage: %s\n", buffer);

            printf("=====================\n\n");

            setLED(joystick.button);
            xSemaphoreGive(serialMutex);
        }

        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}