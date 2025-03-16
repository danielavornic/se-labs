#include "ultrasonic.h"
#include "../config/config.h"

void initUltrasonic()
{
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

float getDistance()
{
    // #ifdef WOKWI
    //     static int counter = 0;
    //     counter++;
    //     if (counter % 50 < 25) {
    //         return 5.0;
    //     } else {
    //         return 15.0;
    //     }
    // #else
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH);
    // 0.034 = speed of sound in cm/us
    // pulseIn -> duration of the pulse in microseconds
    // divide by 2 to get the round trip distance
    float distance = duration * 0.034 / 2;

    return distance;
    // #endif
}