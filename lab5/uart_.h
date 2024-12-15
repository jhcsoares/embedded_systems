#ifndef __UART__H__
#define __UART__H__

// Used to identify the microcontroller in .h files of TivaWare (it defines the GPIO_PA1_U0TX and GPIO_PA0_U0RX addresses)
#define PART_TM4C1294NCPDT 1

#include <stdbool.h>
#include <stdint.h>
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "globals.h"
#include "inc/hw_memmap.h"

void uart_interruption_handler(void);
void uart_print_char(char c);
void uart_print_string(char* string);
void uart_setup(void);

#endif // __UART__H__
