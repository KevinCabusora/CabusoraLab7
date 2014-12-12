/*
 * lab7.c
 *
 *  Created on: Dec 5, 2014
 *      Author: C16Kevin.Cabusora
 */
#include "lab7.h"

#include <msp430g2553.h>

void left()
{
	ADC10CTL0 = ADC10SHT_3 + ADC10ON + ADC10IE; //ADC10ON,interrupt enabled
	ADC10CTL1 = INCH_3;				// input A3
	ADC10AE0 |= BIT3;				
	ADC10CTL1 |= ADC10SSEL1|ADC10SSEL0;
	P1DIR |= BIT0;

		ADC10CTL0 |= ENC + ADC10SC;
		__bis_SR_register(CPUOFF + GIE);
		if (ADC10MEM < 0x1FF)
			P1OUT &= ~BIT0;
		else
			P1OUT |= BIT0;
}

void middle()
{
	ADC10CTL0 = ADC10SHT_3 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
  	ADC10CTL1 = INCH_4;                       // input A5
	ADC10AE0 |= BIT4;                         // PA.1 ADC option select
  	ADC10CTL1 |= ADC10SSEL1|ADC10SSEL0;                // Select SMCLK
  	P1DIR |= BIT0|BIT6;                            // Set P1.0, P1.6 to output direction

		ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
		__bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
		if (ADC10MEM < 0x1FF)
      			P1OUT &= ~(BIT0|BIT6);                       // Clear P1.0, P1.6 LED off
     		else
      			P1OUT |= BIT0|BIT6;                        // Set P1.0 LED on
}


void right()
{
  	ADC10CTL0 = ADC10SHT_3 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
  	ADC10CTL1 = INCH_5;                       // input A5
	ADC10AE0 |= BIT5;                         // PA.1 ADC option select
  	ADC10CTL1 |= ADC10SSEL1|ADC10SSEL0;                // Select SMCLK
  	P1DIR |= BIT6;                            // Set P1.0 to output direction

		ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    		__bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
    		if (ADC10MEM < 0x1FF)
      			P1OUT &= ~BIT6;                       // Clear P1.6 LED off
     		else
      			P1OUT |= BIT6;                        // Set P1.6 LED on
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void) {
	__bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}
