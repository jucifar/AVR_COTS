/****************************************************************************
 ****************************************************************************
 *******************   SWC    :       LCD Driver         ********************
 *******************    By    : Youssef Mostafa Mohamed  ********************
 *******************   Date   :       27/8/2022          ********************
 *******************  Version :          V1.0            ********************
 ****************************************************************************
 ***************************************************************************/
#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_init.h"
#include "DIO_private.h"
#include "LCD_init.h"
#include "LCD_private.h"
#include "LCD_config.h"
#include <util/delay.h>

void LCD_VidSendData(u8 copy_u8Data)
{
  DIO_VoidSet_Pin_Value(CONTROL_PORT, RS_PIN, High);
  DIO_VoidSet_Pin_Value(CONTROL_PORT, RW_PIN, Low);
  DIO_VoidSet_Port_Value(DATA_PORT, copy_u8Data);
  DIO_VoidSet_Pin_Value(CONTROL_PORT, ENABLE, High);
  _delay_ms(3);
  DIO_VoidSet_Pin_Value(CONTROL_PORT, ENABLE, Low);
}

void LCD_VidSendCommand(u8 copy_u8Data)
{
  DIO_VoidSet_Pin_Value(CONTROL_PORT, RS_PIN, Low);
  DIO_VoidSet_Pin_Value(CONTROL_PORT, RW_PIN, Low);
  DIO_VoidSet_Port_Value(DATA_PORT, copy_u8Data);
  DIO_VoidSet_Pin_Value(CONTROL_PORT, ENABLE, High);
  _delay_ms(3);
  DIO_VoidSet_Pin_Value(CONTROL_PORT, ENABLE, Low);
}

void LCD_VidInit()
{
  DIO_VoidSet_Port_Direction(DATA_PORT, Output);
  DIO_VoidSet_Pin_Direction(CONTROL_PORT, RS_PIN, Output);
  DIO_VoidSet_Pin_Direction(CONTROL_PORT, RW_PIN, Output);
  DIO_VoidSet_Pin_Direction(CONTROL_PORT, ENABLE, Output);
  _delay_ms(40);
  LCD_VidSendCommand(0b00111100);
  LCD_VidSendCommand(0b00001100);
  LCD_VidSendCommand(0b00000001);
}

void LCD_VidDisplayName(u8 *copy_u8name)
{
  while ((*copy_u8name) != '\0')
  {
    LCD_VidSendData(*(copy_u8name));
    copy_u8name++;
  }
}

void LCD_VidGoTo(u8 copy_u8X, u8 copy_u8Y)
{
#if LCD_TYPE == TWO_16
  if (copy_u8X == 1)
    copy_u8Y += 0x40;
#elif LCD_TYPE == FOUR_20
  if (copy_u8X == 1)
    copy_u8Y += 0x40;
  else if (copy_u8X == 2)
    copy_u8Y += 0x14;
  else if (copy_u8X == 3)
    copy_u8Y += 0x54;
#endif
  LCD_VidSendCommand(copy_u8Y + 0b10000000);
}

void LCD_VidClearDisplay(void)
{
  LCD_VidSendCommand(0x01);
}

void LCD_VidCreateSpecialChar(u8 *copy_u8pattern, u8 pattern_num)
{
  u8 local_pos = 8 * pattern_num;
  LCD_VidSendCommand(0b01000000 + local_pos);
  for (u8 i = 0; i < 8; i++)
    LCD_VidSendData(copy_u8pattern[i]);
  LCD_VidGoTo(0, 0);
}

void LCD_VidSendSpecialChar(u8 copy_u8pattern, u8 copy_u8X, u8 copy_u8Y)
{
  LCD_VidGoTo(copy_u8X, copy_u8Y);
  LCD_VidSendData(copy_u8pattern);
}

void LCD_VidSendInteger(u64 copy_u64integer)
{
  if (copy_u64integer != 0)
  {
    LCD_VidSendInteger(copy_u64integer / 10);
    LCD_VidSendData((copy_u64integer % 10) + '0');
  }
}

void LCD_VidSendDecimal(f64 copy_f64decimal)
{
  f64 copy_f128fraction = copy_f64decimal - ((u64)copy_f64decimal);
  copy_f128fraction = copy_f128fraction * 10;
  u64 copy_u64integer = (u64)copy_f128fraction;
  if (copy_u64integer != 0)
  {
    LCD_VidSendData(copy_u64integer + '0');
    LCD_VidSendDecimal(copy_f128fraction);
  }
}

void LCD_VidSendNumber(f64 copy_f64Number)
{
  if (copy_f64Number == 0)
    LCD_VidSendData('0');
  if (copy_f64Number < 0)
  {
    LCD_VidSendData('-');
    if ((u64)(-1 * copy_f64Number) == 0)
      LCD_VidSendData('0');
    LCD_VidSendInteger((u64)(-1 * copy_f64Number));
    if ((-1 * copy_f64Number) > (u64)(-1 * copy_f64Number))
    {
      LCD_VidSendData('.');
      LCD_VidSendDecimal(-1 * copy_f64Number);
    }
  }
  else if (copy_f64Number > 0)
  {
    if ((u64)copy_f64Number == 0)
      LCD_VidSendData('0');
    LCD_VidSendInteger((u64)copy_f64Number);
    if (copy_f64Number > (u64)copy_f64Number)
    {
      LCD_VidSendData('.');
      LCD_VidSendDecimal(copy_f64Number);
    }
  }
}
