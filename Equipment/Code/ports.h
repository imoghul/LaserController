//==============================================================================
// File Name : ports.h
//
// Description: This file contains macros and function declarations for ports.c
//
// Author: Ibrahim Moghul
// Date: Feb 2022
// Compiler: Built with IAR Embedded Workbench Version: 7.21.1
//==============================================================================

#define USE_GPIO (0)
#define USE_SMCLK (1)

// Port 1 Pins
#define RED_LED (0x01)  // 0 
#define A1_SEEED (0x02) // 1 
#define P1_2 (0x04)     // 2 
#define P1_3 (0x08)     // 3 
#define HEATER_ADC (0x10)     // 4 
#define HEATER_DAC (0x20)     // 5 
#define UCA0RXD (0x40)  // 6 Back Channel UCA0RXD
#define UCA0TXD (0x80)  // 7 Back Channel UCA0TXD
// Port 2 Pins
#define P2_0 (0x01)   // 0 
#define P2_1    (0x02)   // 1 
#define P2_2 (0x04)   // 2
#define SW2 (0x08)    // 3 SW2
#define P2_4    (0x10)   // 4 
#define P2_5 (0x20)   // 5 
#define LFXOUT (0x40) // 6 XOUTR
#define LFXIN (0x80)  // 7 XINR
// Port 3 Pins
#define TEST_PROBE (0x01) // 0 TEST PROBE
#define P3_1 (0x02)       // 1 
#define OA2N (0x04)       // 2 Photodiode Circuit
#define P3_3 (0x08)       // 3
#define P3_4 (0x10) // 4
#define DAC_CNTL (0x20)       // 5
#define P3_6 (0x40)       // 6
#define P3_7 (0x80)       // 7
// Port 4 Pins
#define P4_0 (0x01)        // 0
#define SW1 (0x02)         // 1 SW1
#define UCA1RXD (0x04)     // 2 Back Channel UCA1RXD (0x08) // 3 Back Channel UCA1TXD (0x10) // 4 Chip Select
#define UCA1TXD (0x08)     // 3 Back Channel UCA1TXD
#define UCB1_CS_LCD (0x10) // 4 Chip Select
#define UCB1CLK (0x20)     // 5 SPI mode -
#define UCB1SIMO (0x40)    // 6 UCB1SIMO
#define UCB1SOMI (0x80)    // 7 UCB1SOMI
// Port 5 Pins
#define P5_0 (0x01)
#define P5_1 (0x02)
#define P5_2 (0x04)
#define P5_3 (0x08)
#define P5_4 (0x10)
// Port 6 Pins
#define P6_0 (0x01)   // 0
#define P6_1 (0x02)   // 1
#define P6_2 (0x04)   // 2
#define P6_3 (0x08)   // 3
#define P6_4 (0x10)   // 4
#define P6_5 (0x20)    // 5
#define GRN_LED (0x40) // 6

// shortcuts

#define ENABLE1_P_ON {P2OUT |= MOTOR1_ENABLE_P;}
#define ENABLE1_P_OFF {P2OUT &= ~MOTOR1_ENABLE_P;}
#define DIR1_P_ON {P2OUT |= MOTOR1_DIR_P;}
#define DIR1_P_OFF {P2OUT &= ~MOTOR1_DIR_P;}

#define ENABLE2_P_ON {P2OUT |= MOTOR2_ENABLE_P;}
#define ENABLE2_P_OFF {P2OUT &= ~MOTOR2_ENABLE_P;}
#define DIR2_P_ON {P2OUT |= MOTOR2_DIR_P;}
#define DIR2_P_OFF {P2OUT &= ~MOTOR2_DIR_P;}

#define ENABLE3_P_ON {P5OUT |= MOTOR3_ENABLE_P;}
#define ENABLE3_P_OFF {P5OUT &= ~MOTOR3_ENABLE_P;}
#define DIR3_P_ON {P5OUT |= MOTOR3_DIR_P;}
#define DIR3_P_OFF {P5OUT &= ~MOTOR3_DIR_P;}

#define ENABLE4_P_ON {P5OUT |= MOTOR4_ENABLE_P;}
#define ENABLE4_P_OFF {P5OUT &= ~MOTOR4_ENABLE_P;}
#define DIR4_P_ON {P5OUT |= MOTOR4_DIR_P;}
#define DIR4_P_OFF {P5OUT &= ~MOTOR4_DIR_P;}

#define ENABLE5_P_ON {P4OUT |= MOTOR5_ENABLE_P;}
#define ENABLE5_P_OFF {P4OUT &= ~MOTOR5_ENABLE_P;}
#define DIR5_P_ON {P5OUT |= MOTOR5_DIR_P;}
#define DIR5_P_OFF {P5OUT &= ~MOTOR5_DIR_P;}

void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(char smclk);
void Init_Port4(void);
void Init_Port5(void);
void Init_Port6(void);