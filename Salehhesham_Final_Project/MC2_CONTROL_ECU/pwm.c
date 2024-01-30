/*
 *    file name: pwm.c
 *       Author: Saleh
 *  description: source file of the PWM-DRIVER
 *   Created on: Oct 10, 2022
 */
#include<avr/io.h>
#include"pwm.h"

/*********************
 * Functions
 **********************/

void PWM_Timer0_Start(uint8 dutyCycle)
{
	/* WGM01 & WGM02 : Fast PWM mode
	 * COM01 : non_inverting
	 * CS01 : freq of timer = fcpu/8 */
	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<CS01);

	/* Initial value of timer counter is zero*/
	TCNT0 = 0;

	/* Setting the compare value controls the duty cycle of
	 * the PWM as Timer0 is an eight bit timer thereby the max
	 * compare value is 255 this is 100% duty cycle and 128 is
	 * 50% duty cycle and 64 is 25% duty cycle*/
	OCR0 = dutyCycle;

	/* PWM pin set to output */
	GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);
}

void PWM_deinit(void)
{
	TCCR0 = 0;
	TCNT0 = 0;
	OCR0 = 0;
}
