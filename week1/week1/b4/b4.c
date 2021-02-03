/*
 * b4.c
 *
 * Created: 3-2-2021 12:58:54
 *  Author: Dennis
 */

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	uint8_t i = 0;
	
	DDRD = 0xFF;
	PORTD = 0x01;
	
	while (1) {
		if (i >= 7) {
			PORTD = 1 << i;
		} else {
			PORTD = 0x01;
		}
	}
}
