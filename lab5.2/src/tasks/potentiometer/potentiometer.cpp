#include "potentiometer.h"

void potentiometerTask(void* pvParameters)
{
    int lastPosition = 0;

    while (1) {
        int newPosition = readPotentiometer();

        if (newPosition != lastPosition) {
            MotorCommand cmd = { MOTOR_UPDATE_POSITION, newPosition };
            xQueueSend(motorCommandQueue, &cmd, portMAX_DELAY);

            if (xSemaphoreTake(g_statusMutex, portMAX_DELAY) == pdTRUE) {
                g_systemStatus.currentPosition = newPosition;
                xSemaphoreGive(g_statusMutex);
            }

            lastPosition = newPosition;
        }

        vTaskDelay(pdMS_TO_TICKS(20));
    }
}
