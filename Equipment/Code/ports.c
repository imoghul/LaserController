//==============================================================================
// File Name : ports.c
//
// Description: This file contains the Initialization for all port pins
//
// Author: Ibrahim Moghul
// Date: Feb 2022
// Compiler: Built with IAR Embedded Workbench Version: 7.21.1
//==============================================================================
#include "ports.h"
#include "msp430.h"

//===========================================================================
// Function name: Init_Ports
//
// Description: Initialize all ports
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: no global variables used
//
// Author: Ibrahim Moghul
// Date: Feb 2022
// Compiler: Built with IAR Embedded Workbench Version: (7.21.1)
//===========================================================================
void Init_Ports(void) {
    Init_Port1();
    Init_Port2();
    Init_Port3(USE_GPIO);
    Init_Port4();
    Init_Port5();
    Init_Port6();
}

//===========================================================================
// Function name: Init_Port1
//
// Description: Initialize all pins on port 1
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: no global variables used
//
// Author: Ibrahim Moghul
// Date: Feb 2022
// Compiler: Built with IAR Embedded Workbench Version: (7.21.1)
//===========================================================================
void Init_Port1() {
    P1OUT = 0x00;
    P1DIR = 0x00;

    P1SEL0 &= ~RED_LED;
    P1SEL1 &= ~RED_LED;
    P1DIR |= RED_LED;
    P1OUT &= ~RED_LED;

    //P1SEL0 |= A1_SEEED;
    //P1SEL1 |= A1_SEEED;
    P1SELC |= A1_SEEED;

    P1SEL0 &= ~P1_2;
    P1SEL1 &= ~P1_2;
    P1DIR &= ~P1_2;

    P1SEL0 &= ~P1_3;
    P1SEL1 &= ~P1_3;
    P1DIR &= ~P1_3;

    P1SELC |= HEATER_ADC;

    P1SELC |= HEATER_DAC;

    P1SEL1 &= ~UCA0RXD;
    P1SEL0 |= UCA0RXD;

    P1SEL1 &= ~UCA0TXD;
    P1SEL0 |= UCA0TXD;
}

//===========================================================================
// Function name: Init_Port2
//
// Description: Initialize all pins on port 2
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: no global variables used
//
// Author: Ibrahim Moghul
// Date: Feb 2022
// Compiler: Built with IAR Embedded Workbench Version: (7.21.1)
//===========================================================================
void Init_Port2() {
    P2OUT = 0x00;
    P2DIR = 0x00;

    P2SEL0 &= ~P2_0;
    P2SEL1 &= ~P2_0;
    P2DIR &= ~P2_0;

    P2SEL0 &= ~P2_1;
    P2SEL1 &= ~P2_1;
    P2DIR &= ~P2_1;

    P2SEL0 &= ~P2_2;
    P2SEL1 &= ~P2_2;
    P2DIR &= ~P2_2;

    P2SEL0 &= ~SW2;
    P2SEL1 &= ~SW2;
    P2OUT |= SW2;
    P2DIR &= ~SW2;
    P2REN |= SW2;
    P2IES |= SW2;
    P2IFG &= ~SW2;
    P2IE &= ~SW2;

    P2SEL0 &= ~P2_4;
    P2SEL1 &= ~P2_4;
    P2DIR &= ~P2_4;

    P2SEL0 &= ~P2_5;
    P2SEL1 &= ~P2_5;
    P2DIR &= ~P2_5;

    P2SEL0 &= ~LFXOUT;
    P2SEL1 |= LFXOUT;

    P2SEL0 &= ~LFXIN;
    P2SEL1 |= LFXIN;
}

//===========================================================================
// Function name: Init_Port3
//
// Description: Initialize all pins on port 3
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: no global variables used
//
// Author: Ibrahim Moghul
// Date: Feb 2022
// Compiler: Built with IAR Embedded Workbench Version: (7.21.1)
//===========================================================================
void Init_Port3(char smclk) {
    P3OUT = 0x00;
    P3DIR = 0x00;

    P3SEL0 &= ~TEST_PROBE;
    P3SEL1 &= ~TEST_PROBE;
    P3DIR &= ~TEST_PROBE;

    P3SEL0 &= ~P3_1;
    P3SEL1 &= ~P3_1;
    P3DIR &= ~P3_1;

    P3SEL0 |= OA2N;
    P3SEL1 |= OA2N;

    P3SEL0 &= ~P3_3;
    P3SEL1 &= ~P3_3;
    P3DIR &= ~P3_3;

    P3SEL0 &= ~P3_4;
    P3SEL1 &= ~P3_4;
    P3DIR &= ~P3_4;

    P3SEL0 |= DAC_CNTL;
    P3SEL1 |= DAC_CNTL;
    //P3DIR &= ~DAC_CNTL;

    P3SEL0 &= ~P3_6;
    P3SEL1 &= ~P3_6;
    P3DIR &= ~P3_6;

    P3SEL0 &= ~P3_7;
    P3SEL1 &= ~P3_7;
    P3DIR &= ~P3_7;
}

