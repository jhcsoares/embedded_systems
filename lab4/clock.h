#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <stdbool.h>
#include <stdint.h>
#include "driverlib/sysctl.h"
#include "globals.h"
#include "inc/hw_memmap.h"

void clock_setup(uint32_t frequency);

#endif // __CLOCK_H__
