#include "msp430.h"
#include "functions.h"
#include "ports.h"
#include "adc.h"
#include "timers.h"
#include "serial.h"
/**
 * main.c
 */


int main(void) {
    PM5CTL0 &= ~LOCKLPM5;
    Init_Ports();
    Init_Clocks();
    enable_interrupts();

    Init_Serial_UCA();
    Init_Timers();
    Init_ADC();
    Init_DAC();

    while(1) {
        SerialProcess();
        HandleCommands();
    }

    return 0;
}
