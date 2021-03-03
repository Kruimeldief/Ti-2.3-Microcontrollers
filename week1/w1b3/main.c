/*
 * main.c
 *
 * Created: 3-2-2021 11:48:45
 * Author: Dennis Kruijt & Shinichi Hezemans
 */

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

void wait(int ms);

int main(void)
{
	DDRD =	0b11111111;
	DDRC = 	0b11111110;
	unsigned char state = 0;
	while (1)
	{
		if (PINC) {
			state ^= 0b10000000;
		} else {
			state = 0;
		}
		PORTD = state;
		wait(500);
	}
}

void wait(int ms) {
	for (int i = 0; i < ms; i++) {
		_delay_ms(1);
	}
}