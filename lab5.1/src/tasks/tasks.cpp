#include "tasks.h"
#include "../config/config.h"
#include "button_handler/button_handler.h"
#include "motor_control/motor_control.h"
#include "potentiometer/potentiometer.h"

void createTasks()
{
    xTaskCreate(
        potentiometerTask,
        "PotentiometerTask",
        1024,
        NULL,
        POTENTIOMETER_TASK_PRIORITY,
        NULL);

    xTaskCreate(
        motorControlTask,
        "MotorControl",
        1024,
        NULL,
        MOTOR_TASK_PRIORITY,
        NULL);

    xTaskCreate(
        buttonHandlerTask,
        "ButtonHandler",
        1024,
        NULL,
        BUTTON_TASK_PRIORITY,
        NULL);
}