#include "sys_timer.h"
#include "../state_manager/state_manager.h"
#include "../task_manager/task_manager.h"
#include <Arduino.h>

int buttonLedTaskCounter = BUTTON_LED_TASK_REC;
int blinkingLedTaskCounter = BLINKING_LED_TASK_REC;
int counterButtonsTaskCounter = COUNTER_BUTTONS_TASK_REC;

void initSystemTimer()
{
    cli(); // disable interrupts

    // reset registers
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;

    // compare match register for 1ms increments
    OCR1A = 62;

    // turn on CTC mode
    // this mode is used to compare the timer value with the OCR1A register
    TCCR1B |= (1 << WGM12);

    // set CS12 bit for 256 prescaler
    TCCR1B |= (1 << CS12);

    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);

    sei(); // enable interrupts
}

// routine for timer compare interrupt
ISR(TIMER1_COMPA_vect)
{
    timeScheduler();
}

void timeScheduler()
{
    int dynamicBlinkingLedTaskRec = BLINKING_LED_TASK_REC + (getCounter() * 50);

    if (--buttonLedTaskCounter <= 0) {
        buttonLedTaskCounter = BUTTON_LED_TASK_REC;
        taskButtonLed();
    }

    if (--blinkingLedTaskCounter <= 0) {
        blinkingLedTaskCounter = dynamicBlinkingLedTaskRec;
        taskBlinkingLed();
    }

    if (--counterButtonsTaskCounter <= 0) {
        counterButtonsTaskCounter = COUNTER_BUTTONS_TASK_REC;
        taskCounterButtons();
    }
}