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
    STATE_FLASHING_YELLOW,
    STATE_COUNT,
} FSMState;

typedef enum {
    BUTTON_NONE,
    BUTTON_NORTH,
    BUTTON_NIGHT_MODE
} ButtonPress;

typedef struct {
    FSMState next[3]; // [0]: timeout/no button, [1]: north button, [2]: night mode button
    StateAction enter;
    StateAction update;
    unsigned long duration;
} StateConfig;

extern const StateConfig stateConfig[STATE_COUNT];
extern const char* const stateNames[STATE_COUNT];

const char* getStateName(FSMState state);

#endif