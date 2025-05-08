#include "motor.h"

void initMotor()
{
    pinMode(MOTOR_ENABLE_PIN, OUTPUT);
    pinMode(MOTOR_IN1_PIN, OUTPUT);
    pinMode(MOTOR_IN2_PIN, OUTPUT);

    digitalWrite(MOTOR_IN1_PIN, HIGH);
    digitalWrite(MOTOR_IN2_PIN, LOW);

    analogWrite(MOTOR_ENABLE_PIN, state.output);
}

void applyMotorOutput()
{
    analogWrite(MOTOR_ENABLE_PIN, state.output);
}
