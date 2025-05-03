#include "button_handler.h"

void buttonHandlerTask(void* pvParameters)
{
    while (1) {
        if (buttonCheckIncrement()) {
            int currentSetpoint = motorGetSetpoint();
            int newSetpoint = currentSetpoint + BUTTON_SETPOINT_CHANGE_UNITS;
            if (newSetpoint > 100) {
                newSetpoint = 100;
            }

            if (newSetpoint != currentSetpoint) {
                MotorCommand motorCmd;
                motorCmd.type = MOTOR_SET_SETPOINT;
                motorCmd.value = newSetpoint;
                xQueueSend(motorCommandQueue, &motorCmd, portMAX_DELAY);
            }
        }

        if (buttonCheckDecrement()) {
            int currentSetpoint = motorGetSetpoint();
            int newSetpoint = currentSetpoint - BUTTON_SETPOINT_CHANGE_UNITS;
            if (newSetpoint < 0) {
                newSetpoint = 0;
            }

            if (newSetpoint != currentSetpoint) {
                MotorCommand motorCmd;
                motorCmd.type = MOTOR_SET_SETPOINT;
                motorCmd.value = newSetpoint;
                xQueueSend(motorCommandQueue, &motorCmd, portMAX_DELAY);
            }
        }

        vTaskDelay(pdMS_TO_TICKS(20));
    }
}