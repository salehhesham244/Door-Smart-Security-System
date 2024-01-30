/*
 *     File name: TIM1.c
 *        Author: Saleh
 *   Description: Source file of TIMER1-Driver.
 *    Created on: Oct 28, 2022
 */

#include "TIM1.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/* Interrupt Service Routine of COMPARE mode*/
ISR(TIMER1_COMPA_vect)
{
	if(g_Timer1_Call_Back_Ptr!=NULL_PTR)
		/* Call the Call back function in the Application */
		g_Timer1_Call_Back_Ptr();}

/* Interrupt Service Routine of COMPARE mode*/
ISR(TIMER1_OVF_vect)
{

	if(g_Timer1_Call_Back_Ptr!=NULL_PTR)
		/* Call the Call back function in the Application */
		g_Timer1_Call_Back_Ptr();
}

/*
 *  Description: Function to initialize the Timer driver.
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{


	/* Set the Initial Value */
	TCNT1 = Config_Ptr->initial_value;

	/* Set the Compared Value */
	OCR1A = Config_Ptr->compare_value;
	/*                   * For TCCR1A *
	 *       FOC1A : Set 1 to disable PWM mode.
	 *       FOC1B : Set 1 to disable PWM mode.
	 * WGM11&WGM10 : Set 0 to select Normal or Compare Mode.
	 *    COM1A1:0 : Set 1OR0 depends on the Selected Mode .
	 *    COM1B1:0 : Set 1OR0 depends on the Selected Mode .
	 */

	TCCR1A = (1<<FOC1A)|(1<<FOC1B);


	/*                   * For TCCRB1 *
	 *   CS10:CS12 : Set the Selected Prescaler in it.
	 * WGM12&WGM13 : Set 0 to Select Normal or Compare Mode.
	 *       ICNC1 : Set 0 to Disable The Noise Canceler.
	 *       ICES1 : Set 0 to Disable The Input Capture Select Due to putting The Top Value in it .
	 */

	TCCR1B = (TCCR1B & 0XF8) | ((Config_Ptr->prescaler & 0X07)<<0);

	/* Set the Selected Mode */
	TCCR1B=  (TCCR1B & 0XE7) | ((Config_Ptr->mode & 0X01)<<3);

	/* Enable The Interrupts of Timer1 */
	if(Config_Ptr->mode==0)
	{
		/* Enable The Overflow Interrupt */
		TIMSK |= (1<<TOIE1);
	}
	else
	{
		/* Enable The CTC Interrupt */
		TIMSK |= (1<<OCIE1A);
	}
}

/*
 *  Description: Function to disable the Timer1.
 */
void Timer1_deInit(void)
{
	TCCR1A=0;
	TCCR1B=0;
	OCR1A=0;
	TCNT1=0;
	TIMSK=0;
}


/*
 *  Description: Function to set the Call Back function address.
 */
void Timer1_setCallBack(void(*a_ptr)(void))
{
	/* Put the Address of The CallBack Function in The Global Pointer */
	g_Timer1_Call_Back_Ptr=a_ptr;
}

