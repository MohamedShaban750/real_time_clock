/*
 * GccApplication1.c
 *
 * Created: 27/09/2022 12:31:09 
 * Author : M7med
 */ 
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "keypad.h"
#include "7seg.h"
#include "timer2.h"
#include "std_macros.h"

volatile unsigned char seconds_counter=0;
unsigned char minutes_counter=0, hours_counter=0;
unsigned char value, first_digit, second_digit;

int main(void)
{
	keypad_init();
	lcd_init();
	seven_seg_init('A');
	SET_BIT(DDRC, 0);
	SET_BIT(DDRC, 1);
	SET_BIT(DDRC, 2);
	SET_BIT(DDRC, 3);
	SET_BIT(DDRC, 4);
	SET_BIT(DDRC, 5);
	lcd_send_string("press ON/C to");
	lcd_move_cursor(2,1);
	lcd_send_string("set clock");
	timer2_overflow_init_intr();
	
	while (1)
	{
		value=keypad_check_press();
		if (value!=NOTPRESSED)
		{
			if (value=='A')
			{
				_delay_ms(250);
				lcd_send_cmd(CLR_SCREEN);
				lcd_send_string("hours=--");
				lcd_move_cursor(1,7);
				_delay_ms(100);
				do 
				{
					first_digit=keypad_check_press();
				} while (first_digit==NOTPRESSED);
				lcd_send_char(first_digit);
				_delay_ms(300);
				do
				{
					second_digit=keypad_check_press();
				} while (second_digit==NOTPRESSED);
				lcd_send_char(second_digit);
				_delay_ms(300);
				hours_counter=(second_digit-48)+10*(first_digit-48);
			
				lcd_send_cmd(CLR_SCREEN);
				lcd_send_string("minutes=--");
				lcd_move_cursor(1,9);
				_delay_ms(500);
				do
				{
					first_digit=keypad_check_press();
				} while (first_digit==NOTPRESSED);
				lcd_send_char(first_digit);
				_delay_ms(300);
				do
				{
					second_digit=keypad_check_press();
				} while (second_digit==NOTPRESSED);
				lcd_send_char(second_digit);
				_delay_ms(300);
				minutes_counter=(second_digit-48)+10*(first_digit-48);
			
				lcd_send_cmd(CLR_SCREEN);
				lcd_send_string("seconds=--");
			
				lcd_move_cursor(1,9);
				_delay_ms(500);
				do
				{
					first_digit=keypad_check_press();
				} while (first_digit==NOTPRESSED);
				lcd_send_char(first_digit);
				_delay_ms(300);
				do
				{
					second_digit=keypad_check_press();
				} while (second_digit==NOTPRESSED);
				lcd_send_char(second_digit);
				_delay_ms(300);
				seconds_counter=(second_digit-48)+10*(first_digit-48);
			
				lcd_send_cmd(CLR_SCREEN);
				lcd_send_string("press ON/C to");
				lcd_move_cursor(2, 1);
				lcd_send_string("set clock");
			}
			else
			{
				lcd_send_cmd(CLR_SCREEN);
				lcd_send_string("wrong choice");
				_delay_ms(1000);
				lcd_send_cmd(CLR_SCREEN);
				lcd_send_string("press ON/C to");
				lcd_move_cursor(2,1);
				lcd_send_string("set clock");
			}
		}	
		
		CLR_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		SET_BIT(PORTC,3);
		SET_BIT(PORTC,4);
		SET_BIT(PORTC,5);
		cathode_7seg_write('A',seconds_counter%10);
		_delay_ms(5);
		
		SET_BIT(PORTC,0);
		CLR_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		SET_BIT(PORTC,3);
		SET_BIT(PORTC,4);
		SET_BIT(PORTC,5);
		cathode_7seg_write('A',seconds_counter/10);
		_delay_ms(5);
		
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		CLR_BIT(PORTC,2);
		SET_BIT(PORTC,3);
		SET_BIT(PORTC,4);
		SET_BIT(PORTC,5);
		cathode_7seg_write('A',minutes_counter%10);
		_delay_ms(5);
		
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		CLR_BIT(PORTC,3);
		SET_BIT(PORTC,4);
		SET_BIT(PORTC,5);
		cathode_7seg_write('A',minutes_counter/10);
		_delay_ms(5);
		
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		SET_BIT(PORTC,3);
		CLR_BIT(PORTC,4);
		SET_BIT(PORTC,5);
		cathode_7seg_write('A',hours_counter%10);
		_delay_ms(5);
		
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		SET_BIT(PORTC,3);
		SET_BIT(PORTC,4);
		CLR_BIT(PORTC,5);
		cathode_7seg_write('A',hours_counter/10);
		_delay_ms(5);
		
		if (seconds_counter>=60)
		{
			seconds_counter=0;
			minutes_counter++;
		}
		if (minutes_counter>=60)
		{
			minutes_counter=0;
			hours_counter++;
		}
		if (hours_counter>=24)
		{
			hours_counter=0;
		}
		
	}
}

ISR(TIMER2_OVF_vect)
{
	seconds_counter++;
}