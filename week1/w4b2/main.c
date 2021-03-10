/*
 * w4b2.c
 *
 * Created: 3/3/2021 12:18:30 PM
 * Author : Shinichi
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

void wait(int ms);

void  adcInit(void){
	ADMUX = 0b01100011;
	ADCSRA = 0b11000110;
}

int main(void)
{
	adcInit();
	DDRF = 0;
	DDRA = 0xff;
	while (1)
	{
		PORTA = ADCH;
		wait(100);
		ADCSRA ^= 0b01000000;		
	}
}

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

