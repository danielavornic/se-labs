#ifndef PID_H
#define PID_H

#include "../globals/globals.h"
#include <Arduino.h>

#define MAX_INTEGRAL_CONTRIBUTION 50
#define MAX_SAFE_SPEED 605

static bool protectionHasOverriddenOutput = false;

void updatePIDController();
void checkAndApplyProtections();
#endif
