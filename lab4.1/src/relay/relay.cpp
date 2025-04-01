#include "relay.h"
#include "../config/config.h"

static bool relayState = false;

void initRelay()
{
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);
}

void setRelay(bool state)
{
    relayState = state;
    digitalWrite(RELAY_PIN, state ? HIGH : LOW);
}

bool getRelayState()
{
    return relayState;
}