#include "button.h"

static bool lastButtonState = HIGH;
static unsigned long lastDebounceTime = 0;
static const unsigned long debounceDelay = 50;

void initButton()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

bool isButtonPressed()
{
    bool buttonState = digitalRead(BUTTON_PIN);
    bool buttonPressed = false;

    if (buttonState != lastButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (buttonState == LOW) {
            buttonPressed = true;
        }
    }

    lastButtonState = buttonState;
    return buttonPressed;
}
