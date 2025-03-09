#include "button.h"

static uint8_t lastButtonState = HIGH;
static unsigned long lastDebounceTime = 0;
static const unsigned long debounceDelay = 50;

void buttonInit(uint8_t pin)
{
    pinMode(pin, INPUT_PULLUP);
    Serial.println("Button initialized");
}

bool isButtonPressed(uint8_t pin)
{
    static uint8_t lastState = HIGH;
    uint8_t currentState = digitalRead(pin);
    bool pressed = false;

    if (currentState == LOW && lastState == HIGH) {
        pressed = true;
    }

    lastState = currentState;
    return pressed;
}