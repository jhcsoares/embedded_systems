#ifndef __LED_H__
#define __LED_H__

#include <stdbool.h>
#include <stdint.h>
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "globals.h"
#include "pwm.h"

uint8_t get_led0_status(void);
uint8_t get_led1_status(void);
uint8_t get_led2_status(void);
uint8_t get_leds_status(void);
void set_led_duty_cycle(void);
void turn_off_led(uint8_t led_id);
void turn_off_leds(void);
void turn_on_led(uint8_t led_id);
void turn_on_leds(void);

#endif // __LED_H__
