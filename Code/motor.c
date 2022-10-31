#include "motor.h"
#include "msp430.h"
#include "timers.h"
#include "ports.h"

unsigned int pulseCount;
volatile unsigned char pulseTrainsSent;
volatile unsigned int pulsesToSend;
volatile unsigned int trainsToSend, trainsDir;
volatile unsigned int trainsSent;

int sendTrains(){
  if(pulseTrainsSent && trainsToSend){
      sendPulseTrains(1, 1);
      if(trainsSent++ >= trainsToSend){
        trainsSent = 0;
        trainsToSend = 0;
        pulseTrainsSent = 0;
      }
      return 1;
  }
  return 0;
}

void sendPulseTrains(int revs, int dir){
  pulseTrainsSent = 0;
  pulsesToSend = 200*revs;
  setMotor1(dir);
}

void setMotor2(int dir){
  if(dir){
    DIR2_P_ON;
  }
  else {
    DIR2_P_OFF;
  }
  MOTOR2_P = PULSE_PERIOD>>1;
}

void setMotor1(int dir){
  if(dir){
    DIR1_P_ON
  }
  else {
    DIR1_P_OFF
  }
  MOTOR1_P = PULSE_PERIOD>>1;
}



#pragma vector=PORT3_VECTOR
__interrupt void motor1Count_interrupt(void) {
    if(((P3IFG & MOTOR1_P_COUNT) && MOTOR1_P)) {
            if(++pulseCount>=pulsesToSend){
              MOTOR1_P = 0;
              pulseTrainsSent=1;
              pulseCount = 0;
              pulsesToSend = 0;
            }
    }
    P3IFG &= ~MOTOR1_P_COUNT;
}