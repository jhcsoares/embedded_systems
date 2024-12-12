#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <stdbool.h>
#include <stdint.h>
#include "driverlib/gpio.h"
#include "globals.h"
#include "inc/hw_memmap.h"

char keyboard_scan(void);

#endif // __KEYBOARD_H__