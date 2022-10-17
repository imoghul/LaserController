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
#define MOTOR_ENABLE_P (0x04)     // 2 
#define MOTOR_ENABLE_N (0x08)     // 3 
#define MOTOR_DIR_P (0x10)     // 4 
#define MOTOR_DIR_N (0x20)     // 5 
#define UCA0RXD (0x40)  // 6 Back Channel UCA0RXD
#define UCA0TXD (0x80)  // 7 Back Channel UCA0TXD
// Port 2 Pins
#define P2_0 (0x01)   // 0 
#define P2_1 (0x02)   // 1 
#define P2_2 (0x04)   // 2
#define SW2 (0x08)    // 3 SW2
#define P2_4 (0x10)   // 4 
#define P2_5 (0x20)   // 5 
#define LFXOUT (0x40) // 6 XOUTR
#define LFXIN (0x80)  // 7 XINR
// Port 3 Pins
#define TEST_PROBE (0x01) // 0 TEST PROBE
#define P3_1 (0x02)       // 1 
#define OA2N (0x04)       // 2 Photodiode Circuit
#define P3_3 (0x08)       // 3
#define SMCLK_2355 (0x10) // 4
#define P3_5 (0x20)       // 5
#define MOTOR1_P_COUNT (0x40)       // 6
#define MOTOR1_N_COUNT (0x80)       // 7
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
#define MOTOR1_P_PIN (0x01)   // 0
#define MOTOR1_N_PIN (0x02)   // 1
#define MOTOR2_P_PIN (0x04)   // 2
#define MOTOR2_N_PIN (0x08)   // 3
#define P6_4 (0x10)   // 4
#define P6_5 (0x20)    // 5
#define GRN_LED (0x40) // 6

// shortcuts
#define ENABLE_P_ON {P1OUT |= MOTOR_ENABLE_P;}
#define ENABLE_P_OFF {P1OUT &= ~MOTOR_ENABLE_P;}
#define DIR_P_ON {P1OUT |= MOTOR_DIR_P;}
#define DIR_P_OFF {P1OUT &= ~MOTOR_DIR_P;}
//#define PULSE_P_ON {P1OUT |= MOTOR_PULSE_P;}
//#define PULSE_P_OFF {P2OUT &= ~MOTOR_PULSE_P;}
//#define PULSE_P_TOGGLE {P2OUT ^= MOTOR_PULSE_P;}


void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(char smclk);
void Init_Port4(void);
void Init_Port5(void);
void Init_Port6(void);