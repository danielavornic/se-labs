#ifndef FSM_H
#define FSM_H

#include "../button/button.h"
#include "../led/led.h"
#include "../state_actions/state_actions.h"
#include <Arduino.h>

typedef enum {
    STATE_EAST_GREEN,
    STATE_EAST_YELLOW,
    STATE_ALL_RED_EAST_TO_NORTH,
    STATE_NORTH_GREEN,
    STATE_NORTH_YELLOW,
    STATE_ALL_RED_NORTH_TO_EAST,
    STATE_COUNT,
} FSMState;

typedef struct {
    // 0 - button not pressed, 1 - button pressed
    FSMState next[2];
    StateAction enter;
    unsigned long duration;
} StateConfig;

void initFSM();
void updateFSM();
FSMState getCurrentState();
const char* getStateName(FSMState state);

#endif