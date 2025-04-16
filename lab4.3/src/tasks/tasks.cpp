#include "tasks.h"
#include "../config/config.h"
#include "command_processing/command_processing.h"
#include "motor_control/motor_control.h"
#include "potentiometer/potentiometer.h"

void createTasks()
{
    xTaskCreate(
        potentiometerTask,
        "PotentiometerTask",
        1024,
        NULL,
        3,
        NULL);

    xTaskCreate(
        commandProcessingTask,
        "CommandProcessing",
        1024,
        NULL,
        1,
        NULL);

    xTaskCreate(
        motorControlTask,
        "MotorControl",
        1024,
        NULL,
        2,
        NULL);
}