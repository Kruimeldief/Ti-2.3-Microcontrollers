/*
* main.c
*
* Created: 2/24/2021 10:34:51 AM
* Author: Dennis Kruijt & Shinichi Hezemans & Merijn Couweleers
*/

#define F_CPU 16e6
#define BIT1(x) (1 << (x))
#define BIT0(x) (0 << (x))

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int msCounter = 0;
int io = 1;

void timer2Init( void ) {
	OCR2 = 519;
	TCCR2 = 1 << WGM21; // CTC mode
	
	/* Enable interrupts */
	TIMSK = TIMSK | 1<<TOIE1 | 1<<OCIE2;
	TCCR2 |= 1<<CS22 | 0<<CS21 | 1<<CS20;
	TCNT2 = 0;
	sei();
}

ISR( TIMER2_COMP_vect )
{
	msCounter++;
	
	if (io && msCounter >= 25) {
		PORTD = BIT1(7);
		msCounter = 0;
		io = 0;
		
	} else if (!io && msCounter >= 15) {
		PORTD = BIT0(7);
		msCounter = 0;
		io = 1;
	}
}

int main (void)
{
	DDRD = 0xFF;
	timer2Init();
	
	while(1){
		// Empty
	}
}