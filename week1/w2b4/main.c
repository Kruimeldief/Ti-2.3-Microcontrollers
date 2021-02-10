/*
 * w2b4.c
 *
 * Created: 2/10/2021 11:22:39 AM
 * Author : Shinichi
 */ 
#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

char lookUpTable[] = {0b0001100, 0b01000100, 0b01100000, 0b00100001, 0b00000011, 0b01000010,
	0b01010000, 0b00011000};
	
void wait(int);

int main(void)
{
    DDRD = 0xff;
	int index = 0;
    while (1) 
    {
		PORTD = lookUpTable[(int) index];
		wait(500);
		index++;
		index %= sizeof lookUpTable;
    }
	
}

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

