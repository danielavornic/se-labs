#ifndef FSM_H
#define FSM_H

#include "../button/button.h"
#include "../state_actions/state_actions.h"
#include <Arduino.h>

typedef enum {
    STATE_OFF,
    STATE_ON,
    STATE_BLINK,
    STATE_COUNT,
} FSMState;

typedef struct {
    FSMState next;
    StateAction enter;
    StateAction update;
} StateConfig;

void initFSM();
void updateFSM();

#endif