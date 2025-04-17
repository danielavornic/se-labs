#include "motor.h"
#include "../globals/globals.h"

static int currentPosition = 0;
static int targetSetpoint = DEFAULT_SETPOINT;
static int hysteresisBand = DEFAULT_HYSTERESIS;
static int lastMotorState = 0; // 0=stop, 1=forward, -1=backward

void initMotor()
{
    pinMode(MOTOR_IN1_PIN, OUTPUT);
    pinMode(MOTOR_IN2_PIN, OUTPUT);
    pinMode(MOTOR_ENA_PIN, OUTPUT);

    digitalWrite(MOTOR_IN1_PIN, LOW);
    digitalWrite(MOTOR_IN2_PIN, LOW);
    analogWrite(MOTOR_ENA_PIN, 0);

    currentPosition = 0;
    targetSetpoint = DEFAULT_SETPOINT;
    hysteresisBand = DEFAULT_HYSTERESIS;
    lastMotorState = 0;
}

void motorUpdatePosition(int position)
{
    currentPosition = position;
    int lowerBound = targetSetpoint - hysteresisBand;
    int upperBound = targetSetpoint + hysteresisBand;

    uint8_t pwmValue = map(MOTOR_POWER, 0, 100, 0, 255);
    int newMotorState;

    if (currentPosition < lowerBound) {
        // move forward
        digitalWrite(MOTOR_IN1_PIN, HIGH);
        digitalWrite(MOTOR_IN2_PIN, LOW);
        analogWrite(MOTOR_ENA_PIN, pwmValue);
        newMotorState = 1;
    } else if (currentPosition > upperBound) {
        // move backward
        digitalWrite(MOTOR_IN1_PIN, LOW);
        digitalWrite(MOTOR_IN2_PIN, HIGH);
        analogWrite(MOTOR_ENA_PIN, pwmValue);
        newMotorState = -1;
    } else {
        // within hysteresis band - stop motor
        digitalWrite(MOTOR_IN1_PIN, LOW);
        digitalWrite(MOTOR_IN2_PIN, LOW);
        analogWrite(MOTOR_ENA_PIN, 0);
        newMotorState = 0;
    }

    if (newMotorState != lastMotorState) {
        if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
            switch (newMotorState) {
            case 1:
                printf("Motor: FORWARD - Position %d below range [%d to %d]\n",
                    currentPosition, lowerBound, upperBound);
                break;
            case -1:
                printf("Motor: BACKWARD - Position %d above range [%d to %d]\n",
                    currentPosition, lowerBound, upperBound);
                break;
            case 0:
                printf("Motor: STOPPED - Position %d within range [%d to %d]\n",
                    currentPosition, lowerBound, upperBound);
                break;
            }
            xSemaphoreGive(serialMutex);
        }
        lastMotorState = newMotorState;
    }
}

void motorSetSetpoint(int setpoint)
{
    targetSetpoint = setpoint;
    motorUpdatePosition(currentPosition);
}

int motorGetSetpoint()
{
    return targetSetpoint;
}