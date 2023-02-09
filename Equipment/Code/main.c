#include "msp430.h"
#include "functions.h"
#include "motor.h"
#include "ports.h"
#include "adc.h"
#include "timers.h"
#include "serial.h"
/**
 * main.c
 */

extern Motor motor1, motor2, motor3, motor4, motor5;

int main(void) {
    PM5CTL0 &= ~LOCKLPM5;
    Init_Ports();
    Init_Clocks();
    enable_interrupts();

    Init_Serial_UCA();
    Init_Timers();
    //Init_ADC();
    //Init_DAC();

    while(1) {
        SerialProcess();
        HandleCommands();
        sendTrains(&motor1);
        sendTrains(&motor2);
        sendTrains(&motor3);
        sendTrains(&motor4);
        sendTrains(&motor5);
    }

    return 0;
}
