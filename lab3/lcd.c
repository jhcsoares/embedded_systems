#include "lcd.h"

// Pin map:
// RS -> PM0
// R/W -> PM1
// E -> PM2
// Dn -> PKn

// Main commands:
// 0x0 -> Disable (clock falling edge)
// 0x4 -> Enable (mainly used to instructions/commands)
// 0x5 -> Enable | RS (mainly used to write a string/char)


// M BUS (command/instruction)
void lcd_command(uint8_t command)
{
	GPIOPinWrite(GPIO_PORTM_BASE, PORT_M_BUS_DATA_OUTPUT, command);
}


// K BUS (data)
void lcd_data(uint8_t data)
{
	GPIOPinWrite(GPIO_PORTK_BASE, PORT_K_BUS_DATA_OUTPUT, data);
}


void lcd_print_char(char c)
{
	lcd_write(c, 0x5, 40);
}


void lcd_print_string(char* string)
{
	char* aux = 0;
	
	for(aux = string; *aux != '\0'; aux++)
	{
		lcd_print_char(*aux);
	}
}


void lcd_setup(void)
{
	// 0x38 -> LCD initialization = 0x20 / 8 bits mode = 0x10 / 2 lines = 0x08
	lcd_write(0x38, 0x4, 40);
	
	// 0x06 -> Cursor right autoincrement
	lcd_write(0x06, 0x4, 40);
	
	// 0xF -> Cursor initialization = 0x08 / Display enable = 0x04 / Cursor enable = 0x02 / Cursor blinking = 0x01
	lcd_write(0xF, 0x4, 40);
	
	// 0x01 -> Display reset
	lcd_write(0x01, 0x4, 3000);
}


void lcd_new_line(void)
{
	lcd_write(0xC0, 0x4, 40);
}


void lcd_write(uint8_t data, uint8_t command, uint32_t clock_duration_us)
{
	lcd_data(data);
	
	lcd_command(command);
	delay_us(clock_duration_us);
	
	// 0x0 -> Disable
	lcd_command(0x0);
	delay_us(clock_duration_us);
}
