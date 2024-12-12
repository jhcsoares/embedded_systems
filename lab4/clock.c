#include "clock.h"

void clock_setup(uint32_t frequency)
{
	sys_clock = SysCtlClockFreqSet(SYSCTL_XTAL_25MHZ, frequency);
}
