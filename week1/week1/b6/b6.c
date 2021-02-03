/*
 * b6.c
 *
 * Created: 3-2-2021 13:57:55
 *  Author: Dennis
 */

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

void wait(int ms);
void detectButton(void);

int main(void) {
	uint8_t step = 25; // in milliseconds.
	uint16_t counter = 0; // in milliseconds.
	uint16_t ms = 1000; // in millihertz.
	uint8_t isPressed = 0;
	
	DDRD = 0xFF;
	PORTD = 0x00;
	DDRC = 0x00;
	
	while (1) {
		
		// Check if button is pressed.
		if (PINC == 0x80) {
			if (!isPressed) {
				isPressed = 1;
				// Chance the frequency of the blinking effect.
				if (ms == 1000) ms = 250;
				else if (ms == 4000) ms = 1000;
				else ms = 1000;
			}
		} else {
			isPressed = 0;
		}
		
		// Wait if the counter hasn't reached the blinking frequency.
		if (counter >= (ms / 2)) {
			PORTD ^= 0x80;
			counter = 0;
			wait(step);
		} else {
			counter += step;
			wait(step);
		}
	}
}