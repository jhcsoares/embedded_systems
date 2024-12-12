#include "uart_.h"

void uart_interruption_handler(void)
{	
  UARTIntClear(UART0_BASE, UARTIntStatus(UART0_BASE, true));
	
	// Read the next character coming from UART
	int32_t next_character = UARTCharGetNonBlocking(UART0_BASE);
	
	if(next_character < 0x80)
	{
		rx_buffer_counter++;
		
		// Rotates circular buffer
		rx_buffer[0] = rx_buffer[1];
		rx_buffer[1] = rx_buffer[2];
		rx_buffer[2] = rx_buffer[3];
		rx_buffer[3] = (char)next_character;
		
		// Received entire message from client
		if(rx_buffer_counter == 4)
		{
			received_command = 1;
			rx_buffer_counter = 0;
		}
	}
}


void uart_print_char(char c)
{
	UARTCharPut(UART0_BASE, c);
}


void uart_print_string(char* string)
{
	char* aux = 0;
	for(aux = string; *aux != 0; aux++)
		UARTCharPut(UART0_BASE, *aux);
}


void uart_setup(void)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0));
  
	UARTConfigSetExpClk(UART0_BASE, sys_clock, 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
  
	UARTFIFODisable(UART0_BASE);
	
  UARTIntEnable(UART0_BASE, UART_INT_RX);
  UARTIntRegister(UART0_BASE, uart_interruption_handler);
  
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));
	
  GPIOPinConfigure(GPIO_PA0_U0RX);
  GPIOPinConfigure(GPIO_PA1_U0TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE, (GPIO_PIN_1 | GPIO_PIN_0));
}
