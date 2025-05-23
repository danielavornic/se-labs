#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino_FreeRTOS.h>

#define MOTOR_IN1_PIN 3
#define MOTOR_IN2_PIN 4
#define MOTOR_ENA_PIN 5

#define MAX_COMMAND_LENGTH 32

#define COMMAND_TASK_PRIORITY 1
#define MOTOR_TASK_PRIORITY 2

#define DISPLAY_TASK_FREQUENCY 1000
#define COMMAND_TASK_FREQUENCY 100

#define MOTOR_PWM_FREQUENCY 5000
#define MOTOR_PWM_RESOLUTION 8
#define MOTOR_PWM_CHANNEL 0

#define SERIAL_BAUD_RATE 9600

typedef enum {
    MOTOR_SET_SPEED,
    MOTOR_STOP,
    MOTOR_INCREMENT,
    MOTOR_DECREMENT,
    MOTOR_SET_MAX
} MotorCommandType;

typedef struct {
    MotorCommandType type;
    int8_t speed;
} MotorCommand;

#endif
