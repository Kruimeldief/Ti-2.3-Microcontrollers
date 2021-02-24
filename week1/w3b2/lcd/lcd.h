/*
 * lcd.h
 *
 * Created: 10-2-2021 11:23:14
 *  Author: Dennis
 */ 


#ifndef LCD_H_
#define LCD_H_

#define LCD_E 	6  // RA6 UNI-6
#define LCD_RS	4  // RA4 UNI-6

void wait(int ms);
void init( void );
void lcd_strobe_lcd_e(void);
void lcd_write_data( unsigned char byte );
void lcd_write_command(unsigned char byte);
void lcd_clear();
void display_text(char *str);void set_cursor( int position );
#endif /* LCD_H_ */ 