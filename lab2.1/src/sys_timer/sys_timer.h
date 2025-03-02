#ifndef SYS_TIMER_H
#define SYS_TIMER_H

#include <Arduino.h>

#define SYS_TICK 1 // 1ms system tick

#define BUTTON_LED_TASK_REC (100 / SYS_TICK)
#define BLINKING_LED_TASK_REC (200 / SYS_TICK)
#define COUNTER_BUTTONS_TASK_REC (250 / SYS_TICK)

void initSystemTimer();
void timeScheduler();

extern int buttonLedTaskCounter;
extern int blinkingLedTaskCounter;
extern int counterButtonsTaskCounter;

#endif