#include "motor.h"
#include "msp430.h"
#include "timers.h"
#include "ports.h"

unsigned int pulseCount;
volatile unsigned char pulseTrainSent;
volatile unsigned int pulsesToSend;

void sendPulseTrain(int pulses){
  pulseTrainSent = 0;
  pulsesToSend = pulses;
  MOTOR1_P = PULSE_PERIOD>>1;
}

void setMotor2(int dir){
  if(dir){
    MOTOR2_N = 0;
    MOTOR2_P = PULSE_PERIOD>>1;
  }
  else {
    MOTOR2_P= 0 ;
    MOTOR2_N = PULSE_PERIOD>>1;
  }
}



#pragma vector=PORT3_VECTOR
__interrupt void motor1Count_interrupt(void) {
    if(((P3IFG & MOTOR1_P_COUNT) && MOTOR1_P) || ((P3IFG & MOTOR1_N_COUNT)&&MOTOR1_N)) {
            if(++pulseCount>=pulsesToSend){
              MOTOR1_P = 0;
              MOTOR1_N = 0;
              pulseTrainSent = 1;
              pulseCount = 0;
              pulsesToSend = 0;
            }
    }
    P3IFG &= ~MOTOR1_P_COUNT;
    P3IFG &= ~MOTOR1_N_COUNT;
}