#include "state_manager.h"
#include <stdio.h>

volatile SystemState globalState = {
    .ledOneState = false,
    .ledTwoState = false,
    .counter = 0,
};

void initStateManager()
{
    globalState.ledOneState = true;
    globalState.ledTwoState = false;
    globalState.counter = 0;
}

void updateLedOneState(bool state)
{
    globalState.ledOneState = state;
}

void updateLedTwoState(bool state)
{
    globalState.ledTwoState = state;
}

void incrementCounter()
{
    globalState.counter++;
}

void decrementCounter()
{
    if (globalState.counter > 0) {
        globalState.counter--;
    }
}

bool getLedOneState()
{
    return globalState.ledOneState;
}

bool getLedTwoState()
{
    return globalState.ledTwoState;
}

int getCounter()
{
    return globalState.counter;
}
