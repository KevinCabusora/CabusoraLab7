#include <msp430.h>
#include "lab7.h"

void initMSP430();

/*
 * main.c
 */
int main(void) {
    IFG1=0;                                                     // clear interrupt flag1
       WDTCTL = WDTPW + WDTHOLD;                                   // disable WDT

       BCSCTL1 = CALBC1_8MHZ;                                      // 8MHz clock
       DCOCTL = CALDCO_8MHZ;

       P1DIR = BIT0|BIT6;                                               // Set the red LED as output

       P1OUT = BIT0|BIT6;
       P1OUT &= ~(BIT0|BIT6);

    while(1){
    	left();
    	middle();
    	right();
    }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void){
	__bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}
