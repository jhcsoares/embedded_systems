#ifndef __GPIO_H__
#define __GPIO_H__

#define PART_TM4C1294NCPDT 1

#include <stdbool.h>
#include <stdint.h>
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "globals.h"

void gpio_setup(void);

#endif // __GPIO_H__
