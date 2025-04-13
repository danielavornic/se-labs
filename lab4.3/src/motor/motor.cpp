#include "motor.h"

static int currentPosition = 0;
static int targetSetpoint = DEFAULT_SETPOINT;
static int hysteresisBand = DEFAULT_HYSTERESIS;

void motorInit()
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
}

void motorUpdatePosition(int position)
{
    currentPosition = position;

    // Calculate error and control bounds
    int error = targetSetpoint - currentPosition;
    int upperBound = hysteresisBand;
    int lowerBound = -hysteresisBand;

    // Apply hysteresis control
    uint8_t pwmValue = map(MOTOR_POWER, 0, 100, 0, 255);

    if (error > upperBound) {
        // Need to move forward - position too low
        digitalWrite(MOTOR_IN1_PIN, HIGH);
        digitalWrite(MOTOR_IN2_PIN, LOW);
        analogWrite(MOTOR_ENA_PIN, pwmValue);
        printf("Motor running FORWARD (50%%) - Position %d below target range [%d to %d]\n",
            currentPosition, targetSetpoint - hysteresisBand, targetSetpoint + hysteresisBand);
    } else if (error < lowerBound) {
        // Need to move backward - position too high
        digitalWrite(MOTOR_IN1_PIN, LOW);
        digitalWrite(MOTOR_IN2_PIN, HIGH);
        analogWrite(MOTOR_ENA_PIN, pwmValue);
        printf("Motor running BACKWARD (50%%) - Position %d above target range [%d to %d]\n",
            currentPosition, targetSetpoint - hysteresisBand, targetSetpoint + hysteresisBand);
    } else {
        // Within hysteresis band - stop motor
        digitalWrite(MOTOR_IN1_PIN, LOW);
        digitalWrite(MOTOR_IN2_PIN, LOW);
        analogWrite(MOTOR_ENA_PIN, 0);
        printf("Motor STOPPED - Position %d within target range [%d to %d]\n",
            currentPosition, targetSetpoint - hysteresisBand, targetSetpoint + hysteresisBand);
    }
}

void motorSetSetpoint(int setpoint)
{
    targetSetpoint = setpoint;
    // Immediately check if we need to move
    motorUpdatePosition(currentPosition);
}

void motorStop()
{
    digitalWrite(MOTOR_IN1_PIN, LOW);
    digitalWrite(MOTOR_IN2_PIN, LOW);
    analogWrite(MOTOR_ENA_PIN, 0);
}

int motorGetPosition()
{
    return currentPosition;
}

int motorGetSetpoint()
{
    return targetSetpoint;
}

void motorSetHysteresis(int value)
{
    if (value > 0) {
        hysteresisBand = value;
        // Immediately check if the new hysteresis affects motor control
        motorUpdatePosition(currentPosition);
    }
}

int motorGetHysteresis()
{
    return hysteresisBand;
}