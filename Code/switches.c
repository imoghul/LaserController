#include "msp430.h"
#include "switches.h"
#include "ports.h"
#include "macros.h"
#include "timers.h"
#include "motor.h"
#include <string.h>

volatile unsigned int sw1Okay, sw2Okay;
volatile unsigned int count_debounce_SW1, count_debounce_SW2;
volatile unsigned int sw1_pos, sw2_pos;
extern volatile unsigned int debounce_count1, debounce_count2;
extern volatile unsigned int debouncing1, debouncing2;
extern volatile unsigned char pulseTrainSent;
//===========================================================================
// Function name: switchP4_interrupt
//
// Description: This is the switch 1 interrupt, turns off LCD_BACKLITE and its
// blinking timer
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

#pragma vector=PORT4_VECTOR
__interrupt void switchP4_interrupt(void) {
    if(P4IFG & SW1 && debouncing1 == FALSE) {
        P4IE &= ~SW1;
        P4IFG &= ~SW1;
        TB0CCTL1 &= ~CCIFG;
        TB0CCR1 = TB0R + TB0CCR1_INTERVAL;
        TB0CCTL1 |= CCIE;
        debouncing1 = TRUE;

    }
}

//===========================================================================
// Function name: switchP4_interrupt
//
// Description: This is the switch 2 interrupt, turns off LCD_BACKLITE and its
// blinking timer
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
#pragma vector=PORT2_VECTOR
__interrupt void switchP2_interrupt(void) {
    if(P2IFG & SW2 && debouncing2 == FALSE) {
        P2IE &= ~SW2;
        P2IFG &= ~SW2;
        TB0CCTL2 &= ~CCIFG;
        TB0CCR2 = TB0R + TB0CCR2_INTERVAL;
        TB0CCTL2 |= CCIE;
        debouncing2 = TRUE;

    }
}

