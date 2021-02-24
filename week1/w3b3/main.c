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


// Build in led Arduino on PB7 (pin 13)
void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

volatile int tenthValue = 0;
volatile int CompareValue = 0;

ISR( TIMER2_COMP_vect ) {
	TCNT2 = 0;
	tenthValue++;
}

void setupTimer(void) {
	cli();
	OCR2 = CompareValue;
	TIMSK |= BIT(7);
	sei();
	TCCR2 = 0b00011111;
}


int main(void) {
	DDRD &= ~BIT(7);
	DDRA = 0xFF;
	DDRB = 0xFF;
	setupTimer();
	
    while (1)  {
		PORTA = TCNT2;
		PORTB = tenthValue;
		wait(10);
    }
	
	return 0;
}