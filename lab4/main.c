#include "clock.h"
#include "globals.h"
#include "gpio.h"
#include "led.h"
#include "sys_tick.h"
#include "uart_.h"

// Initializating global variables
uint8_t received_command = 0;
uint8_t rx_buffer_counter = 0;
char rx_buffer[5] = {0, 0, 0, 0, 0};

uint32_t sys_tick = 0;
uint32_t sys_clock = 0;

int main()
{
	// 80MHz
	clock_setup(80000000);
	sys_tick_setup();
	gpio_setup();
	uart_setup();
	
	while(1)
	{	
		if(received_command)
		{			
			// Command decoder
			char b0 = rx_buffer[0];
			char b1 = rx_buffer[1];
			char b2 = rx_buffer[2];
			char b3 = rx_buffer[3];
			
			//////////////////////////Error codes///////////////////////
			if(b0 != '#')
				uart_print_string("Missing start byte\n");
			
			else if(b1 != 'R' && b1 != 'T')
				uart_print_string("Incorrect hardware selection byte\n");
			
			else if(b2 != '0' && b2 != '1' && b2 != '2' && b2 != '3' && b2 != 'X' && b2 != 'S')
				uart_print_string("Incorrect hardware ID byte\n");
			
			else if(b3 != '0' && b3 != '1' && b3 != 'T')
				uart_print_string("Incorrect hardware status byte\n");
			//////////////////////////////////////////////////////////
			
			//////////////////////////Actions///////////////////////
			else
			{
				// Handle a single led
				if(b1 == 'R')
				{
					uint8_t led_id = b2 - '0';
					
					// Turn off led
					if(b3 == '0')
					{
						turn_off_led(led_id);
						
						char response[6] = {'@', 'R', b2, '0', '\n', 0};
						uart_print_string(response);
					}
					
					// Turn on led
					else if(b3 == '1')
					{
						turn_on_led(led_id);
						
						char response[6] = {'@', 'R', b2, '1', '\n', 0};
						uart_print_string(response);
					}
				}
				
				// Handle all leds
				else if(b1 == 'T')
				{
					// Change leds status
					if(b2 == 'X')
					{
						// Turn off leds
						if(b3 == '0')
						{
							turn_off_leds();
							
							char response[6] = {'@', 'T', 'X', '0', '\n', 0};
							uart_print_string(response);
						}
						
						else if(b3 == '1')
						{
							turn_on_leds();
							
							char response[6] = {'@', 'T', 'X', '1', '\n', 0};
							uart_print_string(response);
						}
					}
					
					// Get leds status
					else if(b2 == 'S')
					{
						// Added 64 to offset ASCII characters according to the decoding table in lab instructions
						char decoded_leds_status = get_leds_status() + 64;
						
						char response[6] = {'@', 'T', 'S', decoded_leds_status, '\n', 0};
						uart_print_string(response);
					}
				}
			}
			
			// Need to restart the flag to decode a new message from client
			received_command = 0;
		}
	}
}