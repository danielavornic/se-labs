#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#define BUTTON_CHECK_INTERVAL 50
#define BLINK_INTERVAL 500
#define COUNTER_CHECK_INTERVAL 100
#define IDLE_INTERVAL 1000

void initTaskManager();
void taskButtonLed();
void taskBlinkingLed();
void taskCounterButtons();
void taskIdle();

#endif
