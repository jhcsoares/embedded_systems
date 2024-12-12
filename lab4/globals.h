#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <stdint.h>
#include "inc/hw_memmap.h"

#define PORT_F_BUS_DATA_OUTPUT GPIO_PIN_4 | GPIO_PIN_0
#define PORT_N_BUS_DATA_OUTPUT GPIO_PIN_1 | GPIO_PIN_0

extern uint8_t received_command;
extern uint8_t rx_buffer_counter;
extern char rx_buffer[5];
extern uint32_t sys_clock;
extern uint32_t sys_tick;

#endif // __GLOBALS_H__
