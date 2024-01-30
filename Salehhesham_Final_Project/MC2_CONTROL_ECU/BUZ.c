/*
 *     File name: TIM1.c
 *        Author: Saleh
 *   Description: Source file of BUZZER-Driver.
 *    Created on: Oct 28, 2022
 */

#include "BUZ.h"

/*
 *     Description: Function to initialize the BUZZER-DRIVER.
 */
void Buzzer_init(void)
{
	/* Set The direction of the BUZZER Pin */
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PIN_OUTPUT);

	/* Turn OFF the BUZZER Initially */
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}

/*
 *     Description: Function to Turn ON the BUZZER.
 */
void Buzzer_on(void)
{
	/* Turn ON the BUZZER Initially */
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_HIGH);
}

/*
 *     Description: Function to Turn OFF the BUZZER.
 */
void Buzzer_off(void)
{
	/* Turn ON the BUZZER Initially */
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}
