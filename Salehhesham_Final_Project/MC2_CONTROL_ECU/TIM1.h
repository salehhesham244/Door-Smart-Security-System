/*
 *     File name: TIM1.h
 *        Author: Saleh
 *   Description: Header file of TIMER1-Driver.
 *    Created on: Oct 28, 2022
 */

#ifndef TIM1_H_
#define TIM1_H_
#include "gpio.h"

/*****************************************************************************************************/
                                           /* USER TYPES DEFINITIONS */
/*****************************************************************************************************/
static volatile void (*g_Timer1_Call_Back_Ptr) (void)=NULL_PTR;

typedef enum
{
   /* Select the Prescaler-of the Timer1  */
   NO_CLK,CLK_1,CLK_8,CLK_64,CLK_256,CLK_1024,EXT_CLK_FALLING,EXT_CLK_RISING,
}Timer1_Prescaler;

typedef enum
{
   /* Modes of Timer1 without PWM */
   NORMAL,COM
}Timer1_Mode;

typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;

/********************************************************************************************************/

/*
 *  Description: Function to initialize the Timer driver.
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/*
 *  Description: Function to disable the Timer1.
 */
void Timer1_deInit(void);

/*
 *  Description: Function to set the Call Back function address.
 */
void Timer1_setCallBack(void(*a_ptr)(void));

#endif /* TIM1_H_ */
