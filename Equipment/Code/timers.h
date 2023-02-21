#define TB0CCR0_INTERVAL                (50000)          // 4 ms
#define TB0CCR1_INTERVAL                (50000)         // 100 ms
#define TB0CCR2_INTERVAL                (50000)         // 100 ms

#define TB1CCR0_INTERVAL                (50000)         // 200 ms
#define TB1CCR1_INTERVAL                (1)
#define TB1CCR2_INTERVAL                (25000)         // 100 ms


#define PULSE_PERIOD                    (4000)//(4000)

void Init_Timers(void);
void Init_Timer_B0(void);
void Init_Timer_B1(void);
void Init_Timer_B3(void);