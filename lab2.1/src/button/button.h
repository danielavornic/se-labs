#ifndef BUTTON_H
#define BUTTON_H

#define BUTTON_1_PIN 2 // controls LED1
#define BUTTON_2_PIN 3 // increments counter
#define BUTTON_3_PIN 4 // decrements counter

#define DEBOUNCE_DELAY 50

void initButtons();
bool isButtonPressed(int pin);

#endif
