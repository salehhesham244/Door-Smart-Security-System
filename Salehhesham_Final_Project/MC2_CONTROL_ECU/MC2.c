/*
 *     File name: MC2.c
 *        Author: Saleh
 *   Description: Main program of the Second Micro-controller.
 *    Created on: Oct 31, 2022
 */

#include <avr/io.h>
#include <util/delay.h>
#include "TIM1.h"
#include "uart.h"
#include "DC.h"
#include "BUZ.h"
#include "external_eeprom.h"
#include "twi.h"

/********************************************************************************************************
 *                                            DEFINITIONS
********************************************************************************************************/
/* Adjust setting of the Timer1-driver */
Timer1_ConfigType TIM_Config={0,58594,CLK_1024,COM};

#define  MATCHED    1
#define  NMATCHED   0

/********************************************************************************************************
 *                                            Used Variable
********************************************************************************************************/

uint8 checkMatching=0;
uint8 pass1[10];
uint8 pass2[10];
uint8 result;
uint8 count=0;
uint8 tick=0;
uint8 g_check=0;
uint8 buzzer_state=0;
uint8 saved=0;
uint8 Option_mode;
uint8 g_tick=0;

/********************************************************************************************************
 *                                            Functions
********************************************************************************************************/
/*
 *      Description: Function to check if two passwords are matched or not .
 */
uint8 check (uint8 * ptr1,uint8 * ptr2)
{
	uint8 k=0;
	for(uint8 i=0;i<5;++i)
	{
		if (ptr1[i]==ptr2[i])
		{
			k++;
		}
		else
		{
			return NMATCHED;
		}
	}
	if(k==5)
	{
		return MATCHED;
	}
}

void set_error(void)
{
	Buzzer_on();

	/* Change configurations to count 7.5 seconds*/
	TIM_Config.initial_value = 0;
	TIM_Config.compare_value = 58593;
	TIM_Config.prescaler = CLK_1024;

	/* Start timer to count 7.5 seconds*/
	Timer1_init(&TIM_Config);

	/* wait for timer to finish counting eight times!*/
	/* 60 seconds*/
	while(g_tick !=8){}
	g_tick =0;

	Buzzer_off();

	/* Change configurations to STOP*/
	TIM_Config.initial_value = 0;
	TIM_Config.prescaler = NO_CLK;

	/* Stop the timer*/
	Timer1_init(&TIM_Config);
}

void set_openDoor(void)
{
	/* Call the call-back function once manually to
	 * start opening the door*/
	openDoor();

	/* Change configurations to count 7.5 seconds*/
	TIM_Config.prescaler = CLK_1024;
	TIM_Config.initial_value = 0;
	TIM_Config.compare_value = 58593;

	/* Start timer to count 7.5 seconds*/
	Timer1_init(&TIM_Config);

	/* wait for timer to finish counting twice!*/
	/* 15 seconds*/
	while(g_tick !=2){}
	g_tick =0;
	openDoor();

	/* Change configurations to count 3 seconds*/
	TIM_Config.initial_value = 0;
	TIM_Config.compare_value = 23438;

	/* Start timer to count 3 seconds*/
	Timer1_init(&TIM_Config);

	/* wait for timer to finish counting once!*/
	while(g_tick !=1){}
	g_tick = 0;
	openDoor();

	/* Change configurations to count 7.5 seconds*/
	TIM_Config.initial_value = 0;
	TIM_Config.compare_value = 58593;

	/* Start timer to count 7.5 seconds*/
	Timer1_init(&TIM_Config);

	/* wait for timer to finish counting twice!*/
	/* 15 seconds*/
	while(g_tick !=2){}
	g_tick =0;
	openDoor();

	/* Change configurations to STOP*/
	TIM_Config.initial_value = 0;
	TIM_Config.prescaler = NO_CLK;

	/* Stop the timer*/
	Timer1_init(&TIM_Config);
}
/* Count ticks */
void ticks (void)
{

	++g_tick;
}


void openDoor(void)
{
	static uint8 callNum = 1;

	switch (callNum)
	{
	case 1:
		DcMotor_Rotate(CW, 100);
		break;
	case 2:
		DcMotor_Rotate(STOP, 0);
		break;
	case 3:
		DcMotor_Rotate(A_CW, 100);
		break;
	case 4:
		DcMotor_Rotate(STOP, 0);
		break;
	}
	callNum++;
	if(callNum > 4)
		callNum = 1;
}
/********************************************************************************************************/

int main()
{
	SREG|=(1<<7);//To Enable Interrupts.

	/* Adjust setting of the I2C-driver */
	TWI_ConfigType TWI_Config={ADD_1,FAST_MODE};
	/* Adjust setting of the uart-driver */
	UART_ConfigType uart_config ={ASYNCH,DISABLE,ONEBIT,BITS_8,BAUD_96H};
	/* Initialize the UART-Driver */
	UART_init(&uart_config);
	/* Initialize The I2C-Driver */
	TWI_init(&TWI_Config);
	/* Initialize The Buzzer-Driver */
	Buzzer_init();
	/* Initialize The DC-Motor-Driver */
	MOTOR_init();
	/* Set The Function of TheCallBack Function */
	Timer1_setCallBack(ticks);
	while(1)
	{
		if(saved==0)
		{
			/* Receive The first entered Password */
			UART_receiveString(pass1);

			/* Receive The Second entered Password */
			UART_receiveString(pass2);

			/* Check if The two Passwords are equal */
			result=check(pass1, pass2);

			if(result)
			{
				UART_sendByte(result);
			}
			else
			{
				UART_sendByte(result);
			}

			/* Save The Password inside EEPROM */
			for(uint8 i=0;i<5;++i)
			{
				EEPROM_writeByte(0x0311+i,pass1[i]);
			}
			/* Get the Saved Password From EEPROM */
			for(uint8 i=0;i<5;++i)
			{
				EEPROM_readByte(0x0316-i,pass1[i]);
				saved=1;
			}
		}
		else
		{
			UART_receiveString(pass2);
			Option_mode=UART_recieveByte();
			result=check(pass1, pass2);
			/* Open door mode */
			if(Option_mode=='+')
			{
				saved=1;
				if(result)
				{
					UART_sendByte(result);
			    	set_openDoor();
				}
				else
				{
					UART_sendByte(result);
					buzzer_state=UART_recieveByte();
					if(buzzer_state==3)
					{
						saved=1;
                        set_error();
					}
				}
			}
			/* Change password mode */
			else
			{
				/* They are matched */
				if(result==1)
				{
					UART_sendByte(result);
					/* To save it again */
					saved=0;
				}
				else
				{
					UART_sendByte(result);
					buzzer_state=UART_recieveByte();
					if(buzzer_state==3)
					{
						saved=1;
						set_error();
					}
				}
			}
		}
	}
	return 0;
}
