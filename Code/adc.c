#include "msp430.h"
#include "ports.h"
#include "adc.h"
#include <string.h>

volatile unsigned int DAC_setpoint;
volatile unsigned int HeaterADC;

void Init_ADC(void) {
    //------------------------------------------------------------------------------
    // V_DETECT_L
    // V_DETECT_R
    // V_THUMB
    //------------------------------------------------------------------------------
    // ADCCTL0 Register
    ADCCTL0 = 0;
    ADCCTL0 |= ADCSHT_2;
    ADCCTL0 |= ADCMSC;
    ADCCTL0 |= ADCON;
    //ADCCTL0 = ADCSHT_2 | ADCMSC | ADCON;
    // ADCCTL1 Register
    ADCCTL1 = 0;
    ADCCTL1 |= ADCSHS_0;
    ADCCTL1 |= ADCSHP;
    ADCCTL1 &= ~ADCISSH;
    ADCCTL1 |= ADCDIV_0;
    ADCCTL1 |= ADCSSEL_0;
    ADCCTL1 |= ADCCONSEQ_0;
    // ADCCTL2 Register
    ADCCTL2 = 0;
    ADCCTL2 |= ADCPDIV0;
    ADCCTL2 |= ADCRES_1;
    ADCCTL2 &= ~ADCDF;
    ADCCTL2 &= ~ADCSR;
    // ADCMCTL0 Register
    ADCMCTL0 |= ADCSREF_0;
    ADCMCTL0 |= ADCINCH_3;

    ADCIE |= ADCIE0;
    ADCCTL0 |= ADCENC;
    ADCCTL0 |= ADCSC;
}

void Init_REF(void) {
    PMMCTL0_H = PMMPW_H;
    PMMCTL2 = INTREFEN;
    PMMCTL2 |= REFVSEL_2;

    while(!(PMMCTL2 & REFGENRDY));
}

void Init_DAC(void) {
    DAC_setpoint = 1000;
    SAC3DAT = DAC_setpoint;
    SAC3DAC = DACSREF_1;
    SAC3DAC |= DACLSEL_0;
    //  SAC3DAC |= DACIE;
    SAC3DAC |= DACEN;

    SAC3OA = NMUXEN;
    SAC3OA |= PMUXEN;
    SAC3OA |= PSEL_1;
    SAC3OA |= NSEL_1;
    SAC3OA |= OAPM;

    SAC3PGA = MSEL_1;

    SAC3OA |= SACEN;
    SAC3OA |= OAEN;
}

#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void) {
    switch(__even_in_range(ADCIV, ADCIV_ADCIFG)) {
        //        case ADCIV_NONE:
        //            break;
        //
        //        case ADCIV_ADCOVIFG:
        //            break;
        //
        //        case ADCIV_ADCTOVIFG:
        //            break;
        //
        //        case ADCIV_ADCHIIFG:
        //            break;
        //
        //        case ADCIV_ADCLOIFG:
        //            break;
        //
        //        case ADCIV_ADCINIFG:
        //            break;

        case ADCIV_ADCIFG:
            ADCCTL0 &= ~ADCENC;

            HeaterADC = ADCMEM0;


            break;

        default:
            break;
    }
}