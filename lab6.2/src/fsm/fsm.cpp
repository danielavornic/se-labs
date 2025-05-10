#include "fsm.h"
#include "../config.h"

static FSMState currentState;
static unsigned long stateStartTime;

static const char* const stateNames[] = {
    "EAST_GREEN",
    "EAST_YELLOW",
    "ALL_RED_EAST_TO_NORTH",
    "NORTH_GREEN",
    "NORTH_YELLOW",
    "ALL_RED_NORTH_TO_EAST"
};

static const StateConfig stateConfig[STATE_COUNT] = {
    [STATE_EAST_GREEN] = { { STATE_EAST_GREEN, STATE_EAST_YELLOW }, enterEastGreen, GREEN_DURATION },
    [STATE_EAST_YELLOW] = { { STATE_ALL_RED_EAST_TO_NORTH, STATE_ALL_RED_EAST_TO_NORTH }, enterEastYellow, YELLOW_DURATION },
    [STATE_ALL_RED_EAST_TO_NORTH] = { { STATE_NORTH_GREEN, STATE_NORTH_GREEN }, enterAllRed, ALL_RED_DURATION },
    [STATE_NORTH_GREEN] = { { STATE_NORTH_YELLOW, STATE_NORTH_YELLOW }, enterNorthGreen, GREEN_DURATION },
    [STATE_NORTH_YELLOW] = { { STATE_ALL_RED_NORTH_TO_EAST, STATE_ALL_RED_NORTH_TO_EAST }, enterNorthYellow, YELLOW_DURATION },
    [STATE_ALL_RED_NORTH_TO_EAST] = { { STATE_EAST_GREEN, STATE_EAST_GREEN }, enterAllRed, ALL_RED_DURATION }
};

static void changeState(FSMState new_state)
{
    currentState = new_state;
    stateStartTime = millis();
    stateConfig[new_state].enter();
    printf("State: %s\n", stateNames[new_state]);
}

void initFSM()
{
    changeState(STATE_EAST_GREEN);
}

void updateFSM()
{
    unsigned long currentTime = millis();
    bool timeExpired = (currentTime - stateStartTime) >= stateConfig[currentState].duration;
    bool buttonPressed = isButtonPressed();

    bool shouldChangeState = timeExpired || (buttonPressed && currentState == STATE_EAST_GREEN);
    if (shouldChangeState) {
        changeState(stateConfig[currentState].next[buttonPressed ? 1 : 0]);
    }
}

FSMState getCurrentState()
{
    return currentState;
}

const char* getStateName(FSMState state)
{
    return stateNames[state];
}