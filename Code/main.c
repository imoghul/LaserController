#include "msp430.h"
#include "functions.h"

/**
 * main.c
 */
int main(void)
{
    PM5CTL0 &= ~LOCKLPM5;
    Init_Ports();
    Init_Clocks();
    enable_interrupts();
    return 0;
}
