#include "sys_tick.h"

void delay_ms(float ms)
{
	delay_us(1000 * ms);
}

void delay_us(float us)
{
	uint32_t t0 = sys_tick;
	
	while(us)
	{
		if(sys_tick != t0)
		{
			t0 = sys_tick;
			us--;
		}
	}
}

// This handler is called every 1 us
void sys_tick_interrupt_handler(void)
{
	sys_tick++;
}

void sys_tick_setup(void)
{
	SysTickDisable();
	
	// Setting up sys_tick to count every 1us
	SysTickPeriodSet(sys_clock / 1000000);
	
	SysTickIntRegister(sys_tick_interrupt_handler);
	SysTickIntEnable();
  SysTickEnable();
}
