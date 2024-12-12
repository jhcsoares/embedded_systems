#include "led.h"


uint8_t get_leds_status(void)
{
	uint8_t led_0_status = GPIOPinRead(GPIO_PORTN_BASE, 0x2);
	if(led_0_status)
		led_0_status = 1;
	
	uint8_t led_1_status = GPIOPinRead(GPIO_PORTN_BASE, 0x1);
	if(led_1_status)
		led_1_status = 1;
	
	uint8_t led_2_status = GPIOPinRead(GPIO_PORTF_BASE, 0x10);
	if(led_2_status)
		led_2_status = 1;
	
	uint8_t led_3_status = GPIOPinRead(GPIO_PORTF_BASE, 0x1);
	if(led_3_status)
		led_3_status = 1;
	
	uint8_t leds_status = led_0_status * 8 + led_1_status * 4 + led_2_status * 2 + led_3_status * 1;

	return leds_status;
}


void turn_off_led(uint8_t led_id)
{
	if(led_id == 0)
		GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x0);
	
	else if(led_id == 1)
		GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
	
	else if(led_id == 2)
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x0);
	
	else if(led_id == 3)
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);
}


void turn_off_leds(void)
{
	uint8_t i = 0;
	for(i = 0; i < 4; i++)
		turn_off_led(i);
}

void turn_on_led(uint8_t led_id)
{
	if(led_id == 0)
		GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x2);
	
	else if(led_id == 1)
		GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x1);
	
	else if(led_id == 2)
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x10);
	
	else if(led_id == 3)
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x1);
}


void turn_on_leds(void)
{
	uint8_t i = 0;
	for(i = 0; i < 4; i++)
		turn_on_led(i);
}
