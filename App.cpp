#include <Arduino.h>

#include "LedMatrix.h"
#include "App.h"

extern int latchPin = 8;
extern int clockPin = 12;
extern int data_R1 = 10;
extern int data_R2 = 11;
extern int en_74138 = 2;
extern int la_74138 = 3;
extern int lb_74138 = 4;
extern int lc_74138 = 5;
extern int ld_74138 = 6;

App::App()
    : ledMatrix(new LedMatrix(LED_R_PIN, LED_G_PIN, LED_B_Pin))
{
}

void App::setup()
{
    // Set up Timer2 as the scanning interrupt timer

    cli();

    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2 = 0;

    // Set 1024 prescaler
    TCCR2B |= (1 << CS22) | (1 << CS20);

    // 160Hz scan rate = 10 frames / second (16 pairs of rows)
    // 97 = (16,000,000 / (1024 * 160)) - 1
    OCR2A = 97;

    // turn on CTC mode
    TCCR2A |= (1 << WGM21);
    // enable timer compare interrupt
    TIMSK2 |= (1 << OCIE2A);

    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(data_R1, OUTPUT);
    pinMode(data_R2, OUTPUT);

    pinMode(en_74138, OUTPUT);
    pinMode(la_74138, OUTPUT);
    pinMode(lb_74138, OUTPUT);
    pinMode(lc_74138, OUTPUT);
    pinMode(ld_74138, OUTPUT);

    digitalWrite(en_74138, LOW);
    digitalWrite(data_R1, HIGH);
    digitalWrite(data_R2, HIGH);

    sei();
}
