/*
 * KPD_Prog.c
 *
 *  Created on: Nov 26, 2022
 *      Author: Abanoub
 */
#include "LIB/STD_TYPES.h"
#include "DIO_Interface.h"
#include "KPD_Interface.h"
#include "KPD_Config.h"
#include "KPD_Priv.h"

#include <util/delay.h>
/*keypad matrix array*/
static const u8 KPD_au8Array[4][4]=
{
		{'1', '2', '3', '+'},
		{'4', '5', '6', '-'},
		{'7', '8', '9', '*'},
		{'/', '0', 'B', '='}
};

u8 KPD_u8GetPressedKey (void)
{

	u8 u8SwitchVal=NOT_PRESSED ;
	u8 u8Column;
	u8 u8Row;

	for(u8Column=0 ; u8Column<4 ; u8Column++)
	{
		DIO_vidSetPinVal(COLUMN_PORT,u8Column,DIO_LOW);

		for(u8Row=0 ; u8Row<4 ; u8Row++)
		{

			if ((DIO_u8GetPinVal(ROW_PORT,u8Row))==DIO_LOW)
			{
				u8SwitchVal = KPD_au8Array[(u8Row)][u8Column] ;
				while (DIO_u8GetPinVal(ROW_PORT,u8Row)==DIO_LOW);

				_delay_ms(10);
				return u8SwitchVal;
			}

		}

		DIO_vidSetPinVal(COLUMN_PORT,u8Column,DIO_HIGH);
	}
	return u8SwitchVal;

}
