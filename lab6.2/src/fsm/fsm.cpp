#include "fsm.h"
#include "../config.h"
#include <limits.h>

static FSMState currentState;
static unsigned long stateStartTime;

static const char* const stateNames[] = {
    "EAST_GREEN",
    "EAST_YELLOW",
    "ALL_RED_EAST_TO_NORTH",
    "NORTH_GREEN",
    "NORTH_YELLOW",
    "ALL_RED_NORTH_TO_EAST",
    "FLASHING_YELLOW"
};

static const StateConfig stateConfig[STATE_COUNT] = {
    [STATE_EAST_GREEN] = {
        .next = {
            STATE_EAST_GREEN,
            STATE_EAST_YELLOW,
            STATE_FLASHING_YELLOW },
        .enter = enterEastGreen,
        .update = updateEastGreen,
        .duration = GREEN_DURATION },
    [STATE_EAST_YELLOW] = { .next = { STATE_ALL_RED_EAST_TO_NORTH, STATE_ALL_RED_EAST_TO_NORTH, STATE_FLASHING_YELLOW }, .enter = enterEastYellow, .update = updateEastYellow, .duration = YELLOW_DURATION },
    [STATE_ALL_RED_EAST_TO_NORTH] = { .next = { STATE_NORTH_GREEN, STATE_NORTH_GREEN, STATE_FLASHING_YELLOW }, .enter = enterAllRed, .update = updateAllRed, .duration = ALL_RED_DURATION },
    [STATE_NORTH_GREEN] = { .next = { STATE_NORTH_YELLOW, STATE_NORTH_YELLOW, STATE_FLASHING_YELLOW }, .enter = enterNorthGreen, .update = updateNorthGreen, .duration = GREEN_DURATION },
    [STATE_NORTH_YELLOW] = { .next = { STATE_ALL_RED_NORTH_TO_EAST, STATE_ALL_RED_NORTH_TO_EAST, STATE_FLASHING_YELLOW }, .enter = enterNorthYellow, .update = updateNorthYellow, .duration = YELLOW_DURATION },
    [STATE_ALL_RED_NORTH_TO_EAST] = { .next = { STATE_EAST_GREEN, STATE_EAST_GREEN, STATE_FLASHING_YELLOW }, .enter = enterAllRed, .update = updateAllRed, .duration = ALL_RED_DURATION },
    [STATE_FLASHING_YELLOW] = { .next = { STATE_FLASHING_YELLOW, STATE_FLASHING_YELLOW, STATE_EAST_GREEN }, .enter = enterFlashingYellow, .update = updateFlashingYellow, .duration = ULONG_MAX }
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
    ButtonPress buttonPressed = BUTTON_NONE;
    if (isNightModeButtonPressed()) {
        buttonPressed = BUTTON_NIGHT_MODE;
    } else if (isButtonPressed()) {
        buttonPressed = BUTTON_NORTH;
    }

    unsigned long currentTime = millis();
    bool timeExpired = (currentTime - stateStartTime) >= stateConfig[currentState].duration;

    if (timeExpired || buttonPressed != BUTTON_NONE) {
        FSMState nextState = stateConfig[currentState].next[buttonPressed];
        if (nextState != currentState) {
            changeState(nextState);
        }
    }

    stateConfig[currentState].update();
}

FSMState getCurrentState()
{
    return currentState;
}

const char* getStateName(FSMState state)
{
    return stateNames[state];
}