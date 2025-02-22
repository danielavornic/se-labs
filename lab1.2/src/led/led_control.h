#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <Arduino.h>

#define LED_GREEN_PIN 13
#define LED_RED_PIN 10

void ledInit();
void ledGreenOn();
void ledGreenOff();
void ledRedOn();
void ledRedOff();

#endif