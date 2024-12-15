#ifndef __LCD_H__
#define __LCD_H__

#include <stdbool.h>
#include <stdint.h>
#include "driverlib/gpio.h"
#include "globals.h"
#include "inc/hw_memmap.h"
#include "sys_tick.h"

void lcd_command(uint8_t command);
void lcd_data(uint8_t data);
void lcd_define_custom_chars(void);
void lcd_setup(void);
void lcd_new_line(void);
void lcd_print_char(char c);
void lcd_print_special_char(uint8_t c);
void lcd_print_string(char* string);
void lcd_write(uint8_t data, uint8_t command, uint32_t clock_duration_us);

#endif // __LCD_H__
