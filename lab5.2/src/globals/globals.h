#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>

#define DEFAULT_SETPOINT 0

#define POSITION_MIN 0
#define POSITION_MAX 100

#define ADC_MIN 0
#define ADC_MAX 1023

typedef enum {
    MOTOR_UPDATE_POSITION,
    MOTOR_SET_SETPOINT
} MotorCommandType;

typedef struct {
    MotorCommandType type;
    int value;
} MotorCommand;

extern QueueHandle_t motorCommandQueue;

typedef struct {
    int currentPosition;
    int targetPosition;
    double pidOutput;
} SystemStatus;

extern SystemStatus g_systemStatus;

extern SemaphoreHandle_t g_statusMutex;

void initGlobals(void);

#endif