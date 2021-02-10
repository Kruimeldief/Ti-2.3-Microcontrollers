/*
 * lcd.h
 *
 * Created: 10-2-2021 11:23:14
 *  Author: Dennis
 */ 


#ifndef LCD_H_
#define LCD_H_

void init();
void display_text(char *str);
void set_cursor(int position);
#endif /* LCD_H_ */