#include "potentiometer.h"

void potentiometerTask(void* pvParameters)
{
    int lastPosition = -1;
    int lastReportedPosition = -1;
    const int POSITION_THRESHOLD = 1;
    pinMode(POT_PIN, INPUT);

    while (1) {
        int rawValue = analogRead(POT_PIN);
        int newPosition = map(rawValue, 0, 1023, 0, 100);

        if (newPosition != lastPosition) {
            MotorCommand cmd;
            cmd.type = MOTOR_UPDATE_POSITION;
            cmd.value = newPosition;
            xQueueSend(motorCommandQueue, &cmd, portMAX_DELAY);

            if (abs(newPosition - lastReportedPosition) >= POSITION_THRESHOLD) {
                if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
                    printf("Position: %d\n", newPosition);
                    xSemaphoreGive(serialMutex);
                    lastReportedPosition = newPosition;
                }
            }

            lastPosition = newPosition;
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
