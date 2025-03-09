#include "led.h"
#include <Arduino_FreeRTOS.h>

static SemaphoreHandle_t ledMutex = NULL;

static volatile bool isBlinking[14] = { false }; // pins 0-13

bool ledInit(uint8_t pin)
{
    // Create mutex if not already created
    if (ledMutex == NULL) {
        ledMutex = xSemaphoreCreateMutex();
        if (ledMutex == NULL) {
            Serial.println("Failed to create LED mutex!");
            return false;
        }
    }

    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    Serial.println("LED initialized");
    return true;
}

void ledTurnOn(uint8_t pin)
{
    if (xSemaphoreTake(ledMutex, portMAX_DELAY) == pdTRUE) {
        digitalWrite(pin, HIGH);
        xSemaphoreGive(ledMutex);
    }
}

void ledTurnOff(uint8_t pin)
{
    if (xSemaphoreTake(ledMutex, portMAX_DELAY) == pdTRUE) {
        digitalWrite(pin, LOW);
        xSemaphoreGive(ledMutex);
    }
}

void ledToggle(uint8_t pin)
{
    if (xSemaphoreTake(ledMutex, portMAX_DELAY) == pdTRUE) {
        digitalWrite(pin, !digitalRead(pin));
        xSemaphoreGive(ledMutex);
    }
}

void ledBlinkNTimes(uint8_t pin, uint8_t n, uint16_t onTime, uint16_t offTime)
{
    if (xSemaphoreTake(ledMutex, portMAX_DELAY) == pdTRUE) {
        isBlinking[pin] = true;

        for (uint8_t i = 0; i < n; i++) {
            digitalWrite(pin, HIGH);
            vTaskDelay(pdMS_TO_TICKS(onTime));
            digitalWrite(pin, LOW);
            vTaskDelay(pdMS_TO_TICKS(offTime));
        }

        isBlinking[pin] = false;
        digitalWrite(pin, LOW);
        xSemaphoreGive(ledMutex);
    }
}

bool isLedBlinking(uint8_t pin)
{
    bool status = false;
    if (xSemaphoreTake(ledMutex, portMAX_DELAY) == pdTRUE) {
        status = isBlinking[pin];
        xSemaphoreGive(ledMutex);
    }
    return status;
}