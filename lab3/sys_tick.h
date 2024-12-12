#ifndef __SYS_TICK_H__
#define __SYS_TICK_H__

#include <stdint.h>
#include "driverlib/systick.h"
#include "globals.h"

void delay_ms(float ms);
void delay_us(float us);
void interrupt_handler(void);
void sys_tick_setup(void);

#endif // __SYS_TICK_H__
