/*
 * main.c
 *
 *  Created on: Nov 26, 2022
 *      Author: Abanoub
 */
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "LCD_Config.h"
#include "KPD_Interface.h"
#include "TIMER_interface.h"
#include "GIE_interface.h"
#include <util/delay.h>


#define SET_CALENDER	2
#define SET_CLOCK		1
#define NORMAL_MODE	 	0
#define CHECKED 		1
#define INCREMENT 		1
#define DECREMENT 		2

#define HRS 			1
#define MINS 			2
#define SECS 			3
#define DAY 			4
#define MON 			5
#define YRS 			6
#define DAYSTATE		7

#define AM 				0
#define PM				1

#define OUT 			1
#define ENTER 			2

void NormalClock_ModeDisplay (void);

void Set_ClockEnterDisplay (void);

void Clock (void);
void Hours_Display (void);
void Minutes_Display (void);
void Seconds_Display (void);

void Day_Display (void);
void Month_Display (void);
void Year_Display (void);

void DayState_Display (void);

void Set_ClockEnterDisplay (void);
void Set_CalendarEnterDisplay (void);

void Set_Option (void);

void Set_ClockSystem (u8 Choice);

void Minutes_AutoInc (void);
void Hours_AutoInc (void);

void Day_AutoInc (void);
void Month_AutoInc (void);
void Year_AutoInc (void);

void DayState_AutoInc (void);

void Set_CalenderMode(void);
void Set_ClockMode(void);

u8 Hours=1;
u8 Minutes;
u8 Seconds;

u8 Day=12;
u8 Month=6;
u8 Year=22;

u8 Option;
u8 Entery;
u8 Key;
u8 Mode;
u8 Choose;
u8 Chose;
u8 flag;

u8 DayCheck;
u8 DayStateCheck;
u8 DayState;

void main()
{

	/*KPD: Internal pull up for Rows and output for columns*/
	/*coulms*/
	DIO_vidSetPortDir(DIO_PORTA,0b00001111);
	DIO_vidSetPortVal(DIO_PORTA,0xff);
	
	/*rows*/
	DIO_vidSetPortDir(DIO_PORTB,0);
	DIO_vidSetPortVal(DIO_PORTB,0xff);

	/*LCD PORT Data and Control Directions */
	DIO_vidSetPortDir(LCD_DATA_PORT,0xFF); //PORT Data Direction
	DIO_vidSetPinDir(LCD_CONTROL_PORT,LCD_RS_PIN,DIO_OUTPUT); //PORT Control Direction For RS
	DIO_vidSetPinDir(LCD_CONTROL_PORT,LCD_E_PIN,DIO_OUTPUT); //PORT Control Direction For E

	/*LCD Init*/
	HLCD_voidInit();

	/*Timer*/
	TIMER0_voidInit();
	TIMER0_u8SetCallBack(&Clock);
	GIE_voidEnable();



	 while(1)
	{
		Key= KPD_u8GetPressedKey();
		NormalClock_ModeDisplay ();
		if (Key!=0xFF)
		{
			Set_Option ();
		}
		Set_CalenderMode();
		Set_ClockMode();


	}
}



void NormalClock_ModeDisplay (void)
{
	Minutes_AutoInc ();
	Hours_AutoInc ();
	DayState_AutoInc ();
	HLCD_voidSendCommand(LCD_CLEAR);
	HLCD_voidGotoxy(3,0);
	Hours_Display ();
	HLCD_voidSendChar(':');
	Minutes_Display ();
	HLCD_voidSendChar(':');
	Seconds_Display ();

	DayState_Display ();

	Day_AutoInc();
	Month_AutoInc();
	Year_AutoInc();
	HLCD_voidGotoxy(3,1);
	Day_Display ();
	HLCD_voidSendChar('/');
	Month_Display ();
	HLCD_voidSendChar('/');
	Year_Display ();
	_delay_ms(100);
}

void Set_ClockEnterDisplay (void)
{
	HLCD_voidSendCommand(LCD_CLEAR);
	HLCD_voidSendString("Clock  Set  Mode");
	HLCD_voidGotoxy(0,1);
	HLCD_voidSendString("   Activated");
	_delay_ms(1000);
}
void Set_CalendarEnterDisplay (void)
{
	HLCD_voidSendCommand(LCD_CLEAR);
	HLCD_voidSendString(" Date Set Mode");
	HLCD_voidGotoxy(0,1);
	HLCD_voidSendString("   Activated");
	_delay_ms(1000);
}
void Set_CalenderModeDisplay (void)
{
	Day_AutoInc();
	Month_AutoInc();
	Year_AutoInc();
	HLCD_voidSendCommand(LCD_CLEAR);
	HLCD_voidGotoxy(0,0);
	HLCD_voidSendString("Set Date:");
	HLCD_voidGotoxy(0,1);
	Day_Display ();
	HLCD_voidSendChar('/');
	Month_Display ();
	HLCD_voidSendChar('/');
	Year_Display ();
	_delay_ms(50);
}
void Set_ClockModeDisplay (void)
{
	HLCD_voidSendCommand(LCD_CLEAR);
	Minutes_AutoInc ();
	Hours_AutoInc ();
	Day_AutoInc();
	DayState_AutoInc ();

	HLCD_voidGotoxy(0,0);
	HLCD_voidSendString("Set Clock:");

	HLCD_voidGotoxy(0,1);
	Hours_Display ();
	HLCD_voidSendChar(':');
	Minutes_Display ();
	HLCD_voidSendChar(':');
	Seconds_Display ();
	DayState_Display();

	_delay_ms(50);
}


