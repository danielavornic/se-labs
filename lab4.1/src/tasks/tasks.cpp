#include "tasks.h"
#include "../config/config.h"
#include "../globals/globals.h"
#include "../relay/relay.h"
#include "../serial_comm/serial_comm.h"
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include <stdio.h>
#include <string.h>
#include <task.h>

void createTasks()
{
    xTaskCreate(
        serialCommandHandler,
        "SerialCmd",
        COMMAND_PROCESSOR_TASK_STACK_SIZE,
        NULL,
        TASK_PRIORITY,
        NULL);
}

void serialCommandHandler(void* pvParameters)
{
    struct Command cmd;

    while (1) {
        if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
            if (scanf("%s %s", cmd.command, cmd.modifier) == 2) {
                printf("Received: %s %s\n", cmd.command, cmd.modifier);

                if (strcmp(cmd.command, "relay") == 0) {
                    bool currentState = getRelayState();
                    if (strcmp(cmd.modifier, "on") == 0) {
                        if (currentState) {
                            printf("Relay is already ON\n");
                        } else {
                            setRelay(true);
                            printf("Relay turned ON\n");
                        }
                        printRelayStatus();
                    } else if (strcmp(cmd.modifier, "off") == 0) {
                        if (!currentState) {
                            printf("Relay is already OFF\n");
                        } else {
                            setRelay(false);
                            printf("Relay turned OFF\n");
                        }
                        printRelayStatus();
                    } else {
                        printf("Unknown modifier. Use 'on' or 'off'\n");
                    }
                } else {
                    printf("Unknown command. Use 'relay'\n");
                }
            }
            xSemaphoreGive(serialMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}