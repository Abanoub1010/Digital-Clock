/*
 * LCD_Prog.c
 *
 *  Created on: Nov 25, 2022
 *      Author: Abanoub
 */
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "LCD_Priv.h"
#include "LCD_Config.h"
#include <avr/delay.h>

void HLCD_voidInit(void)
{



	_delay_ms(100);
	HLCD_voidSendCommand(FUNCTION_SET_8BIT);
	_delay_ms(2);
	HLCD_voidSendCommand(LCD_DISPLAY);
	_delay_ms(2);
	HLCD_voidSendCommand(LCD_CLEAR);
	_delay_ms(2);
	HLCD_voidSendCommand(LCD_ENTRYMODE);

}
void HLCD_voidSendCommand(u8 Copy_u8Cmd)
{
	//RS LOW
	DIO_vidSetPinVal(LCD_CONTROL_PORT,LCD_RS_PIN,DIO_LOW);
	//Command
	DIO_vidSetPortVal(LCD_DATA_PORT,Copy_u8Cmd);
	//Enable
	DIO_vidSetPinVal(LCD_CONTROL_PORT,LCD_E_PIN,DIO_HIGH);
	_delay_ms(1);
	DIO_vidSetPinVal(LCD_CONTROL_PORT,LCD_E_PIN,DIO_LOW);

}
void HLCD_voidSendChar(u8 Copy_u8Char)
{
	//RS LOW
	DIO_vidSetPinVal(LCD_CONTROL_PORT,LCD_RS_PIN,DIO_HIGH);
	//Command
	DIO_vidSetPortVal(LCD_DATA_PORT,Copy_u8Char);
	//Enable
	DIO_vidSetPinVal(LCD_CONTROL_PORT,LCD_E_PIN,DIO_HIGH);
	_delay_ms(1);
	DIO_vidSetPinVal(LCD_CONTROL_PORT,LCD_E_PIN,DIO_LOW);
}

void HLCD_voidGotoxy(u8 X,u8 Y)
{
	if(Y==0)
	{
	HLCD_voidSendCommand(LCD_SETCURSER|X) ;
	}
	else
	{
		HLCD_voidSendCommand((LCD_SETCURSER|X) | (0x40)) ;
	}

}

void HLCD_voidSendString(u8 *Copy_u8ptrString)
{

	while(*Copy_u8ptrString!='\0')
	{
		HLCD_voidSendChar(*Copy_u8ptrString);
		Copy_u8ptrString++;

	}
}

void LCD_Send_Num(int num)
{
	int txt[10] = {0};					// Array holds the number in digits
	int i = 0;						// Iterator
	if(num == 0)
	{
		HLCD_voidSendChar('0');
		return;
	}
	for(i = 0; num != 0; i++)
	{
		txt[i] = num%10 +48;				// Get the ASCII code of the rightmost digit
		num = num/ 10;					// Remove the rightmost digit
	}
	i--;
	while(i >= 0 )
	{
		HLCD_voidSendChar(txt[i]);				// Display the digits in reverse order
		i--;
	}
}
void LCD_Send_Float(float num)
{
	f32 num2ndPart;
	s32 num1stPart = (u32) num;
	LCD_Send_Num(num1stPart);

	num2ndPart = (f32) num-num1stPart;
	if (num < 0) {
		num2ndPart = (f32) (-1) * (num2ndPart);
	}
	if(((f32)num-num1stPart)>0)
	{
		HLCD_voidSendChar('.');
			u8 zero_flag=0,temp;
			for (u8 i = 1; i <= 4; i++) {
				num2ndPart = num2ndPart * 10;
				 temp = (u8) num2ndPart;
				if((temp==0)&&zero_flag&&i<=3)
				{
					HLCD_voidSendChar('0');
					break;
				}
				else if(zero_flag&&(temp>0))
				{
					if(temp>=4)
						HLCD_voidSendChar('1');
					else
						HLCD_voidSendChar('0');
					break;
				}
				else if(temp==0)
				{
					zero_flag=1;
				}
				else
				{
					HLCD_voidSendChar(temp + '0');
				}
				num2ndPart = (f32) (num2ndPart - temp);
			}
	}
	}
