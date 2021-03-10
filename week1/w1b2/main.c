/*
 * main.c
 *
 * Created: 3-2-2021 11:42:18
 * Author: Dennis Kruijt & Shinichi Hezemans
 */

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

void wait(int ms);

int main(void)
{
	DDRD =	0b11000000;
	PORTD = 0b10000000;
	
	while (1)
	{
		wait(500);
		PORTD ^= 0b11000000;
	}
}

void wait(int ms) {
	for (int i = 0; i < ms; i++) {
		_delay_ms(1);
	}
}
