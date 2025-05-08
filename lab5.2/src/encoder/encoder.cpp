#include "encoder.h"

void initEncoder()
{
    pinMode(ENCODER_A, INPUT);
}

int measureSpeed()
{
    unsigned long pulseDuration = pulseIn(ENCODER_A, HIGH);
    if (pulseDuration == 0) {
        printf("Warning: pulseIn timeout or no pulse detected.\n");
        return 0;
    }
    return ENCODER_CALIBRATION * ((60 * 1000 * 10) / pulseDuration);
}
