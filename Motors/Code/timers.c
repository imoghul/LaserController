#include "msp430.h"
#include "timers.h"
#include "ports.h"
#include "macros.h"

unsigned int debounce_count1, debounce_count2;
volatile unsigned int debouncing1, debouncing2;
volatile unsigned int debounce_thresh1 = 10, debounce_thresh2 = 10;

void Init_Timers(void) {
    Init_Timer_B3();
}

void Init_Timer_B3(void) {
    TB3CTL = TBSSEL__SMCLK;
    TB3CTL |= MC__UP;
    TB3CTL |= TBCLR;
    TB3CTL |= ID__2; // Divide clock by 4

    TB3CCR0 = PULSE_PERIOD;

    TB3CCTL1 = OUTMOD_7;
    MOTOR1_P = 0;

    TB3CCTL2 = OUTMOD_7;
    MOTOR2_P = 0;

    TB3CCTL3 = OUTMOD_7;
    MOTOR3_P = 0;

    TB3CCTL4 = OUTMOD_7;
    MOTOR4_P = 0;

    TB3CCTL5 = OUTMOD_7;
    MOTOR5_P = 0;

}