void DayState_Display (void)
{
	if (DayState == AM)
	{
		HLCD_voidSendString(" AM");
	}
	else if (DayState == PM)
	{
		HLCD_voidSendString(" PM");
	}
	else
	{
		//Do Nothing
	}
}

void Hours_Display (void)
{
	if (Hours == 0)
	{
		Hours =12;
	}
	if (Hours>=0 && Hours<=9)
	{
		LCD_Send_Num(0);
		LCD_Send_Num(Hours);
	}
	else
	{
		LCD_Send_Num(Hours);
	}
}

void Minutes_Display (void)
{
	if (Minutes>=0 && Minutes<=9)
		{
			LCD_Send_Num(0);
			LCD_Send_Num(Minutes);
		}
		else
		{
			LCD_Send_Num(Minutes);
		}
}

void Seconds_Display (void)
{
	if (Seconds>=0 && Seconds<=9)
		{
			LCD_Send_Num(0);
			LCD_Send_Num(Seconds);
		}
		else
		{
			LCD_Send_Num(Seconds);
		}
}

void Day_Display (void)
{
	if (Day>=0 && Day<=9)
		{
			LCD_Send_Num(0);
			LCD_Send_Num(Day);
		}
		else
		{
			LCD_Send_Num(Day);
		}
}

void Month_Display (void)
{
	if (Month>=0 && Month<=9)
		{
			LCD_Send_Num(0);
			LCD_Send_Num(Month);
		}
		else
		{
			LCD_Send_Num(Month);
		}
}

void Year_Display (void)
{
	LCD_Send_Num(2);
	LCD_Send_Num(0);

	if (Year>=0 && Year<=9)
		{
			LCD_Send_Num(0);
			LCD_Send_Num(Year);
		}
	else
		{
			LCD_Send_Num(Year);
		}
}

void DayState_AutoInc (void)
{
	if(Hours ==12 && Minutes == 0 && Seconds==0 && DayStateCheck==0 && DayState == AM)
	{
		DayState=PM;
		DayStateCheck=1;
			_delay_ms(2);
	}
	 if (Hours ==12 && Minutes == 0 && Seconds==0 && DayStateCheck==0 && DayState == PM)
	{
		DayState=AM;
		DayStateCheck=1;
		_delay_ms(2);
	}
}

void Day_AutoInc (void)
{

	if(Hours ==12 && Minutes == 0 && Seconds==0 && DayCheck==0 && DayState == AM)
	{
		Day+=1;
		DayCheck=1;
			_delay_ms(2);
	}
	else
	{
		//Do Nothing
	}

}
void Month_AutoInc (void)
{
	if((Day==32) && (Month == 1 || Month == 3 || Month ==5 || Month ==7 || Month ==8 || Month ==10|| Month == 12))
	{

		Day=1;
		Month+=1;
	}
	else if((Day==31 )&& (Month ==4  || Month == 6 || Month ==9 || Month ==11))
	{

		Day=1;
		Month+=1;
	}
	else if(Day==29 && Month ==2)
	{
		Month+=1;
		Day=1;
	}
	else
	{
		//Do Nothing
	}
}

void Year_AutoInc (void)
{
	if(Month>12 )
	{
		Year+=1;
		Month=1;
	}
	else
	{
		//Do Nothing
	}
}


void Minutes_AutoInc (void)
{
	if(Seconds>=60)
	{
		Seconds=0;
		Minutes+=1;
	}
	else
	{
		//Do Nothing
	}
}

void Hours_AutoInc (void)
{
	if(Minutes>=60)
	{
		Minutes=0;
		 Hours+=1;
	}

	if (Hours>12)
	{
		Hours=1;
	}
	else
	{
		//Do Nothing
	}
}





