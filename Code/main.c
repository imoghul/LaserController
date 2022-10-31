#include "msp430.h"
#include "functions.h"
#include "motor.h"
#include "ports.h"
#include "timers.h"
#include "serial.h"
/**
 * main.c
 */

extern volatile unsigned char pulseTrainSent;

int main(void)
{
    PM5CTL0 &= ~LOCKLPM5;
    Init_Ports();
    Init_Clocks();
    enable_interrupts();
    
    Init_Serial_UCA();
    Init_Timers();
    
    
    while(1){
      SerialProcess();
      HandleCommands();
      sendTrains();
    }
    return 0;
}
