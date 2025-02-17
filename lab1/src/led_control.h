#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <Arduino.h>

#define LED_PIN 13 // built-in LED pin

void ledInit();
void ledOn();
void ledOff();
bool ledGetState();

#endif