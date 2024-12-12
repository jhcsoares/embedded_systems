#include "gpio.h"

void gpio_setup(void)
{
	// Port J initialization as input (PJ1 -- PJ0)
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ));
	GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, PORT_J_BUS_DATA_INPUT);
	// Pull-up resistor
	GPIOPadConfigSet(GPIO_PORTJ_BASE, PORT_J_BUS_DATA_INPUT, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	
	// Port K initialization as output (PK7 -- PK0)
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOK));
	GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE, PORT_K_BUS_DATA_OUTPUT);
	
	// Port L initialization as input (PL3 -- PL0)
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOL));
	GPIOPinTypeGPIOInput(GPIO_PORTL_BASE, PORT_L_BUS_DATA_INPUT);
	// Pull-up resistor
	GPIOPadConfigSet(GPIO_PORTL_BASE, PORT_L_BUS_DATA_INPUT, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	
	// Port M initialization as input (PM7 -- PM4)
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOM));
	GPIOPinTypeGPIOInput(GPIO_PORTM_BASE, PORT_M_BUS_DATA_INPUT);
	
	// Port M initialization as output (PM2 -- PM0)
	GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, PORT_M_BUS_DATA_OUTPUT);

	// Port N initialization as output (PN1 -- PN0) built-in leds
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION));
	GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, PORT_N_BUS_DATA_OUTPUT);
}
