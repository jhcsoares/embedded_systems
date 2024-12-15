#include "keyboard.h"

char keyboard_scan(void)
{
	uint8_t gpio_pins_array[4] = {GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7};
	
	char keyboard_keys_matrix[4][4] = {'7', '8', '9', 'A',
																		 '4', '5', '6', 'B',
																		 '1', '2', '3', 'C',
																		 '#', '0', '*', 'D'};
	
	char pressed_button = 0;
																		 
	uint8_t i = 0;
	for(i = 0; i < 4; i++)
	{
		GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, gpio_pins_array[i]);
		GPIOPinWrite(GPIO_PORTM_BASE, gpio_pins_array[i], 0);
		
		int32_t row_read = GPIOPinRead(GPIO_PORTL_BASE, PORT_L_BUS_DATA_INPUT);
		
		if(row_read != 0xF)
		{
			if(row_read == 0xE)
				pressed_button = keyboard_keys_matrix[0][i];
		
			else if(row_read == 0xD)
				pressed_button = keyboard_keys_matrix[1][i];
			
			else if(row_read == 0xB)
				pressed_button = keyboard_keys_matrix[2][i];
			
			else
				pressed_button = keyboard_keys_matrix[3][i];
			
			// Set back high-impedance mode for the current pin
			GPIOPinTypeGPIOInput(GPIO_PORTM_BASE, gpio_pins_array[i]);
			
			return pressed_button;
		}
		
		// Set back high-impedance mode for the current pin
		GPIOPinTypeGPIOInput(GPIO_PORTM_BASE, gpio_pins_array[i]);
	}
	
	// Return 0 if no button is pressed
	return pressed_button;
}


void update_keyboard_buffer(char c)
{
	// The buffer is updated only when user presses a number
	if(c != 'A' && c != 'B' && c != 'C' && c != 'D' && c != '*' && c != '#')
	{
		// Rotates keyboard buffer
		keyboard_buffer[0] = keyboard_buffer[1];
		keyboard_buffer[1] = c;
	}
}
