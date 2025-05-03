#include "potentiometer.h"

void initPotentiometer()
{
    pinMode(POT_PIN, INPUT);
}

int readPotentiometer()
{
    int rawValue = analogRead(POT_PIN);
    int mappedValue = map(rawValue, ADC_MIN, ADC_MAX, POSITION_MIN, POSITION_MAX);
    return constrain(mappedValue, POSITION_MIN, POSITION_MAX);
}