void Set_Option (void)
{
	switch(Key)
	{
	case '1':
				Option=SET_CLOCK;
				Entery=CHECKED ;
				break;

	case '+':	Option=SET_CALENDER;
				Entery=CHECKED ;
				break;

	case '2':
				if (Option==SET_CLOCK || Option==SET_CALENDER)
				{
					Mode = INCREMENT;
				}
				break;

	case '5':
				if (Option==SET_CLOCK || Option==SET_CALENDER)
				{
					Mode = DECREMENT;
				}
				break;

	case '7':
			Choose= OUT ;
			break;

	case '8':
			Chose= ENTER ;
			flag++;
			break;

	}
}
void Set_CalenderMode(void)
{
	while (Option==SET_CALENDER)
	{
		if (Entery==CHECKED)
		{
			Set_CalendarEnterDisplay ();
			Entery=0;
		}
		 Set_CalenderModeDisplay ();
		 Key= KPD_u8GetPressedKey();

		 if (Key!=0xFF)
		{
			Set_Option ();
		}

		 if (flag == 0)
		{
			 Set_ClockSystem (DAY);
		}
		if (flag == 2)
		{
			Set_ClockSystem (YRS);
		}
		if (flag == 1)
		{
			 Set_ClockSystem (MON);
		}
		if (Choose == OUT)
		{
			DayStateCheck=0;
			DayCheck=0;
			Choose=0;
			Chose=0;
			flag=0;
			HLCD_voidSendCommand(LCD_CLEAR);
			HLCD_voidSendString("    Date Set");
			HLCD_voidGotoxy(0,1);
			HLCD_voidSendString("  Successfully ");
			_delay_ms(1200);
			Option=NORMAL_MODE;
		}
	}
}
void Set_ClockMode(void)
{
	while (Option==SET_CLOCK)
			{
				if (Entery==CHECKED)
				{
					Set_ClockEnterDisplay ();
					Entery=0;
				}

				Set_ClockModeDisplay ();

				Key= KPD_u8GetPressedKey();

				if (Key!=0xFF)
				{
					Set_Option ();
				}

				if (flag ==0)
				{
					Set_ClockSystem (HRS);
				}
				if (flag == 2)
				{
					Set_ClockSystem (SECS);
				}
				if (flag == 1)
				{
					Set_ClockSystem (MINS);
				}
				if (flag == 3)
				{
					Set_ClockSystem (DAYSTATE);
				}

				if (Choose == OUT)
				{
					DayStateCheck=0;
					DayCheck=0;
					Choose=0;
					Chose=0;
					flag=0;
					HLCD_voidSendCommand(LCD_CLEAR);
					HLCD_voidSendString("   Clock  Set");
					HLCD_voidGotoxy(0,1);
					HLCD_voidSendString("  Successfully ");
					_delay_ms(1200);
					Option=NORMAL_MODE;
				}
}
}

void Set_ClockSystem (u8 Choice)
{
	if (Choice == HRS)
	{

		if (Mode==INCREMENT)
			{
				if(Hours>=0 && Hours<=12)
				{
					Hours++;
					Mode =0;
				}

			}
			if (Mode==DECREMENT)
			{
				if (Hours>=0 && Hours<=12)
				{
					Hours--;
					Mode =0;
				}
			}
	}

	if (Choice == MINS)
	{
		if (Mode==INCREMENT)
		{
			Minutes++;
			Mode =0;
		}
		if (Mode==DECREMENT)
		{
			if (Minutes ==0)
			{
				Minutes=59;
			}
			Minutes--;
			Mode =0;
		}
	}

	if (Choice == SECS)
	{
		if (Mode==INCREMENT)
		{
			Seconds++;
			Mode =0;
		}
		if (Mode==DECREMENT)
		{
			if (Seconds ==0)
			{
				Seconds=59;
			}
			Seconds--;
			Mode =0;
		}
	}

	if (Choice == DAY)
		{
			if (Mode==INCREMENT)
			{
				Day++;
				Mode =0;
			}
			if (Mode==DECREMENT)
			{
				Day--;
				Mode =0;
			}
		}

	if (Choice == MON)
		{
			if (Mode==INCREMENT)
			{
				Month++;
				Mode =0;
			}
			if (Mode==DECREMENT)
			{
				Month--;
				Mode =0;
			}
		}

	if (Choice == YRS)
		{
			if (Mode==INCREMENT)
			{
				Year++;
				Mode =0;
			}
			if (Mode==DECREMENT)
			{
				Year--;
				Mode =0;
			}
		}

	if (Choice == DAYSTATE)
		{
			if (Mode==INCREMENT)
			{
					TOGGLE_BIT(DayState,0);
					Mode =0;
			}
			if (Mode==DECREMENT)
			{
				TOGGLE_BIT(DayState,0);
				Mode =0;
			}
		}
}


void Clock (void)
{
	static u16 Local_u16Counter =0;
	if (Option==NORMAL_MODE)
	{
		Local_u16Counter++;

		if(Local_u16Counter==4000)
		{
			Local_u16Counter=0;
			Seconds=Seconds+1;
		}


	}
}

