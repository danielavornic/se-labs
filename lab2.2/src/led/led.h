#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

// Initialize LED pin and resources
bool ledInit(uint8_t pin);

// Turn LED on
void ledTurnOn(uint8_t pin);

void ledTurnOff(uint8_t pin);

void ledToggle(uint8_t pin);

void ledBlinkNTimes(uint8_t pin, uint8_t n, uint16_t onTime, uint16_t offTime);

bool isLedBlinking(uint8_t pin);

#endif