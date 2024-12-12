#include "gpio.h"


void gpio_setup(void)
{
	// Port F initialization as output (PF4 -- PF0) built-in leds
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, PORT_F_BUS_DATA_OUTPUT);

	// Port N initialization as output (PN1 -- PN0) built-in leds
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION));
	GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, PORT_N_BUS_DATA_OUTPUT);
}
