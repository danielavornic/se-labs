#include "serial_comm/serial_comm.h"
#include "state_manager/state_manager.h"
#include "sys_timer/sys_timer.h"
#include "task_manager/task_manager.h"

void setup()
{
    serialInit();
    initStateManager();
    initSystemTimer();
    initTaskManager();

    printf("Lab 2.1 started with timer-based scheduler\n");
}

void loop()
{
    taskIdle();
    delay(1000 * SYS_TICK); // 1 second
}
