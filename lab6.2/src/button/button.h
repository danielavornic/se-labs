#ifndef BUTTON_H
#define BUTTON_H

#include "../config.h"
#include <Arduino.h>

void initButtons();
bool isButtonPressed();
bool isNightModeButtonPressed();

#endif