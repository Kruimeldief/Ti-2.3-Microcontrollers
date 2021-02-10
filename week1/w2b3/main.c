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

char digitLookUpTable[] = {0b00111111, 0b00110000, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 
	0b01111101,	0b00000111, 0b01111111, 0b01101111, 0b01110111, 0b01111100, 0b01011000,0b01011110, 
	0b01111001, 0b01110001};
	char errorDigit = 0b11011000;

// 7 seg
// PORTD dp G F E D C B A
//        y y y y x x x x

void setDigit(char);

void handleInput(char);
/******************************************************************
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}


/******************************************************************
short:			main() loop, entry point of executable
inputs:
outputs:
notes:
Version :    	DMK, Initial code
*******************************************************************/
int main( void ) {
	DDRD = 0b11111111;					// PORTD all output 
	DDRC = 0b00000000;
	
	while (1==1) {
		while( 1 ) {
			// Write data to PORTD	
			handleInput(PINC);
			wait(100);
			
		}
	}

	return 1;
}

void setDigit(char value){
	if (value >= 0 && value <= 15)
	{
		PORTD = digitLookUpTable[(int)value];
	}else{
		PORTD = errorDigit;
	}
}

void handleInput(char port){
	static int position = 0;
	if (port & 0b00000001 && port & 0b00000010)
	{
		position = 0;
	}else if (port & 0b00000001)
	{
		position++;
	}else if(port & 0b00000010){
		position--;
	}
	setDigit(position);
}