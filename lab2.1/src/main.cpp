#include "serial_comm/serial_comm.h"
#include "state_manager/state_manager.h"
#include "task_manager/task_manager.h"

void setup()
{
    serialInit();
    initStateManager();
    initTaskManager();
    printf("App Lab 2.1 Started\n");
}

void loop()
{
    taskButtonLed(); // Task 1
    taskBlinkingLed(); // Task 2
    taskCounterButtons(); // Task 3
    taskIdle(); // Idle Task
}
