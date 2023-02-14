

#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_


#define TCCR0  				*((volatile u8*)0x53)     			/*TIMER0 control register*/
#define TCCR0_WMG00 		6 									/*Waveform generation mode bit0*/
#define TCCR0_WMG01			3 									/*Waveform generation mode bit1*/
#define TCCR0_CS02			2									/*Prescular bit2*/
#define TCCR0_CS01			1									/*Prescular bit1*/
#define TCCR0_CS00			0									/*Prescular bit0*/




#define OCR0				*((volatile u8*)0x5C)				/*Output compare register0*/


#define TIMSK				*((volatile u8*)0x59)				/*Timer Mask*/
#define TIMSK_OCIE0			1									/*Output compare 0 interrupt enable*/













#endif