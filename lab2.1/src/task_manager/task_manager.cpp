#include "task_manager.h"
#include "../button/button.h"
#include "../led/led.h"
#include "../state_manager/state_manager.h"
#include "../sys_timer/sys_timer.h"
#include <Arduino.h>
#include <stdio.h>

void initTaskManager()
{
    initButtons();
    initLeds();
}

void taskButtonLed()
{
    if (isButtonPressed(BUTTON_1_PIN)) {
        bool newState = !getLedOneState();
        updateLedOneState(newState);
        setLedState(LED_1_PIN, newState);

        printf("Button 1 pressed: LED1 is now %s\n\n", newState ? "ON" : "OFF");
    }
}

void taskBlinkingLed()
{
    // only blink when LED1 is off
    if (!getLedOneState()) {
        bool newState = !getLedTwoState();
        updateLedTwoState(newState);
        setLedState(BLINKING_LED_PIN, newState);
    } else {
        updateLedTwoState(false);
        setLedState(BLINKING_LED_PIN, false);
    }
}

void taskCounterButtons()
{
    if (isButtonPressed(BUTTON_2_PIN)) {
        incrementCounter();
        printf("Button 2 pressed: Counter incremented to %d\n\n", getCounter());
    }

    if (isButtonPressed(BUTTON_3_PIN)) {
        decrementCounter();
        printf("Button 3 pressed: Counter decremented to %d\n\n", getCounter());
    }
}

void taskIdle()
{
    int counterValue = getCounter();
    int blinkingLedTaskRec = BLINKING_LED_TASK_REC + (counterValue * 50);

    printf("System Status:\n");
    printf("LED1: %s\n", getLedOneState() ? "ON" : "OFF");
    printf("LED2: %s\n", getLedTwoState() ? "ON" : "OFF");

    printf("Counter: %d\n", getCounter());
    printf("LED2 blink interval: %d ms\n\n", blinkingLedTaskRec);
}
