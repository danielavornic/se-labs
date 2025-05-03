#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "../globals/globals.h"
#include <Arduino.h>

#define POT_PIN A0

void initPotentiometer();
int readPotentiometer();

#endif