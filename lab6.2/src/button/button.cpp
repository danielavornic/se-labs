#include "button.h"

static struct {
    uint8_t pin;
    bool lastState;
    bool consumed;
    unsigned long lastDebounceTime;
} buttons[] = {
    { BUTTON_PIN, HIGH, false, 0 },
    { NIGHT_MODE_BUTTON_PIN, HIGH, false, 0 }
};

static const unsigned long debounceDelay = 50;

void initButtons()
{
    pinMode(buttons[0].pin, INPUT_PULLUP);
    pinMode(buttons[1].pin, INPUT_PULLUP);
}

static bool checkButton(uint8_t buttonIndex)
{
    bool buttonState = digitalRead(buttons[buttonIndex].pin);
    bool buttonPressed = false;

    if (buttonState != buttons[buttonIndex].lastState) {
        buttons[buttonIndex].lastDebounceTime = millis();
        if (buttonState == HIGH) {
            buttons[buttonIndex].consumed = false;
        }
    }

    if ((millis() - buttons[buttonIndex].lastDebounceTime) > debounceDelay) {
        if (buttonState == LOW && !buttons[buttonIndex].consumed) {
            buttonPressed = true;
            buttons[buttonIndex].consumed = true;
        }
    }

    buttons[buttonIndex].lastState = buttonState;
    return buttonPressed;
}

bool isButtonPressed()
{
    return checkButton(0);
}

bool isNightModeButtonPressed()
{
    return checkButton(1);
}
