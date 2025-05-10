#ifndef STATE_ACTIONS_H
#define STATE_ACTIONS_H

#include "../led/led.h"
#include <Arduino.h>

typedef void (*StateAction)();

void enterEastGreen();
void updateEastGreen();
void enterEastYellow();
void updateEastYellow();

void enterNorthGreen();
void updateNorthGreen();
void enterNorthYellow();
void updateNorthYellow();

void enterAllRed();
void updateAllRed();

void enterFlashingYellow();
void updateFlashingYellow();

#endif