#include "status_reporter.h"

void statusReporterTask(void* pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(500);

    while (1) {
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        int currentPos = 0;
        int targetPos = DEFAULT_SETPOINT;
        double pidOutput = 0.0;

        if (xSemaphoreTake(g_statusMutex, portMAX_DELAY) == pdTRUE) {
            currentPos = g_systemStatus.currentPosition;
            targetPos = g_systemStatus.targetPosition;
            pidOutput = g_systemStatus.pidOutput;
            xSemaphoreGive(g_statusMutex);
        }

        printf("SetPoint:%d Position:%d PIDOutput:%.2f\n",
            targetPos, currentPos, pidOutput);
    }
}