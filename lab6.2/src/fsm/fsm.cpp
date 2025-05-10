#include "fsm.h"
#include "../config.h"
#include <limits.h>

const char* const stateNames[] = {
    "EAST_GREEN",
    "EAST_YELLOW",
    "ALL_RED_EAST_TO_NORTH",
    "NORTH_GREEN",
    "NORTH_YELLOW",
    "ALL_RED_NORTH_TO_EAST",
    "FLASHING_YELLOW"
};

const char* getStateName(FSMState state)
{
    return stateNames[state];
}

const StateConfig stateConfig[STATE_COUNT] = {
    { { STATE_EAST_GREEN, STATE_EAST_YELLOW, STATE_FLASHING_YELLOW },
        enterEastGreen,
        updateEastGreen,
        GREEN_DURATION },
    { { STATE_ALL_RED_EAST_TO_NORTH, STATE_ALL_RED_EAST_TO_NORTH, STATE_FLASHING_YELLOW },
        enterEastYellow,
        updateEastYellow,
        YELLOW_DURATION },
    { { STATE_NORTH_GREEN, STATE_NORTH_GREEN, STATE_FLASHING_YELLOW },
        enterAllRed,
        updateAllRed,
        ALL_RED_DURATION },
    { { STATE_NORTH_YELLOW, STATE_NORTH_YELLOW, STATE_FLASHING_YELLOW },
        enterNorthGreen,
        updateNorthGreen,
        GREEN_DURATION },
    { { STATE_ALL_RED_NORTH_TO_EAST, STATE_ALL_RED_NORTH_TO_EAST, STATE_FLASHING_YELLOW },
        enterNorthYellow,
        updateNorthYellow,
        YELLOW_DURATION },
    { { STATE_EAST_GREEN, STATE_EAST_GREEN, STATE_FLASHING_YELLOW },
        enterAllRed,
        updateAllRed,
        ALL_RED_DURATION },
    { { STATE_FLASHING_YELLOW, STATE_FLASHING_YELLOW, STATE_EAST_GREEN },
        enterFlashingYellow,
        updateFlashingYellow,
        ULONG_MAX }
};
