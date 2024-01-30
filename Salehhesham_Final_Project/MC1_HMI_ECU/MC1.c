/*
 *     File name: MC1.c
 *        Author: Saleh
 *   Description: Main program of the First Micro-controller.
 *    Created on: Oct 31, 2022
 */
#include <avr/io.h>
#include "Keypad.h"
#include "lcd.h"
#include "TIM1.h"
#include "uart.h"
#include <util/delay.h>

/********************************************************************************************************
 *                                            DEFINITIONS
********************************************************************************************************/

#define  MATCHED    1u
#define  NMATCHED   0u
/* Adjust setting of the Timer1-driver */
Timer1_ConfigType TIM_Config={0,58600,CLK_1024,COM};

/*********************************************************************************************************/

/********************************************************************************************************
 *                                            Used Variable
********************************************************************************************************/

uint8 pass[7];
uint8 re_pass[7];
uint8 key=0;
uint8 count1=0;
uint8 count2=0;
uint8 confirm=0;
uint8 step1=0;
uint8 step2=0;
uint8 step3=0;
uint8 ready=0;
uint8 door_state;
uint8 chances=0;
uint8 tick=0;
uint8 check=0;
uint8 g_countCompleted=0;

/********************************************************************************************************
 *                                            Functions
********************************************************************************************************/
void error(void)
{
	static uint8 callNum = 1;

	switch (callNum)
	{
	case 1:
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 4, "ERROR");
		LCD_displayStringRowColumn(1, 4, "UNDETECTED");
		break;
	case 2:
		LCD_clearScreen();
		break;
	}
	callNum++;
	if(callNum > 2)
		callNum = 1;
	g_countCompleted = TRUE;

}


	void set_error(void)
	{
		/* Set the call back function to error so that
		 * the timer calls the error function when
		 * it finishes counting*/
		Timer1_setCallBack(error);

		/* Call the error function once manually to start the error message*/
		error();
		/* Reset the variable for the next iteration */
		g_countCompleted = FALSE;

		/* Set counter to count a minute*/
		TIM_Config.initial_value = 0;
		TIM_Config.compare_value = 58594;
		TIM_Config.prescaler = CLK_1024;

		/* Start timer to count 60 seconds*/
		Timer1_init(&TIM_Config);

		/* wait for timer to finish counting !*/
		/* 60 seconds*/
		while(!g_countCompleted){}
		/* Reset the variable for the next iteration */
		g_countCompleted = FALSE;

		/* Change configurations to STOP*/
		TIM_Config.initial_value = 0;
		TIM_Config.prescaler = NO_CLK;

		/* Stop the timer*/
		Timer1_init(&TIM_Config);

	}

	void openDoor(void)
	{
		static uint8 callNum = 1;

		switch (callNum)
		{
		case 1:
			LCD_clearScreen();
			LCD_displayString("Door Unlocking");
			break;
		case 2:
			LCD_clearScreen();
			LCD_displayString("Door Unlocked");
			break;
		case 3:
			LCD_clearScreen();
			LCD_displayString("Door Locking");
			break;
		case 4:
			LCD_clearScreen();
			break;
		}
		callNum++;
		if(callNum > 4)
			callNum = 1;
		g_countCompleted = TRUE;
	}

	void set_openDoor(void)
	{
		Timer1_setCallBack(openDoor);

		/* Call the call-back function once manually to
		 * start opening the door*/
		openDoor();
		/* Reset the flag variable for the next time
		 * the function get's called*/
		g_countCompleted = FALSE;


		/* Change configurations to count 15 seconds*/
		TIM_Config.initial_value = 0;
		TIM_Config.compare_value =14558;
		TIM_Config.prescaler = CLK_1024;

		/* Start timer to count 15 seconds*/
		Timer1_init(&TIM_Config);

		/* wait for timer to finish counting !*/
		/* 15 seconds*/
		while(!g_countCompleted){}
		g_countCompleted = FALSE;


		/* Change configurations to count 3 seconds*/
		TIM_Config.initial_value = 0;
		TIM_Config.compare_value = 2700;

		/* Start timer to count 3 seconds*/
		Timer1_init(&TIM_Config);

		/* wait for timer to finish counting !*/
		while(!g_countCompleted){}
		g_countCompleted = FALSE;


		/* Change configurations to count 15 seconds*/
		TIM_Config.initial_value = 0;
		TIM_Config.compare_value =14588;

		/* Start timer to count 15 seconds*/
		Timer1_init(&TIM_Config);

		/* wait for timer to finish counting !*/
		/* 15 seconds*/
		while(!g_countCompleted){}
		g_countCompleted = FALSE;

		/* Change configurations to STOP*/
		TIM_Config.initial_value = 0;
		TIM_Config.prescaler = NO_CLK;

		/* Stop the timer*/
		Timer1_init(&TIM_Config);

	}

