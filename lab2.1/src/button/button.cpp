#include "button.h"
#include <Arduino.h>

// for each button
static unsigned long lastDebounceTime[3] = { 0, 0, 0 };
static bool lastButtonState[3] = { false, false, false };
static bool buttonState[3] = { false, false, false };

void initButtons()
{
    pinMode(BUTTON_1_PIN, INPUT_PULLUP);
    pinMode(BUTTON_2_PIN, INPUT_PULLUP);
    pinMode(BUTTON_3_PIN, INPUT_PULLUP);
}

bool isButtonPressed(int pin)
{
    static bool lastState[3] = { false, false, false };
    int buttonIndex = pin - 2;

    // inverted because of INPUT_PULLUP
    bool currentState = !digitalRead(pin);

    bool result = currentState && !lastState[buttonIndex];

    lastState[buttonIndex] = currentState;

    return result;
}
