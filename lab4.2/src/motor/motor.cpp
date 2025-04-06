#include "motor.h"

static int8_t currentSpeed = 0;

void motorInit()
{
    pinMode(MOTOR_IN1_PIN, OUTPUT);
    pinMode(MOTOR_IN2_PIN, OUTPUT);
    pinMode(MOTOR_ENA_PIN, OUTPUT);

    digitalWrite(MOTOR_IN1_PIN, LOW);
    digitalWrite(MOTOR_IN2_PIN, LOW);
    analogWrite(MOTOR_ENA_PIN, 0);
}

void motorSetSpeed(int8_t speed)
{
    speed = constrain(speed, -100, 100);
    currentSpeed = speed;

    uint8_t pwmValue = map(abs(speed), 0, 100, 0, 255);

    analogWrite(MOTOR_ENA_PIN, pwmValue);

    if (speed > 0) {
        pinMode(MOTOR_IN1_PIN, OUTPUT);
        pinMode(MOTOR_IN2_PIN, OUTPUT);
        digitalWrite(MOTOR_IN1_PIN, HIGH);
        digitalWrite(MOTOR_IN2_PIN, LOW);
    } else if (speed < 0) {
        digitalWrite(MOTOR_IN1_PIN, LOW);
        digitalWrite(MOTOR_IN2_PIN, HIGH);
    } else {
        digitalWrite(MOTOR_IN1_PIN, LOW);
        digitalWrite(MOTOR_IN2_PIN, LOW);
        analogWrite(MOTOR_ENA_PIN, 0);
    }
}

void motorStop()
{
    digitalWrite(MOTOR_IN1_PIN, LOW);
    digitalWrite(MOTOR_IN2_PIN, LOW);
    analogWrite(MOTOR_ENA_PIN, 0);
    currentSpeed = 0;
}

int8_t motorGetSpeed()
{
    return currentSpeed;
}

void motorIncrement()
{
    int8_t newSpeed = currentSpeed + 10;
    motorSetSpeed(newSpeed);
}

void motorDecrement()
{
    int8_t newSpeed = currentSpeed - 10;
    motorSetSpeed(newSpeed);
}

void motorSetMax()
{
    if (currentSpeed >= 0) {
        motorSetSpeed(100);
    } else {
        motorSetSpeed(-100);
    }
}