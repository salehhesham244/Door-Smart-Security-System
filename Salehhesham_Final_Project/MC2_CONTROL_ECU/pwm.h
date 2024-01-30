/*
 *    file name : pwm.h
 *        Author: Saleh
 *  Description : header file of the PWM-DRIVER
 *    Created on: Oct 10, 2022
 */
#ifndef PWM_H_
#define PWM_H_

#include"std_types.h"
#include"gpio.h"

/*********************
 * SW Scope Variables
 **********************/

extern uint8 g_dutyCycle;

/*********************
 * Definitions
 **********************/

#define MAX_COMP_VALUE 255


/*********************
 * Prototypes
 **********************/

void PWM_Timer0_Start(uint8 dutyCycle);
void PWM_deinit(void);
#endif /* PWM_H_ */
