#include "encoder/encoder.h"
#include "globals/globals.h"
#include "motor/motor.h"
#include "pid/pid.h"
#include "potentiometer/potentiometer.h"
#include "serial_comm/serial_comm.h"
#include "timing/timing.h"

void setup()
{
    initSerial();
    initEncoder();
    initPotentiometer();
    initMotor();
    initTiming();
}

void loop()
{
    if (isUpdateDue()) {
        state.setpoint = readSetpointFromPot();
        state.speed = measureSpeed();

        updatePIDController();
        checkAndApplyProtections();
        applyMotorOutput();

        printf("SP=%d, Value=%d, Output=%d", state.setpoint, state.speed, state.output);
        if (protectionHasOverriddenOutput) {
            printf(" (PROTECTION OVERRIDE)");
        }
        printf("\n");

        markUpdateTime();
    }
}
