#ifndef STATE_ACTIONS_H
#define STATE_ACTIONS_H

#include "../led/led.h"
#include <Arduino.h>

typedef void (*StateAction)();

void enterEastGreen();
void enterEastYellow();
void enterNorthGreen();
void enterNorthYellow();
void enterAllRed();

#endif