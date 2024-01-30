/*
 *    File name: DC.c
 *       Author: Saleh
 *  Description: Source file of the DC-MOTOR DRIVER
 *   Created on: Oct 11, 2022
 */

#include "gpio.h"
#include "std_types.h"
#include "pwm.h"
#include "DC.h"
#include <avr/io.h>

void MOTOR_init(void)
{
	/* Set the two needed pins for the motor*/
	GPIO_setupPinDirection(DC_PORT, DC_PIN1, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_PORT, DC_PIN2, PIN_OUTPUT);

	/* Motor is initially off */
	GPIO_writePin(DC_PORT, DC_PIN1 , LOGIC_LOW);
	GPIO_writePin(DC_PORT, DC_PIN2 , LOGIC_LOW);
}

void DcMotor_Rotate(DcMotor_State state,uint8 a_speed)
{
	uint8 speed;
	switch (state)
	{
	case STOP :
		GPIO_writePin(DC_PORT, DC_PIN1 , LOGIC_LOW);
		GPIO_writePin(DC_PORT, DC_PIN2 , LOGIC_LOW);
		break;
	case CW :
		GPIO_writePin(DC_PORT, DC_PIN1 , LOGIC_HIGH);
		GPIO_writePin(DC_PORT, DC_PIN2 , LOGIC_LOW);
		break;
	case A_CW :
		GPIO_writePin(DC_PORT, DC_PIN1 , LOGIC_LOW);
		GPIO_writePin(DC_PORT, DC_PIN2 , LOGIC_HIGH);
		break;
	}
	speed =  (uint8)ceil( ((float)a_speed/100)*MAX_COMP_VALUE );
	if(speed !=0)
		PWM_Timer0_Start(speed) ;
	else
		PWM_deinit();
	/* We used a value that we don't know which is the max compare
	 * value. we got it from the PWM.h so the structure is still
	 * layered as the motor doesn't know the value and the eqn
	 * is independent just like the sensor reference*/

}