/***********************************************************************************************************/


	int main()
	{
		/* Enable all interrupts */
		SREG|=(1<<7);
		/* Adjust setting of the uart-driver */
		UART_ConfigType uart_config ={ASYNCH,DISABLE,ONEBIT,BITS_8,BAUD_96H};
		/* Initialize the lcd-driver */
		LCD_init();
		/* Initialize the UART-Driver */
		UART_init(&uart_config);

		LCD_displayString("plz enter pass:");
		LCD_moveCursor(1,0);

		while(1)
		{
			/* Permission to start Step 1 */
			if (step1==0)
			{
				/* To enter the first Password */
				if (confirm==0)
				{
					/* get the pressed button from the keypad */
					key=KEYPAD_getPressedKey();

					if(key>=0 && key<=9)
					{
						/* Save the first Password */
						pass[count1]=key;
						++count1;
						/* display * character for each number*/
						LCD_displayCharacter('*');
						pass[5]='#';
						pass[6]='\0';
					}
				}
				else
				{
					/* get the pressed button from the keypad */
					key=KEYPAD_getPressedKey();
					if(key>=0 && key<=9)
					{
						/* Saved the Second Password */
						re_pass[count2]=key;
						++count2;
						/* display * character for each number*/
						LCD_displayCharacter('*');
						re_pass[5]='#';
						re_pass[6]='\0';
					}
					else if(key=='=')
					{
						/* sending the second password to The Uart-Driver */
						UART_sendString(re_pass);
						ready=1;
						key=0;
					}
				}
				/* check if enter button pressed */
				if(key=='=')
				{
					/* sending the first password to The Uart-Driver */
					UART_sendString(pass);
					LCD_clearScreen();
					LCD_displayString("plz re-enter the");
					LCD_moveCursor(1,0);
					LCD_displayString("same pass:");
					LCD_moveCursor(1,11);
					/* To enter the Second Password */
					confirm=1;
					count1=0;
					count2=0;
				}

				/* check if clear button pressed to enter the num again */
				else if(key==13)
				{
					LCD_clearScreen();
					LCD_displayString("plz enter pass: ");
					LCD_moveCursor(1,0);
				}
				_delay_ms(500); /* Press time */
				if(ready==1)
				{
					/* Get the result if they matched or not  */
					step1=UART_recieveByte();
					if (step1)
					{
						/* Displaying The main system options */
						LCD_clearScreen();
						LCD_displayString("+ : Open Door");
						LCD_moveCursor(1,0);
						LCD_displayString("- : Change Pass");
						key=KEYPAD_getPressedKey();
						_delay_ms(500);
						if(key=='+'||key=='-')
						{
							/* to go to OPTION List */
							step2=1;
						}
					}
					/* If the two passwords are wrong */
					else if (step1==0&&ready==1)
					{
						LCD_intgerToString(step1);
						LCD_clearScreen();
						LCD_displayString("WRONG PASS ENTER");
						LCD_moveCursor(1,0);
						LCD_displayString("Enter again");
						LCD_moveCursor(1,11);
						confirm=0;
						ready=0;
					}
				}
			}
			//Start Step2
			else if(step2==1)
			{
				if(key=='+'||key=='-')
				{
					LCD_clearScreen();
					LCD_displayString("plz enter pass:");
					LCD_moveCursor(1,0);
					step3=1;
					count1=0;
				}
			}
			if(step3==1)
			{
				if(key=='+')
				{
					while(key!='=')
					{

						key=KEYPAD_getPressedKey();
						if(key>=0 && key<=9)
						{
							pass[count1]=key;
							++count1;
							/* display * character for each number*/
							LCD_displayCharacter('*');
						}
						_delay_ms(500);
					}
					pass[5]='#';
					pass[6]='\0';
					step2=0;
					UART_sendString(pass);
					UART_sendByte('+');
					door_state=UART_recieveByte();
					LCD_clearScreen();
					if(door_state==1)
					{
						set_openDoor();
						LCD_displayString("+ : Open Door");
						LCD_moveCursor(1,0);
						LCD_displayString("- : Change Pass");
						key=KEYPAD_getPressedKey();
						_delay_ms(500);
						step2=1;
						step3=0;
					}
					else
					{
						step2=1;
						key='+';
						++chances;
						UART_sendByte(chances);
						if(chances==3)
						{
							set_error();
							LCD_displayString("+ : Open Door");
							LCD_moveCursor(1,0);
							LCD_displayString("- : Change Pass");
							key=KEYPAD_getPressedKey();
							_delay_ms(500);
							step2=1;
							step3=0;
							chances=0;
						}
					}
				}
				else if(key=='-')
				{
					while(key!='=')
					{
						key=KEYPAD_getPressedKey();
						if(key>=0 && key<=9)
						{
							pass[count1]=key;
							++count1;
							/* display * character for each number*/
							LCD_displayCharacter('*');
						}
						_delay_ms(500);
					}
					pass[5]='#';
					pass[6]='\0';
					UART_sendString(pass);
					UART_sendByte('-');
					/* Receive if they matched or not  */
					check=UART_recieveByte();
					/* Both Passwords are Matched */
					if(check)
					{
						LCD_clearScreen();
						LCD_displayString("Plz enter Pass:");
						LCD_moveCursor(1,0);
						/* To start the program from the begin */
						step1=0;
						step2=0;
						step3=0;
						ready=0;
						/* To send the first Pass */
						confirm=0;
					}
					/* They not matched */
					else
					{
						step2=1;
						key='-';
						++chances;
						UART_sendByte(chances);
						if(chances==3)
						{
							set_error();
							LCD_displayString("+ : Open Door");
							LCD_moveCursor(1,0);
							LCD_displayString("- : Change Pass");
							key=KEYPAD_getPressedKey();
							_delay_ms(500);
							step2=1;
							step3=0;
							chances=0;
						}
					}
				}
			}
		}
		return 0;
	}

