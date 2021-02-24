/*
* w3b2.c
*
* Created: 2/24/2021 9:15:21 AM
* Author : Shinichi
*/

#define F_CPU 8e6

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd/lcd.h"


void setupCounter(void) {
	TCCR2 |= 0b00000111;
	DDRD &= 0b11111110;
	sei();
}

int main(void) {
	DDRB = 0xFF;
	setupCounter();
	wait(10);
	init();
	wait(10);

	lcd_clear();
	wait(10);
	int lastValue = 0;

	while (1)  {
		wait(50);
		
		if (lastValue != TCNT2)
		{
			if (TCNT2 < lastValue)
			{
				lcd_clear();
			}
			char numStr[12];
			sprintf(numStr, "%d", TCNT2);
			set_cursor(0);
			display_text(numStr);
			lastValue = TCNT2;
		}		
	}
	return 0;
}


