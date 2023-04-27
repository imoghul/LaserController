#include "msp430.h"
#include "timers.h"
#include "ports.h"
#include "macros.h"

volatile unsigned long long encoderVal, encoderValBuffer;
char encoderCounter,encoderRisingEdge;
void Init_Timers(void) {
    Init_Timer_B0();
    Init_Timer_B3();
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
    //TB0CCTL1 |= CCIE; // CCR1 enable interrupt
    
    TB0CCR2 = TB0CCR2_INTERVAL; // CCR2
    //TB0CCTL2 |= CCIE; // CCR2 enable interrupt
    
    TB0CTL &= ~TBIE & ~TBIFG; // Disable Overflow Interrupt
    //TB0CTL &= ~TBIFG; // Clear Overflow Interrupt flag
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

#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void) {
    //------------------------------------------------------------------------------
    // TimerB0 0 Interrupt handler
    //----------------------------------------------------------------------------
    
    P1OUT ^= ENCODER_CLK;
    encoderRisingEdge = !encoderRisingEdge;
    if(encoderRisingEdge){
      encoderValBuffer = encoderValBuffer<<1 + P1IN&ENCODER_DATA; 
      if(++encoderCounter>=12){
        encoderCounter = 0;
        encoderVal = encoderValBuffer & 0x0FFF;
      }
    }
    
    //if(encoderVal>0){
    //  int x = 0;
    //}

    
    TB0CCR0 += TB0CCR0_INTERVAL; // Add Offset to TBCCR0
    //----------------------------------------------------------------------------
}



