#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino_FreeRTOS.h>

#define MOTOR_IN1_PIN 3
#define MOTOR_IN2_PIN 4
#define MOTOR_ENA_PIN 5

#define POT_PIN A0

#define BUTTON_INC_PIN 10
#define BUTTON_DEC_PIN 11

#define POTENTIOMETER_TASK_PRIORITY 3
#define MOTOR_TASK_PRIORITY 2
#define BUTTON_TASK_PRIORITY 1

#define MOTOR_POWER 50
#define DEFAULT_SETPOINT 0
#define DEFAULT_HYSTERESIS 5
#define BUTTON_SETPOINT_CHANGE_UNITS 5

#define SERIAL_BAUD_RATE 9600

typedef enum {
    MOTOR_UPDATE_POSITION,
    MOTOR_SET_SETPOINT
} MotorCommandType;

typedef struct {
    MotorCommandType type;
    int value;
} MotorCommand;

#endif
