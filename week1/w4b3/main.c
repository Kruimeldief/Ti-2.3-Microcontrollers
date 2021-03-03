/*
 * w4b3.c
 *
 * Created: 3/3/2021 12:46:31 PM
 * Author : Shinichi
 */ 
#define F_CPU 8e6

#include <util/delay.h>
#include <stdio.h>

#include <avr/io.h>
#include "lcd/lcd.h"


void  adcInit(void){
	ADMUX = 0b01100011;
	ADCSRA = 0b11000110;
}

int main(void)
{
	DDRB = 0xFF;
	wait(10);
	init();
	wait(10);

	lcd_clear();
	wait(10);
	
	adcInit();
	DDRF = 0;
	DDRE = 0xff;
	while (1)
	{
		PORTE = ADCH;
		wait(100);
		ADCSRA ^= 0b01000000;
		
		char numStr[12];
		sprintf(numStr, "%d", ADCH <<1);
		set_cursor(0);
		display_text(numStr);
	}
}

