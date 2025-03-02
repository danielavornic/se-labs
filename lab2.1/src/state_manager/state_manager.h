#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

struct SystemState {
    bool ledOneState; // Task 1 provides
    bool ledTwoState; // Task 2 provides
    int counter; // Task 3 provides
};

// global state
extern volatile SystemState globalState;

// provider functions
void initStateManager();
void updateLedOneState(bool state);
void updateLedTwoState(bool state);
void incrementCounter();
void decrementCounter();

// consumer functions
bool getLedOneState();
bool getLedTwoState();
int getCounter();

#endif
