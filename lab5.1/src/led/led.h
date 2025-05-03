#ifndef LED_H
#define LED_H

#include "../config/config.h"
#include <Arduino.h>

void initLED();
void setLED(bool state);

#endif