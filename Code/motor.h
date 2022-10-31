typedef struct {
  volatile unsigned short * PWM;
  unsigned int pulseCount;
  volatile unsigned char pulseTrainsSent;
  volatile unsigned int pulsesToSend;
  unsigned int trainsToSend;
  unsigned int trainsDir;
  unsigned int trainsSent;
  char trainsFinished;
  void (*setMotor)(int);
} Motor;


int sendTrains(volatile Motor*);
void sendPulseTrains(volatile Motor* m);
void setMotor2(int);
void setMotor1(int);


