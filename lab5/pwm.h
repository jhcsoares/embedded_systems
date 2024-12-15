#ifndef __PWM_H__
#define __PWM_H__

#include <stdbool.h>
#include <stdint.h>
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "globals.h"
#include "inc/hw_memmap.h"

void pwm_setup(uint32_t frequency);
void set_duty_cicle(uint8_t duty_cicle_pct);

#endif // __PWM_H__
