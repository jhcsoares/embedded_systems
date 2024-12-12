#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <stdint.h>
#include "inc/hw_memmap.h"

#define PORT_J_BUS_DATA_INPUT GPIO_PIN_1 | GPIO_PIN_0
#define PORT_K_BUS_DATA_OUTPUT GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0
#define PORT_L_BUS_DATA_INPUT GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0
#define PORT_M_BUS_DATA_INPUT GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_5 | GPIO_PIN_4
#define PORT_M_BUS_DATA_OUTPUT GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0
#define PORT_N_BUS_DATA_OUTPUT GPIO_PIN_1 | GPIO_PIN_0

extern uint32_t sys_clock;
extern uint32_t sys_tick;

#endif // __GLOBALS_H__
