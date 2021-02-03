/*
 * b4.c
 *
 * Created: 3-2-2021 12:58:54
 *  Author: Dennis
 */

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

void wait(int ms);

int main(void) {
	uint8_t i = 0;
	
	DDRC = 0xFF;
	PORTC = 0x01;
	
	while (1) {
		if (i < 8) {
			PORTC = 1 << i;
			i++;
		} else {
			PORTC = 0x01;
			i = 0;
		}
		
		wait(50);
	}
}
