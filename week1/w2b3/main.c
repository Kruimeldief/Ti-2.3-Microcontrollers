/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** lookup.c
**
** Beschrijving:	Ledpatroon op PORTD dmv table lookup (scheiding logica en data)    
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c switch.c
**					avr-gcc -g -mmcu=atmega128 -o lookup.elf lookup.o
**					avr-objcopy -O ihex lookup.elf lookup.hex 
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

char digitLookUpTable[] = {0b00111111, 0b00110000, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 
	0b01111101,	0b00000111, 0b01111111, 0b01101111, 0b01110111, 0b01111100, 0b01011000,0b01011110, 
	0b01111001, 0b01110001};
	char errorDigit = 0b11011000;

char state = 0;

// 7 seg
// PORTD dp G F E D C B A
//        y y y y x x x x

void setDigit(char);

void handleState(char);

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

ISR( INT0_vect ) {
	EIMSK &= 0b11111110;//turn off interupt
	
	state &= 0b11111110;
	state |= (EICRA & 0b00000001);
	
	EICRA ^= 0b00000001;//flip rizing faling
			handleState(state);

	EIMSK |= 0b00000001;//turn on interupt
}

ISR( INT1_vect ) {
	EIMSK &=0b11111101;//turn off interupt
	
	state &= 0b11111101;
	state |= ((EICRA & 0b00000100) >> 1);
	
	EICRA ^= 0b00000100;//flip rizing faling
			handleState(state);

	EIMSK |= 0b00000010;//turn on interupt
}

int main( void ) {
	// Init I/O
DDRE = 0b11111111;					// PORTD all output
DDRD = 0b00000000;
DDRA = 0xFF;
	// Init Interrupt hardware
	EICRA |= 0b00001111;
	EIMSK |= 0x03;			// Enable INT1 & INT0
	
	// Enable global interrupt system
	//SREG = 0x80;			// Of direct via SREG of via wrapper
	sei();

	while (1) {
	}

	return 1;
}

void setDigit(char value){
	if (value >= 0 && value <= 15)
	{
		PORTE = digitLookUpTable[(int)value];
	}else{
		PORTE = errorDigit;
	}
}

void handleState(char state){
	static int position = 0;
	PORTA = state;
	if (state == 0b00000011)
	{
		position = 0;
	}else if (state == 0b00000001)
	{
		position++;
		}else if(state == 0b00000010){
		position--;
	}
	setDigit(position);

}