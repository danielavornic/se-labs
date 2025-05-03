#include "button_handler.h"

void updateSetpoint(int change)
{
    int currentSetpoint = motorGetSetpoint();
    int newSetpoint = constrain(currentSetpoint + change, 0, 180);

    if (newSetpoint != currentSetpoint) {
        MotorCommand cmd = { MOTOR_SET_SETPOINT, newSetpoint };
        xQueueSend(motorCommandQueue, &cmd, portMAX_DELAY);
    }
}

void buttonHandlerTask(void* pvParameters)
{
    while (1) {
        if (buttonCheckIncrement()) {
            updateSetpoint(BUTTON_SETPOINT_CHANGE_UNITS);
        }
        if (buttonCheckDecrement()) {
            updateSetpoint(-BUTTON_SETPOINT_CHANGE_UNITS);
        }
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}