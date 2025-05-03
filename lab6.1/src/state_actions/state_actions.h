#ifndef STATE_ACTIONS_H
#define STATE_ACTIONS_H

#include "../led/led.h"
#include <Arduino.h>

#define BLINK_MS 500

typedef void (*StateAction)();

void enterStateOff(void);
void updateStateOff(void);

void enterStateOn(void);
void updateStateOn(void);

void enterStateBlink(void);
void updateStateBlink(void);

#endif