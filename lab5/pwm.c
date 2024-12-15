#include "pwm.h"

void pwm_setup(uint32_t frequency)
{
	// Use PWM Module 0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0); 
	
	// Configure the PWM generator
	uint32_t pwm_clock = sys_clock / 64; 
	pwm_load_value = (pwm_clock / frequency) - 1;

	PWMClockSet(PWM0_BASE, PWM_SYSCLK_DIV_64);
	PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, pwm_load_value);

	// Enable the PWM generator
	PWMGenEnable(PWM0_BASE, PWM_GEN_0);
	
	// Starting PWM with duty cycle 0
	PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, false);
}

void set_duty_cicle(uint8_t duty_cicle_pct)
{
	current_duty_cycle_pct = duty_cicle_pct;
	
	if(duty_cicle_pct == 0)
		PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, false);
	
	else
	{
		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, (pwm_load_value * duty_cicle_pct) / 100);
		PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);
	}
}
