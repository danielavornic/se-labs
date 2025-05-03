#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

#define BUTTON_PIN 2

void initButton();
bool isButtonPressed();

#endif