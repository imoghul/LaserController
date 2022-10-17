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
    
    
//    sendPulseTrain();
//    while(!pulseTrainSent);
//    pulseTrainSent = 1;
    
    while(1){
      if(MOTOR1_P>0 && MOTOR1_N>0)
        MOTOR1_P=MOTOR1_N=0;
      if(MOTOR2_P>0 && MOTOR2_N>0)
        MOTOR2_P=MOTOR2_N=0;
      SerialProcess();
    }
    return 0;
}
