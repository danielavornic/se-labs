#include "task_manager.h"
#include "../button/button.h"
#include "../led/led.h"
#include "../state_manager/state_manager.h"
#include <Arduino.h>
#include <stdio.h>

unsigned long lastButtonCheck = 0;
unsigned long lastBlinkTime = 0;
unsigned long lastCounterCheck = 0;
unsigned long lastIdleReport = 0;

void initTaskManager()
{
    initButtons();
    initLeds();
}

// task 1: button LED Control
void taskButtonLed()
{
    unsigned long currentTime = millis();

    if (currentTime - lastButtonCheck >= BUTTON_CHECK_INTERVAL) {
        if (isButtonPressed(BUTTON_1_PIN)) {
            bool newState = !getLedOneState();
            updateLedOneState(newState);
            setLedState(LED_1_PIN, newState);
            printf("Button 1 pressed: LED1 is now %s\n", newState ? "ON" : "OFF");
        }
        lastButtonCheck = currentTime;
    }
}

// task 2: blinking LED (only when LED1 is off)
void taskBlinkingLed()
{
    unsigned long currentTime = millis();

    if (currentTime - lastBlinkTime >= BLINK_INTERVAL) {
        // if LED1 is OFF
        if (!getLedOneState()) {
            bool newState = !getLedTwoState();
            updateLedTwoState(newState);
            setLedState(BLINKING_LED_PIN, newState);
        } else {
            // turn off LED2 when LED1 is ON
            if (getLedTwoState()) {
                updateLedTwoState(false);
                setLedState(BLINKING_LED_PIN, false);
            }
        }

        lastBlinkTime = currentTime;
    }
}

// task 3: counter buttons
void taskCounterButtons()
{
    unsigned long currentTime = millis();
    if (currentTime - lastCounterCheck >= COUNTER_CHECK_INTERVAL) {
        if (isButtonPressed(BUTTON_2_PIN)) {
            incrementCounter();
            printf("Button 2 pressed: Counter incremented to %d\n", getCounter());
        }
        if (isButtonPressed(BUTTON_3_PIN)) {
            decrementCounter();
            printf("Button 3 pressed: Counter decremented to %d\n", getCounter());
        }
        lastCounterCheck = currentTime;
    }
}

// idle task: status reporting
void taskIdle()
{
    unsigned long currentTime = millis();
    if (currentTime - lastIdleReport >= IDLE_INTERVAL) {
        printf("System Status:\n");
        printf("LED1: %s\n", getLedOneState() ? "ON" : "OFF");
        printf("LED2: %s\n", getLedTwoState() ? "ON" : "OFF");
        printf("Counter: %d\n", getCounter());
        lastIdleReport = currentTime;
    }
}
