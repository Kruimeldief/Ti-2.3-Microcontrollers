/*
 * main.c
 *
 * Created: 2/10/2021 11:22:39 AM
 * Author: Dennis Kruijt & Shinichi Hezemans
 */ 

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
	set_cursor(12);

	// Loop forever
	while (1) {
		display_text(".");
		wait( 1000 );
	}

	return 1;
}