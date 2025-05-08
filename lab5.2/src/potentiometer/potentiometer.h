#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <Arduino.h>

#define POT_IN A0

void initPotentiometer();
int readSetpointFromPot();

#endif
