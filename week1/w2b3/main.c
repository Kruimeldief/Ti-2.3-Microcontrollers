/*
 * main.c
 *
 * Created: 10-2-2021 13:24:52
 * Author: Dennis Kruijt & Shinichi Hezemans
 */

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

char digitLookUpTable[] = {
	0b00111111, 0b00110000, 0b01011011, 0b01001111,
	0b01100110, 0b01101101, 0b01111101,	0b00000111,
	0b01111111, 0b01101111, 0b01110111, 0b01111100,
	0b01011000, 0b01011110, 0b01111001, 0b01110001 };
char errorDigit = 0b11011000;
char state = 0;

// 7 seg
// PORTD dp G F E D C B A
//        y y y y x x x x

void setDigit(char);
void handleState(char);

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

ISR( INT0_vect ) {
	EIMSK &= 0b11111110; // turn off interrupt
	
	state &= 0b11111110;
	state |= (EICRA & 0b00000001);
	
	EICRA ^= 0b00000001; // flip rising/falling edge
	handleState(state);

	EIMSK |= 0b00000001; // turn on interrupt
}

ISR( INT1_vect ) {
	EIMSK &=0b11111101; // turn off interrupt
	
	state &= 0b11111101;
	state |= ((EICRA & 0b00000100) >> 1);
	
	EICRA ^= 0b00000100; // flip rising/falling edge
	handleState(state);

	EIMSK |= 0b00000010; // turn on interrupt
}

int main( void ) {
	DDRE = 0b11111111;					
	DDRD = 0b00000000;
	DDRA = 0xFF;

	EICRA |= 0b00001111;
	EIMSK |= 0x03;			
	sei();

	while (1) {
		// Empty
	}

	return 1;
}

void setDigit(char value){
	if (value >= 0 && value <= 15) {
		PORTE = digitLookUpTable[(int)value];
		
	} else {
		PORTE = errorDigit;
	}
}

void handleState(char state){
	static int position = 0;
	PORTA = state;
	
	if (state == 0b00000011) {
		position = 0;
		
	} else if (state == 0b00000001) {
		position++;
		
	} else if(state == 0b00000010) {
		position--;
	}
	
	setDigit(position);
}