#ifndef LED_H
#define LED_H

#include <Arduino.h>

#define LED_PIN 12

void initLed();
void ledOn();
void ledOff();
void ledToggle();

#endif
