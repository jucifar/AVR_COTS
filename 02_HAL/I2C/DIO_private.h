
/****************************************************************************
*****************************************************************************
*******************   SWC    :       DIO Driver         *********************
*******************    By    : Youssef Mostafa Mohamed  *********************
*******************   Date   :       27/8/2022          *********************
*******************  Version :          V1.0            *********************
*****************************************************************************
****************************************************************************/

#ifndef DIO_INT_H
#define DIO_INT_H

#define DDRA *((u8 *)0X3A)
#define PORTA *((u8 *)0X3B)
#define PINA *((volatile u8 *)0X39)
#define DDRB *((u8 *)0X37)
#define PORTB *((u8 *)0X38)
#define PINB *((volatile u8 *)0X36)
#define DDRC *((u8 *)0X34)
#define PORTC *((u8 *)0X35)
#define PINC *((volatile u8 *)0X33)
#define DDRD *((u8 *)0X31)
#define PORTD *((u8 *)0X32)
#define PIND *((volatile u8 *)0X30)

#endif