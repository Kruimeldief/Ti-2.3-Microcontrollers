/*
 * b7a.c
 *
 * Created: 2/3/2021 2:18:24 PM
 *  Author: Shinichi
 */ 
#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void wait(int ms);

void start(char PinD,void (*fp)(void) );
void s1(char PinD, void (*fp)(void) );
void s2(char PinD, void (*fp)(void) );
void s3(char PinD, void (*fp)(void) );
void end(char PinD,  void (*fp)(void) );

int main(void){
	printf("hello");
	DDRD = 0;
	DDRC = 0b11111111;
	void (*fun_ptr)(char ,void (*)(void) ) = &start;

while(1){
	PORTC ^= 0b00000100;
			fun_ptr(PIND,&fun_ptr);
			printf("%d", &fun_ptr);
}
}

void start(char PinD, void (*fp)(void) ){
	PORTC = 0b10000000;
	if (PinD & 0b01000000)
	{
		fp = &s1;
	}
}

void s1(char PinD, void (*fp)(void) ){
		PORTC = 0b01000000;

	if (PinD & 0b10000000)
	{
		fp = &start;
	}else if(PinD & 0b00100000){
		
	fp = &s2;
}
}

void s2(char PinD, void (*fp)(void) ){
		PORTC = 0b00100000;

if (PinD & 0b10000000)
{
	fp = &start;
}else if (PinD & 0b01000000)
{
	fp = &s1;
}else if (PinD & 0b00100000)
{
	fp = &s3;
}
}

void s3(char PinD, void (*fp)(void) ){
		PORTC = 0b00010000;

if (PinD & 0b10000000)
{
	fp = &start;
}else if (PinD & 0b01000000)
{
	fp = &end;
}else if (PinD & 0b00100000)
{
	fp = &end;
}
}

void end(char PinD, void (*fp)(void) ){
		PORTC = 0b00001000;

if (PinD & 0b10000000)
{
	fp = &start;
}
}
