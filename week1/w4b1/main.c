/*
 * w4b1.c
 *
 * Created: 3/3/2021 12:09:17 PM
 * Author : Shinichi
 */ 

#include <avr/io.h>

void  adcInit(void){
	ADMUX = 0b01100001;
	ADCSRA = 0b11100110;
}

int main(void)
{
	adcInit();
	DDRF = 0;
	DDRB = 0xff;
	DDRA = 0xff;
	while (1)
	{
		PORTB = ADCL;
		PORTA = ADCH;
	}
}

