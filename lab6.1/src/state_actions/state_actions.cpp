#include "state_actions.h"

static uint32_t blinkTime;

void enterStateOff(void) { ledOff(); }
void updateStateOff(void) { }

void enterStateOn(void) { ledOn(); }
void updateStateOn(void) { }

void enterStateBlink(void)
{
    ledOn();
    blinkTime = millis();
}

void updateStateBlink(void)
{
    if (millis() - blinkTime >= BLINK_MS) {
        ledToggle();
        blinkTime = millis();
    }
}