//===========================================================================
// Function name: Init_Port4
//
// Description: Initialize all pins on port 4
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: no global variables used
//
// Author: Ibrahim Moghul
// Date: Feb 2022
// Compiler: Built with IAR Embedded Workbench Version: (7.21.1)
//===========================================================================
void Init_Port4() {
    P4OUT = 0x00;
    P4DIR = 0x00;

    P4SEL0 &= ~P4_0;
    P4SEL1 &= ~P4_0;
    P4DIR &= ~P4_0;

    P4SEL0 &= ~SW1;
    P4SEL1 &= ~SW1;
    P4OUT |= SW1;
    P4DIR &= ~SW1;
    P4REN |= SW1;
    P4IES |= SW1;
    P4IFG &= ~SW1;
    P4IE &= ~SW1;

    P4SEL0 |= UCA1TXD;
    P4SEL1 &= ~UCA1TXD;

    P4SEL0 |= UCA1RXD;
    P4SEL1 &= ~UCA1RXD;

    P4SEL0 &= ~UCB1_CS_LCD;
    P4SEL1 &= ~UCB1_CS_LCD;
    P4OUT |= UCB1_CS_LCD;
    P4DIR |= UCB1_CS_LCD;

    P4SEL0 |= UCB1CLK;
    P4SEL1 &= ~UCB1CLK;

    P4SEL0 |= UCB1SIMO;
    P4SEL1 &= ~UCB1SIMO;

    P4SEL0 |= UCB1SOMI;
    P4SEL1 &= UCB1SOMI;
}


//===========================================================================
// Function name: Init_Port5
//
// Description: Initialize all pins on port 5
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: no global variables used
//
// Author: Ibrahim Moghul
// Date: Feb 2022
// Compiler: Built with IAR Embedded Workbench Version: (7.21.1)
//===========================================================================
void Init_Port5() {
    P5OUT = 0x00;
    P5DIR = 0x00;

    P5SEL0 &= ~P5_0;
    P5SEL1 &= ~P5_0;
    P5DIR &= ~P5_0;

    P5SEL0 &= ~P5_1;
    P5SEL1 &= ~P5_1;
    P5DIR &= ~P5_1;

    P5SEL0 &= ~P5_2;
    P5SEL1 &= ~P5_2;
    P5DIR &= ~P5_2;

    P5SEL0 &= ~P5_3;
    P5SEL1 &= ~P5_3;
    P5DIR &= ~P5_3;

    P5SEL0 &= ~P5_4;
    P5SEL1 &= ~P5_4;
    P5DIR &= ~P5_4;

}

//===========================================================================
// Function name: Init_Port6
//
// Description: Initialize all pins on port 6
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: no global variables used
//
// Author: Ibrahim Moghul
// Date: Feb 2022
// Compiler: Built with IAR Embedded Workbench Version: (7.21.1)
//===========================================================================
void Init_Port6() {
    P6OUT = 0x00;
    P6DIR = 0x00;

    P6SEL0 &= ~P6_0;
    P6SEL1 &= ~P6_0;
    P6DIR &= ~P6_0;

    P6SEL0 &= ~P6_1;
    P6SEL1 &= ~P6_1;
    P6DIR &= ~P6_1;

    P6SEL0 &= ~P6_2;
    P6SEL1 &= ~P6_2;
    P6DIR &= ~P6_2;

    P6SEL0 &= ~P6_3;
    P6SEL1 &= ~P6_3;
    P6DIR &= ~P6_3;

    P6SEL0 &= ~P6_4;
    P6SEL1 &= ~P6_4;
    P6DIR &= ~P6_4;

    P6SEL0 &= ~P6_5;
    P6SEL1 &= ~P6_5;
    P6DIR &= ~P6_5;

    P6SEL0 &= ~GRN_LED;
    P6SEL1 &= ~GRN_LED;
    P6DIR |= GRN_LED;
    P6OUT &= ~GRN_LED;
}