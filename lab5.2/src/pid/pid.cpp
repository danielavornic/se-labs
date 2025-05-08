#include "pid.h"

void updatePIDController()
{
    int error = state.setpoint - state.speed;

    state.integralError += error;

    if (pidConfig.ki != 0) {
        long integralSumLimit = (long)(MAX_INTEGRAL_CONTRIBUTION / pidConfig.ki);
        state.integralError = constrain(state.integralError, -integralSumLimit, integralSumLimit);
    }

    int derivativeError = error - state.lastError;

    float pidContribution = (pidConfig.kp * error) + (pidConfig.ki * state.integralError) + (pidConfig.kd * derivativeError);

    state.output += (int)pidContribution;

    state.output = constrain(state.output,
        pidConfig.minOutput,
        pidConfig.maxOutput);

    state.lastError = error;
}

void checkAndApplyProtections()
{
    protectionHasOverriddenOutput = false;

    if (state.speed > MAX_SAFE_SPEED) {
        printf("PROTECTION: Over-speed! Speed=%d > MAX=%d. Forcing output to min.\n", state.speed, MAX_SAFE_SPEED);
        state.output = pidConfig.minOutput; // Or 0 for a harder stop if minOutput still runs motor
        state.integralError = 0;
        protectionHasOverriddenOutput = true;
    }
}