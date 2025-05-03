#include "motor.h"

static int currentPosition = 0;
static int targetSetpoint = DEFAULT_SETPOINT;
static double pidOutput = 0;
static float integral = 0;
static float prevPosition = 0;
static unsigned long lastTime = 0;

void motorSetDirection(int direction, int pwm)
{
    pwm = constrain(pwm, 0, MOTOR_MAX_PWM);

    switch (direction) {
    case MOTOR_DIR_CW:
        digitalWrite(MOTOR_IN1_PIN, HIGH);
        digitalWrite(MOTOR_IN2_PIN, LOW);
        analogWrite(MOTOR_ENA_PIN, pwm);
        break;
    case MOTOR_DIR_CCW:
        digitalWrite(MOTOR_IN1_PIN, LOW);
        digitalWrite(MOTOR_IN2_PIN, HIGH);
        analogWrite(MOTOR_ENA_PIN, pwm);
        break;
    default:
        digitalWrite(MOTOR_IN1_PIN, LOW);
        digitalWrite(MOTOR_IN2_PIN, LOW);
        analogWrite(MOTOR_ENA_PIN, 0);
        break;
    }
}

void initMotor()
{
    pinMode(MOTOR_IN1_PIN, OUTPUT);
    pinMode(MOTOR_IN2_PIN, OUTPUT);
    pinMode(MOTOR_ENA_PIN, OUTPUT);
    motorSetDirection(MOTOR_DIR_STOP, 0);

    currentPosition = 0;
    targetSetpoint = DEFAULT_SETPOINT;
    prevPosition = 0;
    integral = 0;
    lastTime = millis();
    pidOutput = 0;
}

void motorUpdatePosition(int position)
{
    currentPosition = position;
    motorUpdatePID();
}

void motorUpdatePID()
{
    unsigned long now = millis();
    float deltaTime = (float)(now - lastTime) / 1000.0;

    if (deltaTime <= 0.0) {
        return;
    }
    lastTime = now;

    float error = (float)targetSetpoint - currentPosition;

    integral = integral + error * deltaTime;
    integral = constrain(integral, INTEGRAL_MIN, INTEGRAL_MAX);

    float derivative = (currentPosition - prevPosition) / deltaTime;
    prevPosition = currentPosition;

    pidOutput = (KP_DEFAULT * error) + (KI_DEFAULT * integral) - (KD_DEFAULT * derivative);

    pidOutput = constrain(pidOutput, PID_OUTPUT_MIN, PID_OUTPUT_MAX);

    int pwmValue = 0;
    int direction = MOTOR_DIR_STOP;

    if (fabs(pidOutput) > PID_OUTPUT_THRESHOLD) {
        pwmValue = map(fabs(pidOutput), 0.0, PID_OUTPUT_MAX, MOTOR_MIN_PWM,
            MOTOR_MAX_PWM);
        pwmValue = constrain(pwmValue, MOTOR_MIN_PWM, MOTOR_MAX_PWM);
        direction = (pidOutput > 0) ? MOTOR_DIR_CW : MOTOR_DIR_CCW;
    }

    motorSetDirection(direction, pwmValue);
}

void motorSetSetpoint(int setpoint)
{
    targetSetpoint = constrain(setpoint, 0, 100);
    if (abs(targetSetpoint - currentPosition) > INTEGRAL_RESET_THRESHOLD) {
        integral = 0;
    }
}

int motorGetSetpoint()
{
    return targetSetpoint;
}

double motorGetPIDOutput()
{
    return pidOutput;
}