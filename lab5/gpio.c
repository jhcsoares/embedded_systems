#include "gpio.h"

void gpio_setup(void)
{
	// Port B initialization as I2C0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB));  
	GPIOPinConfigure(GPIO_PB2_I2C0SCL);
	GPIOPinConfigure(GPIO_PB3_I2C0SDA);
	GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
	GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);
	
	
	// Port D initialization as I2C7
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)); 
	GPIOPinConfigure(GPIO_PD0_I2C7SCL);
	GPIOPinConfigure(GPIO_PD1_I2C7SDA);
	GPIOPinTypeI2CSCL(GPIO_PORTD_BASE, GPIO_PIN_0);
	GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_1);
	
	// Port F initialization as output (PF4) built-in leds
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4);
	
	// Configure PF0 as a PWM pin
	GPIOPinConfigure(GPIO_PF0_M0PWM0);
	GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_0);
	
	// Enable alternate function (PWM) of PF0
	GPIOPinConfigure(GPIO_PF0_M0PWM0);
	
	
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


	// Port N initialization as output (PN1 -- PN0) built-in leds
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION));
	GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, PORT_N_BUS_DATA_OUTPUT);
}
