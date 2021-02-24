/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ioisr.c
**
** Beschrijving:	BigAVR LCD module
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c lcd.c
**					avr-gcc -g -mmcu=atmega128 -o lcd.elf lcd.o
**					avr-objcopy -O ihex lcd.elf lcd.hex
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd/lcd.h"

#define LCD_E 	6  // RA6 UNI-6
#define LCD_RS	4  // RA4 UNI-6

int main( void ) {
	// Init I/O
	DDRC = 0xFF;			// PORTD(7) output, PORTD(6:0) input
	PORTC = 0xFF;

	// Init LCD
	init();
	
	wait(10);
	
	lcd_clear();
	
	wait(10);

	// Write sample string
	display_text("Hello world!");

	// Loop forever
	while (1) {
		display_text(".");
		wait( 1000 );
	}

	return 1;
}