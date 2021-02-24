/*
 * Lesvoorbeeld_atmega2560.c
 *
 * Created: 10/02/2020 18:26:21
 * Author : Etienne
 */ 

#define F_CPU 16e6
#define BIT(x) (1 << (x))

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../w2b5/lcd/lcd.h"


int msHigh = 25;
int msLow = 15;
volatile int msCount = 0;
volatile int ms = 15;

void timer2Init( void ) {
	OCR2 = 250;
	TIMSK |= BIT(7);
	sei();
	TCCR2 = 0b00001011;
}

ISR( TIMER2_COMP_vect ) {
	msCount++;
	if ( msCount == ms) {
		PORTD ^= BIT(7);
		msCount = 0;
		if (ms == msHigh) {
			ms = msLow;
		} else {
			ms = msHigh;
		}
	}
}


int main(void) {
	DDRD = 0xFF;
	timer2Init();
	
    while (1)  {
		_delay_ms(10);
    }
	
	return 0;
}