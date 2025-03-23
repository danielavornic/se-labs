#include "joystick_task.h"
#include "../../config/config.h"
#include "../../conversion/conversion.h"
#include "../../globals/globals.h"
#include "../../joystick/joystick.h"
#include "../../signal_conditioning/signal_conditioning.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <task.h>

void joystickTask(void* pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(JOYSTICK_TASK_FREQUENCY_MS);

    while (1) {
        JoystickData rawData = getJoystickData();

        float filteredX = saltAndPepperFilter(rawData.x_angle, 0);
        filteredX = weightedAverageFilter(filteredX, 0);
        filteredX = applyPhysicalLimits(filteredX, JOYSTICK_MIN_ANGLE, JOYSTICK_MAX_ANGLE);

        float filteredY = saltAndPepperFilter(rawData.y_angle, 1);
        filteredY = weightedAverageFilter(filteredY, 1);
        filteredY = applyPhysicalLimits(filteredY, JOYSTICK_MIN_ANGLE, JOYSTICK_MAX_ANGLE);

        float voltageX = angleToVoltage(filteredX, VREF, JOYSTICK_MIN_ANGLE, JOYSTICK_MAX_ANGLE);
        float voltageY = angleToVoltage(filteredY, VREF, JOYSTICK_MIN_ANGLE, JOYSTICK_MAX_ANGLE);

        if (xSemaphoreTake(joystickMutex, portMAX_DELAY) == pdTRUE) {
            sharedJoystick.rawX = rawData.x_angle;
            sharedJoystick.rawY = rawData.y_angle;
            sharedJoystick.filteredX = filteredX;
            sharedJoystick.filteredY = filteredY;
            sharedJoystick.voltageX = voltageX;
            sharedJoystick.voltageY = voltageY;
            sharedJoystick.button = rawData.button;
            xSemaphoreGive(joystickMutex);
        }

        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}