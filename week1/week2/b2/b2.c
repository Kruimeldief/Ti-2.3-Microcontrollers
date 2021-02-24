#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t stepperLight = 0;

ISR( INT0_vect ) {
    stepperLight++;
	PORTA = 1 << (stepperLight % 8);
}

ISR( INT1_vect ) {
    stepperLight--;
	PORTA = 1 << (stepperLight % 8);
}

int derp2( void ) {
	// Init I/O
	DDRA = 0b11111111;		// PORTA(0:7) output

	// Init Interrupt hardware
	EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x03;			// Enable INT1 & INT0
	
	// Enable global interrupt system
	//SREG = 0x80;			// Of direct via SREG of via wrapper
	sei();				

	while (1) {							
	}

	return 1;
}