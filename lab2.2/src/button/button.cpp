#include "button.h"
#include "../config/config.h"

void initButton()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

bool isButtonPressed()
{
    return digitalRead(BUTTON_PIN) == LOW;
}
