#include "msp430.h"
#include "timers.h"
#include "ports.h"
#include "adc.h"
#include "macros.h"

unsigned int debounce_count1, debounce_count2;
volatile unsigned int debouncing1, debouncing2;
volatile unsigned int debounce_thresh1 = 10, debounce_thresh2 = 10;
extern volatile unsigned int DAC_setpoint;
unsigned int DAC_current;

void Init_Timers(void) {
    Init_Timer_B0();
    Init_Timer_B1();
}

void Init_Timer_B0(void) {
    TB0CTL = TBSSEL__SMCLK; // SMCLK source
    TB0CTL |= TBCLR; // Resets TB0R, clock divider, count direction
    TB0CTL |= MC__CONTINOUS; // Continuous up
    TB0CTL |= ID__2; // Divide clock by 2
    TB0EX0 = TBIDEX__8; // Divide clock by an additional 8

    TB0CCR0 = TB0CCR0_INTERVAL; // CCR0
    TB0CCTL0 |= CCIE; // CCR0 enable interrupt

    TB0CCR1 = TB0CCR1_INTERVAL; // CCR1
    TB0CCTL1 &= ~CCIE; // CCR1 enable interrupt

    TB0CCR2 = TB0CCR2_INTERVAL; // CCR2
    TB0CCTL2 &= ~CCIE; // CCR2 enable interrupt

    TB0CTL &= ~TBIE & ~TBIFG; // Disable Overflow Interrupt
    TB0CTL &= ~TBIFG; // Clear Overflow Interrupt flag
}

void Init_Timer_B1(void) {
    TB1CTL = TBSSEL__SMCLK; // SMCLK source
    TB1CTL |= TBCLR; // Resets TB0R, clock divider, count direction
    TB1CTL |= MC__CONTINOUS; // Continuous up
    //    TB1CTL |= ID__2; // Divide clock by 4
    //    TB1EX0 = TBIDEX__0; // Divide clock by an additional 8

    TB1CCR0 = TB1CCR0_INTERVAL; // CCR0
    TB1CCTL0 &= ~CCIE; // CCR0 enable interrupt

    TB1CCR1 = 1;//TB1CCR1_INTERVAL; // CCR1
    TB1CCTL1 &= ~CCIE; // CCR1 enable interrupt

    TB1CCR2 = TB1CCR2_INTERVAL; // CCR2
    TB1CCTL2 &= ~CCIE; // CCR2 enable interrupt

    TB1CTL &= ~TBIE & ~TBIFG; // Disable Overflow Interrupt
    TB1CTL &= ~TBIFG; // Clear Overflow Interrupt flag
}


//===========================================================================
// Function name: Timer0_B0_ISR
//
// Description: Increments Time_Sequence and update_display
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: no global values
//
// Author: Ibrahim Moghul
// Date: Feb 2022
// Compiler: Built with IAR Embedded Workbench Version: (7.21.1)
//===========================================================================
int abs(int n) {
    return (n > 0 ? n : -n);
}

#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void) {
    //------------------------------------------------------------------------------
    // TimerB0 0 Interrupt handler
    //----------------------------------------------------------------------------
    // start ADC sample
    ADCCTL0 |= ADCENC;
    ADCCTL0 |= ADCSC;

    // set DAC
    if(abs(DAC_setpoint - DAC_current) >= DAC_STEP) {
        DAC_current += DAC_STEP;
    } else {
        if(DAC_setpoint == 0) DAC_setpoint = 1000;
        else DAC_setpoint = 0;
    }

    SAC3DAT = DAC_current;


    TB0CCR0 += TB0CCR0_INTERVAL; // Add Offset to TBCCR0
    //----------------------------------------------------------------------------
}


//===========================================================================
// Function name: TIMER0_B1_ISR
//
// Description: Timer 1 handles switch debounce, and Timer 2 handles
// LCD blinking
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: no global values
//
// Author: Ibrahim Moghul
// Date: Feb 2022
// Compiler: Built with IAR Embedded Workbench Version: (7.21.1)
//===========================================================================
#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void) {
    //----------------------------------------------------------------------------
    // TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
    //----------------------------------------------------------------------------
    switch(__even_in_range(TB0IV, 14)) {
        case 0:
            break; // No interrupt

        case 2: // CCR1 not used
            if(debouncing1 == TRUE) debounce_count1++;

            if (debounce_count1 > debounce_thresh1) {
                debounce_count1 = 0;
                debouncing1 = FALSE;
                P4IE |= SW1;
                TB0CCTL1 &= ~CCIE;
            }

            TB0CCR1 += TB0CCR1_INTERVAL; // Add Offset to TBCCR1

            break;

        case 4: // CCR2 not used
            if(debouncing2 == TRUE) debounce_count2++;

            if (debounce_count2 > debounce_thresh2) {
                debounce_count2 = 0;
                debouncing2 = FALSE;
                P2IE |= SW2;
                TB0CCTL2 &= ~CCIE;
            }

            TB0CCR2 += TB0CCR2_INTERVAL; // Add Offset to TBCCR2

            break;

        case 14: // overflow

            break;

        default:
            break;
    }

    //----------------------------------------------------------------------------
}

#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void) {
    //------------------------------------------------------------------------------
    // TimerB0 0 Interrupt handler
    //----------------------------------------------------------------------------

    TB1CCR0 += TB1CCR0_INTERVAL;
    //----------------------------------------------------------------------------
}

#pragma vector=TIMER1_B1_VECTOR
__interrupt void TIMER1_B1_ISR(void) {
    //----------------------------------------------------------------------------
    // TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
    //----------------------------------------------------------------------------
    switch(__even_in_range(TB1IV, 14)) {
        case 0:
            break; // No interrupt

        case 2:


            break;

        case 4:
            //TB1CCTL2 &= ~CCIE;
            break;

        case 14: // overflow

            break;

        default:
            break;
    }

    //----------------------------------------------------------------------------
}

//#pragma vector = TIMER3_B0_VECTOR
//__interrupt void Timer3_B0_ISR(void) {
//  return;
//}