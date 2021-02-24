#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LCD_E 	6  // RA6 UNI-6
#define LCD_RS	4  // RA4 UNI-6

void init( void );
void lcd_strobe_lcd_e(void);
void lcd_write_data( unsigned char byte );
void lcd_write_command(unsigned char byte);
void lcd_clear();
void display_text(char *str);void set_cursor( int position );

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

/******************************************************************
short:			Init LCD module in 4 bits mode.
inputs:			-
outputs:		-
notes:			According datasheet HD44780 table 12
Version :    	DMK, Initial code
*******************************************************************/
void init( void ) {
	// PORTC output mode and all low (also E and RS pin)
	DDRD = 0xFF;
	DDRA = 0xFF;
	PORTC = 0x00;
	PORTA = 0x00;

	// Step 2 (table 12): set to 4-bit operation
	PORTC = 0x20;
	lcd_strobe_lcd_e();

	// Step 3 (table 12): Set 4-bit operation
	PORTC = 0x20;
	lcd_strobe_lcd_e();
	
	// Step 3 (table 12): select 1-line display and 5x8 dot font
	PORTC = 0x80;
	lcd_strobe_lcd_e();

	// Step 4 (table 12): turn on display
	PORTC = 0x00;
	lcd_strobe_lcd_e();
	
	// Step 4 (table 12): Turn on cursor
	PORTC = 0xF0;
	lcd_strobe_lcd_e();

	// Step 5 (table 12): Set mode to increment address and cursor
	PORTC = 0x00;
	lcd_strobe_lcd_e();
	PORTC = 0x60;
	lcd_strobe_lcd_e();
	
	// Clear screen to be safe
	lcd_clear();
}

void lcd_strobe_lcd_e(void) {
	PORTA |= (1<<LCD_E);	// E high
	_delay_ms(1);
	PORTA &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);
}

/******************************************************************
short:			Writes 8 bits DATA to lcd
inputs:			byte - written to LCD
outputs:
notes:			According datasheet HD44780 table 12
Version :    	DMK, Initial code
*******************************************************************/
void lcd_write_data( unsigned char byte ) {
	// First nibble.
	PORTC = byte;
	PORTA |= (1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTA |= (1<<LCD_RS);
	lcd_strobe_lcd_e();
}

/******************************************************************
short:			Writes 8 bits COMMAND to lcd
inputs:			byte - written to LCD
outputs:
notes:			According datasheet HD44780 table 12
Version :    	DMK, Initial code
*******************************************************************/
void lcd_write_command(unsigned char byte) {
	// First nibble.
	PORTC = byte;
	PORTA &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTA &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();
}

void lcd_clear() {
	lcd_write_command (0x01); //Leeg display
	_delay_ms(2);
	lcd_write_command (0x80); //Cursor terug naar start
}

void display_text(char *str) {
	for(;*str; str++){
		lcd_write_data(*str);
	}
}

void set_cursor( int position ) {
	// TODO make robust
	lcd_write_command(0x80 | position);
}