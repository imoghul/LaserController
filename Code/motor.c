#include "motor.h"
#include "msp430.h"
#include "timers.h"
#include "ports.h"

unsigned int pulseCount;
volatile unsigned char pulseTrainsSent;
volatile unsigned int pulsesToSend;
volatile unsigned int trainsToSend, trainsDir;
unsigned int trainsSent;
volatile char trainsFinished;

int sendTrains(){
  if(pulseTrainsSent && trainsToSend){
      trainsFinished = 0;
      sendPulseTrains(1, trainsDir);
      if(trainsSent++ >= trainsToSend){
        trainsSent = 0;
        trainsToSend = 0;
        pulseTrainsSent = 0;
        trainsFinished = 1;
      }
      return 1;
  }else if(!trainsToSend){
    trainsSent = 0;
    trainsToSend = 0;
    pulseTrainsSent = 0;
    trainsFinished = 1;
  }
  return 0;
}

void sendPulseTrains(int revs, int dir){
  pulseTrainsSent = 0;
  pulsesToSend = 200*revs;
  setMotor1(dir);
}

// dir:
// 0: stop
// 1: cw
// 2: ccw
void setMotor2(int dir){
  if(!dir){
    MOTOR2_P = 0;
    return;
  }
  
  if(dir==2){
    DIR2_P_ON;
  }
  else if (dir==1) {
    DIR2_P_OFF;
  }
  MOTOR2_P = PULSE_PERIOD>>1;
}

void setMotor1(int dir){
  if(!dir){
    MOTOR1_P = 0;
    return;
  }
  
  if(dir==2){
    DIR1_P_ON
  }
  else if (dir == 1){
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