#ifndef BUTTON_H
#define BUTTON_H

#include "../config/config.h"
#include <Arduino.h>

#define DEBOUNCE_DELAY_MS 50

void initButtons();

bool buttonCheckIncrement();
bool buttonCheckDecrement();

#endif