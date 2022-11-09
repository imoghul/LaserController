#include "motor.h"
#include "msp430.h"
#include "timers.h"
#include "ports.h"

Motor motor1 = {
  .PWM = &MOTOR1_P,
  .pulseCount = 0,
  .pulseTrainsSent = 0,
  .pulsesToSend=0,
  .trainsToSend = 0,
  .trainsDir = 0,
  .trainsSent = 0,
  .trainsFinished = 0,
  .setMotor = setMotor1
};
Motor motor2 = {
  .PWM = &MOTOR2_P,
  .pulseCount = 0,
  .pulseTrainsSent = 0,
  .pulsesToSend=0,
  .trainsToSend = 0,
  .trainsDir = 0,
  .trainsSent = 0,
  .trainsFinished = 0,
  .setMotor = setMotor2
};

int sendTrains(Motor* motor){
  if(motor->pulseTrainsSent && motor->trainsToSend){
      motor->trainsFinished = 0;
      sendPulseTrains(motor);
      if(motor->trainsSent++ >= motor->trainsToSend){
        motor->trainsSent = 0;
        motor->trainsToSend = 0;
        motor->pulseTrainsSent = 0;
        motor->trainsFinished = 1;
      }
      return 1;
  }else if(!motor->trainsToSend){
    motor->trainsSent = 0;
    motor->trainsToSend = 0;
    motor->pulseTrainsSent = 0;
    motor->trainsFinished = 1;
  }
  return 0;
}

void sendPulseTrains(Motor* m){
  m->pulseTrainsSent = 0;
  m->pulsesToSend = 200;
  m->setMotor(m->trainsDir);
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
    if(((P3IFG & MOTOR1_P_COUNT) && *(motor1.PWM))) {
            if(++motor1.pulseCount>=motor1.pulsesToSend){
              *(motor1.PWM) = 0;
              motor1.pulseTrainsSent=1;
              motor1.pulseCount = 0;
              motor1.pulsesToSend = 0;
            }
    }
    if(((P3IFG & MOTOR2_P_COUNT) && *(motor2.PWM))) {
            if(++motor2.pulseCount>=motor2.pulsesToSend){
              *(motor2.PWM) = 0;
              motor2.pulseTrainsSent=1;
              motor2.pulseCount = 0;
              motor2.pulsesToSend = 0;
            }
    }
    P3IFG &= ~MOTOR1_P_COUNT;
    P3IFG &= ~MOTOR2_P_COUNT;
}