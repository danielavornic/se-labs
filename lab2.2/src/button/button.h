#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

void buttonInit(uint8_t pin);

bool isButtonPressed(uint8_t pin);

#endif