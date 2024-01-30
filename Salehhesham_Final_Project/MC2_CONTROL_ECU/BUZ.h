/*
 *     File name: TIM1.h
 *        Author: Saleh
 *   Description: Header file of BUZZER-Driver.
 *    Created on: Oct 28, 2022
 */

#ifndef BUZ_H_
#define BUZ_H_
#include "gpio.h"
/********************************************************************************************************/
                                          /* TYPES DEFINITIONS */
/********************************************************************************************************/
#define BUZZER_PORT_ID         PORTD_ID
#define BUZZER_PIN_ID          PIN7_ID

/********************************************************************************************************/

/********************************************************************************************************/
                                         /* FUNCTIONS DEFINITIONS */
/********************************************************************************************************/
/*
 *     Description: Function to initialize the BUZZER-DRIVER.
 */
void Buzzer_init(void);

/*
 *     Description: Function to Turn ON the BUZZER.
 */
void Buzzer_on(void);

/*
 *     Description: Function to Turn OFF the BUZZER.
 */
void Buzzer_off(void);

#endif /* BUZ_H_ */
