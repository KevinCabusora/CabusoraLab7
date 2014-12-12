#include <msp430.h>
#include "lab7.h"

void main(void){
	WDTCTL = WDTPW + WDTHOLD;

    while(1){
    	left();
    	middle();
    	right();
    }
}

