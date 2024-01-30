/*
 *    File name: DC.h
 *       Author: Saleh
 *  Description: Header file of the DC-MOTOR DRIVER
 *   Created on: Oct 11, 2022
 */

#ifndef DC_H_
#define DC_H_
#include "std_types.h"

/*===================================================================================*/
                                       /* TYPES DEFINITOIN */
/*===================================================================================*/

#include"common_macros.h"
#include"std_types.h"
#include"gpio.h"
#include"pwm.h"
/*********************
 * Definitions
 **********************/

/* Static configuration just like the LCD screen as it cannot
 * Be changed during runtime */

#define DC_PORT PORTB_ID
#define DC_PIN1 PIN1_ID
#define DC_PIN2 PIN2_ID

typedef enum {
	 STOP,A_CW,CW
}DcMotor_State;
/*********************
 * Prototypes
 **********************/

void MOTOR_init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DC_H_ */
