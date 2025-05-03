#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

#define BUTTON_INC_PIN 9
#define BUTTON_DEC_PIN 10
#define DEBOUNCE_DELAY_MS 50

void initButtons();
bool buttonCheckIncrement();
bool buttonCheckDecrement();

#endif