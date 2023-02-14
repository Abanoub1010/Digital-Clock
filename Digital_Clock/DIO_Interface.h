/*
 * DIO_Interface.h
 *
 *  Created on: Nov 18, 2022
 *      Author: Abanoub
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

/********************************************************************/
/**************************Public Functions**************************/
/********************************************************************/

/********************************************************************
 * Description: This function is used to set pin value to digital Low/High
 * Scope      : Public
 * Input      : u8
 *
 */
void DIO_vidSetPinVal(u8 PortId, u8 PinId, u8 val);

void DIO_vidSetPinDir(u8 PortId, u8 PinId, u8 dir);

void DIO_vidSetPortVal(u8 PortId, u8 val);

void DIO_vidSetPortDir(u8 PortId, u8 dir);

u8 DIO_u8GetPinVal(u8 PortId, u8 PinId);

/********************************************************************/
/************************** Public Macros  **************************/
/********************************************************************/

//Port definitions
#define		 DIO_PORTA 			0
#define		 DIO_PORTB 			1
#define 	 DIO_PORTC 			2
#define 	 DIO_PORTD 			3

//Pin definitions
#define 	DIO_PIN0 			0
#define	 	DIO_PIN1			1
#define 	DIO_PIN2			2
#define 	DIO_PIN3			3
#define 	DIO_PIN4			4
#define 	DIO_PIN5			5
#define 	DIO_PIN6			6
#define 	DIO_PIN7			7

//Digital values
#define 	DIO_HIGH 			1
#define 	DIO_LOW 			0
#define 	DIO_OUTPUT 			1
#define 	DIO_INPUT 			0

#define 	DIO_PORTOUTPUT 			0xff
#define 	DIO_PORTHIGH 			0xff

#endif /* DIO_INTERFACE_H_ */
