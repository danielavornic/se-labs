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

        printf("Button 1 pressed: LED1 is now %s\n", newState ? "ON" : "OFF");
    }
}

void taskBlinkingLed()
{
    static int ledStateCounter = 0;

    if (!getLedOneState()) {
        // how long LED2 stays in each state
        // minimum time is 100ms, each counter unit adds 100ms
        int blinkDuration = 100 + (getCounter() * 100);

        ledStateCounter += SYS_TICK;

        // check if it's time to toggle the LED
        if (ledStateCounter >= blinkDuration) {
            bool newState = !getLedTwoState();
            updateLedTwoState(newState);
            setLedState(BLINKING_LED_PIN, newState);

            ledStateCounter = 0;
        }

        return;
    }

    // turn off LED2 when LED1 is ON
    if (getLedTwoState()) {
        updateLedTwoState(false);
        setLedState(BLINKING_LED_PIN, false);
    }

    ledStateCounter = 0;
}

void taskCounterButtons()
{
    if (getLedOneState()) {
        return; // skip if LED1 is ON
    }

    static bool button2LastState = false;
    static bool button3LastState = false;

    bool button2CurrentState = isButtonPressed(BUTTON_2_PIN);
    bool button3CurrentState = isButtonPressed(BUTTON_3_PIN);

    if (button2CurrentState && !button2LastState) {
        incrementCounter();
        printf("Button 2 pressed: Counter incremented to %d\n", getCounter());
    }

    if (button3CurrentState && !button3LastState) {
        decrementCounter();
        printf("Button 3 pressed: Counter decremented to %d\n", getCounter());
    }

    // Update last states
    button2LastState = button2CurrentState;
    button3LastState = button3CurrentState;
}

void taskIdle()
{
    printf("System Status:\n");
    printf("LED1: %s\n", getLedOneState() ? "ON" : "OFF");
    printf("LED2: %s\n", getLedTwoState() ? "ON" : "OFF");
    printf("Counter: %d\n", getCounter());
    printf("LED2 blink duration: %d ms\n", 100 + (getCounter() * 100));
}
