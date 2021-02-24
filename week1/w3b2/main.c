/*
* w3b2.c
*
* Created: 2/24/2021 9:15:21 AM
* Author : Shinichi
*/

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//#include "lcd.h"


// Build in led Arduino on PB7 (pin 13)
void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void setupCounter(void) {
	TCCR2 |= 0b00000111;
	DDRD &= 0b11111110;
	sei();
}


int main(void) {
	DDRB = 0xFF;
	setupCounter();
	while (1)  {
		wait(50);
		PORTB = TCNT2;
	}
	return 0;
}


