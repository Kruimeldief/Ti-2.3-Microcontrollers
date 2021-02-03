/*
 * b5.c
 *
 * Created: 2/3/2021 1:51:30 PM
 *  Author: Shinichi
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

void wait(int ms);

int main5(void){
	DDRC = 0b11111111;
	char pattern[] = {0b10000000,
		0b11000000,
		0b01100000,
		0b00110000,
		0b00011000,
		0b00001100,
		0b00000110,
		0b00000011,
		0b00000001,
		0b00000011,
		0b00000110,
		0b00001100,
		0b00011000,
		0b00110000,
		0b01100000,
		0b11000000};
		int index = 0;
		while (1)
		{
			PORTC = pattern[index];
			index++;
			index %= 16;
			wait(100);
		}
}
