#include "button.h"

#define DEBOUNCE_DELAY_MS 50

static uint32_t lastDebounceTime = 0;
static bool lastState = HIGH;
static bool buttonPressed = false;

void initButton()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    lastDebounceTime = 0;
    lastState = HIGH;
    buttonPressed = false;
}

bool isButtonPressed()
{
    bool currentState = digitalRead(BUTTON_PIN);

    if (currentState != lastState && (millis() - lastDebounceTime) > DEBOUNCE_DELAY_MS) {
        lastDebounceTime = millis();
        lastState = currentState;

        if (currentState == LOW) {
            buttonPressed = true;
        }
    }

    // trigger once per press
    if (buttonPressed) {
        buttonPressed = false;
        return true;
    }

    return false;
}
