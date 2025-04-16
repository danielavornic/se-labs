#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino_FreeRTOS.h>

#define MOTOR_IN1_PIN 3
#define MOTOR_IN2_PIN 4
#define MOTOR_ENA_PIN 5

#define POT_PIN A0

#define MAX_COMMAND_LENGTH 32

#define POTENTIOMETER_TASK_PRIORITY 3
#define COMMAND_TASK_PRIORITY 1
#define MOTOR_TASK_PRIORITY 2

#define COMMAND_TASK_FREQUENCY 100

#define MOTOR_PWM_FREQUENCY 5000
#define MOTOR_PWM_RESOLUTION 8
#define MOTOR_PWM_CHANNEL 0

#define SERIAL_BAUD_RATE 9600

typedef enum {
    MOTOR_UPDATE_POSITION,
    MOTOR_SET_SETPOINT,
    MOTOR_SET_HYSTERESIS,
    MOTOR_STOP
} MotorCommandType;

typedef struct {
    MotorCommandType type;
    int value;
} MotorCommand;

#endif
