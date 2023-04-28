#include "motor.h"
#include "msp430.h"
#include "timers.h"
#include "ports.h"

Motor motor1 = {
    .PWM = &MOTOR1_P,
    .pulseCount = 0,
    .pulseTrainsSent = 0,
    .pulsesToSend = 0,
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
    .pulsesToSend = 0,
    .trainsToSend = 0,
    .trainsDir = 0,
    .trainsSent = 0,
    .trainsFinished = 0,
    .setMotor = setMotor2
};
Motor motor3 = {
    .PWM = &MOTOR3_P,
    .pulseCount = 0,
    .pulseTrainsSent = 0,
    .pulsesToSend = 0,
    .trainsToSend = 0,
    .trainsDir = 0,
    .trainsSent = 0,
    .trainsFinished = 0,
    .setMotor = setMotor3
};
Motor motor4 = {
    .PWM = &MOTOR4_P,
    .pulseCount = 0,
    .pulseTrainsSent = 0,
    .pulsesToSend = 0,
    .trainsToSend = 0,
    .trainsDir = 0,
    .trainsSent = 0,
    .trainsFinished = 0,
    .setMotor = setMotor4
};

Motor motor5 = {
    .PWM = &MOTOR5_P,
    .pulseCount = 0,
    .pulseTrainsSent = 0,
    .pulsesToSend = 0,
    .trainsToSend = 0,
    .trainsDir = 0,
    .trainsSent = 0,
    .trainsFinished = 0,
    .setMotor = setMotor5
};



int sendTrains(Motor* motor) {
    if(motor->pulseTrainsSent && motor->trainsToSend) { 
        motor->trainsFinished = 0;
        sendPulseTrains(motor);

        if(++motor->trainsSent >= motor->trainsToSend) {
            motor->trainsSent = 0;
            motor->trainsToSend = 0;
            motor->pulseTrainsSent = 0;
            motor->trainsFinished = 1;
        }

        return 1;
    } else if(!motor->trainsToSend) {
        motor->trainsSent = 0;
        motor->trainsToSend = 0;
        motor->pulseTrainsSent = 0;
        motor->trainsFinished = 1;
    }

    return 0;
}

void sendPulseTrains(Motor* m) {
    m->pulseTrainsSent = 0;
    m->pulsesToSend = 200;
    m->setMotor(m->trainsDir);
}

// dir:
// 0: stop
// 1: cw
// 2: ccw
void setMotor2(int dir) {
    if(!dir) {
        MOTOR2_P = 0;
        return;
    }

    if(dir == 2) {
        DIR2_P_ON;
    } else if (dir == 1) {
        DIR2_P_OFF;
    }

    MOTOR2_P = PULSE_PERIOD >> 1;
}

void setMotor3(int dir) {
    if(!dir) {
        MOTOR3_P = 0;
        return;
    }

    if(dir == 2) {
        DIR3_P_ON;
    } else if (dir == 1) {
        DIR3_P_OFF;
    }

    MOTOR3_P = PULSE_PERIOD >> 1;
}

void setMotor5(int dir) {
    if(!dir) {
        MOTOR5_P = 0;
        return;
    }

    if(dir == 2) {
        DIR5_P_ON;
    } else if (dir == 1) {
        DIR5_P_OFF;
    }

    MOTOR5_P = PULSE_PERIOD >> 1;
}

void setMotor4(int dir) {
    if(!dir) {
        MOTOR4_P = 0;
        return;
    }

    if(dir == 2) {
        DIR4_P_ON;
    } else if (dir == 1) {
        DIR4_P_OFF;
    }

    MOTOR4_P = PULSE_PERIOD >> 1;
}

void setMotor1(int dir) {
    if(!dir) {
        MOTOR1_P = 0;
        return;
    }

    if(dir == 2) {
        DIR1_P_ON
    } else if (dir == 1) {
        DIR1_P_OFF
    }

    MOTOR1_P = PULSE_PERIOD >> 1;
}



#pragma vector=PORT3_VECTOR
__interrupt void motor1Count_interrupt(void) {
    if(((P3IFG & MOTOR1_P_COUNT) && *(motor1.PWM))) {
        if(++motor1.pulseCount >= motor1.pulsesToSend) {
            *(motor1.PWM) = 0;
            motor1.pulseTrainsSent = 1;
            motor1.pulseCount = 0;
            motor1.pulsesToSend = 0;
        }
    }

    if(((P3IFG & MOTOR2_P_COUNT) && *(motor2.PWM))) {
        if(++motor2.pulseCount >= motor2.pulsesToSend) {
            *(motor2.PWM) = 0;
            motor2.pulseTrainsSent = 1;
            motor2.pulseCount = 0;
            motor2.pulsesToSend = 0;
        }
    }

    if(((P3IFG & MOTOR3_P_COUNT) && *(motor3.PWM))) {
        if(++motor3.pulseCount >= motor3.pulsesToSend) {
            *(motor3.PWM) = 0;
            motor3.pulseTrainsSent = 1;
            motor3.pulseCount = 0;
            motor3.pulsesToSend = 0;
        }
    }

    if(((P3IFG & MOTOR4_P_COUNT) && *(motor4.PWM))) {
        if(++motor4.pulseCount >= motor4.pulsesToSend) {
            *(motor4.PWM) = 0;
            motor4.pulseTrainsSent = 1;
            motor4.pulseCount = 0;
            motor4.pulsesToSend = 0;
        }
    }

    if(((P3IFG & MOTOR5_P_COUNT) && *(motor5.PWM))) {
        if(++motor5.pulseCount >= motor5.pulsesToSend) {
            *(motor5.PWM) = 0;
            motor5.pulseTrainsSent = 1;
            motor5.pulseCount = 0;
            motor5.pulsesToSend = 0;
        }
    }

    P3IFG &= ~MOTOR1_P_COUNT;
    P3IFG &= ~MOTOR2_P_COUNT;
    P3IFG &= ~MOTOR3_P_COUNT;
    P3IFG &= ~MOTOR4_P_COUNT;
    P3IFG &= ~MOTOR5_P_COUNT;
}