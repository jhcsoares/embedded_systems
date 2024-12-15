#include <stdio.h>
#include "clock.h"
#include "globals.h"
#include "gpio.h"
#include "keyboard.h"
#include "lcd.h"
#include "sys_tick.h"

// Initializating global variables
uint32_t sys_tick = 0;
uint32_t sys_clock = 0;

int main()
{
	// 80MHz
	clock_setup(80000000);
	gpio_setup();
	sys_tick_setup();
	lcd_setup();

	lcd_print_string("ELF52-DaLuz:");
	
	// Battery sequence print
	lcd_write(0x00, 0x5, 40);
	lcd_write(0x02, 0x5, 40);
	lcd_write(0x04, 0x5, 40);
	lcd_write(0x06, 0x5, 40);
	
	lcd_new_line();
	lcd_print_string("Key: ");
	
	char pressed_key = 0;
	char lcd_buffer[13] = "";
	
	while(1)
	{	
		// Keys
		
		pressed_key = keyboard_scan();
		
		if(pressed_key == '1' || pressed_key == '4' || pressed_key == '7' || pressed_key == '*')
			GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0, 0x1);
		
		if(pressed_key == '2' || pressed_key == '5' || pressed_key == '8' || pressed_key == '0')
			GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0, 0x3);
		
		if(pressed_key == '3' || pressed_key == '6' || pressed_key == '9' || pressed_key == '#')
			GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0, 0x3);
		
		if(pressed_key == 'A' || pressed_key == 'B' || pressed_key == 'C' || pressed_key == 'D')
			GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0, 0x2);
		
		if(pressed_key == 0)
		{
			pressed_key = '?';
			GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0, 0x0);
		}
		
		
		// Push-buttons
		
		// J0 is pressed
		if(GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_1 | GPIO_PIN_0) == 0x1)
			GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0, 0x1);
		
		// J1 is pressed
		else if(GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_1 | GPIO_PIN_0) == 0x2)
			GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0, 0x2);
		
		// Both are pressed
		else if(GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_1 | GPIO_PIN_0) == 0x0)
			GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0, 0x3);
		
		// Turn of leds
		else if(GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_1 | GPIO_PIN_0) == 0x0)
			GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0, 0x0);
		
		// LCD update
		
		sprintf(lcd_buffer, "Key: [%X]-[%c]", pressed_key, pressed_key);
		lcd_write(0xC0, 0x4, 40);
		lcd_print_string(lcd_buffer);
	}
}
