#ifndef LED_H
#define LED_H

#define LED_1_PIN 13 // controlled by Button1
#define BLINKING_LED_PIN 12 // blinks when LED1 is off

void initLeds();
void setLedState(int pin, bool state);
void toggleLed(int pin);

#endif
