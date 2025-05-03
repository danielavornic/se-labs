#include "motor_control.h"
#include "../../globals/globals.h"
#include "../../motor/motor.h"

void motorControlTask(void* pvParameters)
{
    MotorCommand command;

    while (1) {
        if (xQueueReceive(motorCommandQueue, &command, portMAX_DELAY) == pdTRUE) {
            if (xSemaphoreTake(g_statusMutex, portMAX_DELAY) == pdTRUE) {
                switch (command.type) {
                case MOTOR_UPDATE_POSITION:
                    motorUpdatePosition(command.value);
                    g_systemStatus.currentPosition = command.value;
                    break;
                case MOTOR_SET_SETPOINT:
                    motorSetSetpoint(command.value);
                    motorUpdatePID();
                    g_systemStatus.targetPosition = command.value;
                    break;
                }
                g_systemStatus.pidOutput = motorGetPIDOutput();
                xSemaphoreGive(g_statusMutex);
            }
        }
    }
}