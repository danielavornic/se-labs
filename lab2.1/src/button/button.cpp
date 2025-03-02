#include "button.h"
#include <Arduino.h>

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
    int buttonIndex = pin - 2; // Convert pin number to array index
    bool reading = !digitalRead(pin); // Inverted because of INPUT_PULLUP
    bool pressed = reading != lastButtonState[buttonIndex];

    if (pressed) {
        // reset the debouncing timer
        lastDebounceTime[buttonIndex] = millis();
    }

    // if enough time has passed, the button state stable
    bool debounced = (millis() - lastDebounceTime[buttonIndex]) > DEBOUNCE_DELAY;

    if (debounced) {
        // if the button state has changed
        if (reading != buttonState[buttonIndex]) {
            buttonState[buttonIndex] = reading;

            // on button press
            if (buttonState[buttonIndex] == true) {
                lastButtonState[buttonIndex] = reading;
                return true;
            }
        }
    }

    lastButtonState[buttonIndex] = reading;
    return false;
}
