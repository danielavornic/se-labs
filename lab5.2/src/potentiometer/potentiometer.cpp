#include "potentiometer.h"

void initPotentiometer()
{
    pinMode(POT_IN, INPUT);
}

int readSetpointFromPot()
{
    return map(analogRead(POT_IN), 0, 1023, 0, 600);
}
