#include "fsm.h"

static FSMState currentState;

static const char* const stateNames[] = { "OFF", "ON", "BLINK" };

static const StateConfig stateConfig[STATE_COUNT] = {
    [STATE_OFF] = { STATE_ON, enterStateOff, updateStateOff },
    [STATE_ON] = { STATE_BLINK, enterStateOn, updateStateOn },
    [STATE_BLINK] = { STATE_OFF, enterStateBlink, updateStateBlink }
};

static void changeState(FSMState new_state)
{
    currentState = new_state;
    stateConfig[new_state].enter();
    printf("State: %s\n", stateNames[new_state]);
}

void initFSM()
{
    changeState(STATE_OFF);
}

void updateFSM()
{
    if (isButtonPressed()) {
        changeState(stateConfig[currentState].next);
    }

    stateConfig[currentState].update();
}