#define PART_TM4C1294NCPDT 1

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/gpio.h"
#include "clock.h"
#include "decoder.h"
#include "gpio.h"
#include "i2c_.h"
#include "keyboard.h"
#include "led.h"
#include "pwm.h"
#include "ssd1306.h"
#include "sys_tick.h"


// Initializating global variables
uint8_t current_duty_cycle_pct = 0;
uint32_t pwm_load_value = 0;
uint8_t received_command = 0;
char keyboard_buffer[2] = {'0', '0'};
uint8_t rx_buffer_counter = 0;
char rx_buffer[5] = {0, 0, 0, 0, 0};
uint32_t sys_clock = 0;
uint32_t sys_tick = 0;


int main(void)
{
	clock_setup(120000000);
	sys_tick_setup();
	gpio_setup();
	pwm_setup(1000);
	uart_setup();
	i2c_setup();
	
	OLED0_Init();
	SSD1306_I2C0_cls();
	SSD1306_I2C0_UpdateScreen();
	
	OLED7_Init();
	OLED7_clearDisplay();

	while (1)
	{
		// Keyboard scan
		char pressed_key = keyboard_scan();
		
		if(pressed_key)
		{
			// Debounce
			delay_ms(150);
			
			update_keyboard_buffer(pressed_key);
			
			if(pressed_key == '#')
			{
				set_led_duty_cycle();
				keyboard_buffer[0] = '0';
				keyboard_buffer[1] = '0';
			}
		}
		
		// Received command from UART
		if(received_command)
		{
			decoder();
			
			// Need to restart the flag to decode a new message from client
			received_command = 0;
		}
		
		// OLED0 update
		uint8_t led_0_status = get_led0_status() + '0';
		uint8_t led_1_status = get_led1_status() + '0';
		uint8_t led_2_status = get_led2_status() + '0';
		
		OLED0_sendStrXY("Led 0 status: ", 0, 0);
		OLED0_sendCharXY(led_0_status, 0, 14);
		
		OLED0_sendStrXY("Led 1 status: ", 1, 0);
		OLED0_sendCharXY(led_1_status, 1, 14);
		
		OLED0_sendStrXY("Led 2 status: ", 2, 0);
		OLED0_sendCharXY(led_2_status, 2, 14);
		
		
		// OLED7 update
		OLED7_sendStrXYI("Duty cycle: ", 0, 0);
		OLED7_send8BitNumber(current_duty_cycle_pct, 0, 12);
		
		OLED7_sendStrXYI("DC buffer: ", 1, 0);
		OLED7_sendCharXYI(keyboard_buffer[0], 1, 11);
		OLED7_sendCharXYI(keyboard_buffer[1], 1, 12);
	}
}

