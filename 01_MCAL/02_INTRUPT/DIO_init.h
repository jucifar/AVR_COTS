
/****************************************************************************
 ****************************************************************************
 *******************   SWC    :       DIO Driver         ********************
 *******************    By    : Youssef Mostafa Mohamed  ********************
 *******************   Date   :       27/8/2022          ********************
 *******************  Version :          V1.0            ********************
 ****************************************************************************
 ***************************************************************************/

#ifndef DIO_PRIVATE_H
#define DIO_PRIVATE_H

typedef enum
{
  Port_A,
  Port_B,
  Port_C,
  Port_D
} et_Port;

typedef enum
{
  Pin_0,
  Pin_1,
  Pin_2,
  Pin_3,
  Pin_4,
  Pin_5,
  Pin_6,
  Pin_7
} et_Pin;

typedef enum
{
  Input,
  Output
} et_Direction;

typedef enum
{
  Low,
  High
} et_Status;

/* Setting PIN Direction */
void DIO_VoidSet_Pin_Direction(u8 copy_u8port, u8 copy_u8pin, u8 copy_u8direction);
/* Setting PIN Value */
void DIO_VoidSet_Pin_Value(u8 copy_u8port, u8 copy_u8pin, u8 copy_u8Value);
/* Getting PIN Value */
void DIO_VoidGet_Pin_Value(u8 copy_u8port, u8 copy_u8pin, u8 *copy_u8data);
/* Setting PORT Direction */
void DIO_VoidSet_Port_Direction(u8 copy_u8port, u8 copy_u8direction);
/*Setting port Direction with custom value*/
void DIO_VoidSet_Custom_Port_Direction(u8 copy_u8port, u8 copy_u8value);
/* Setting PORT ( PORT register ) Value */
void DIO_VoidSet_Port_Value(u8 copy_u8port, u8 copy_u8value);
/* Getting PORT ( PIN  register )  */
void DIO_VoidGet_Port_Value(u8 copy_u8port, u8 *copy_u8data);

#endif
