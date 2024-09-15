/****************************************************************************
 ****************************************************************************
 *******************   SWC    :       GLCD Driver         ********************
 *******************    By    : Youssef Mostafa Mohamed  ********************
 *******************   Date   :       31/3/2023          ********************
 *******************  Version :          V2.0            ********************
 ****************************************************************************
 ***************************************************************************/

#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_private.h"
#include "DIO_init.h"
#include "GLCD_config.h"
#include "GLCD_private.h"
#include "GLCD_init.h"
#include <math.h>
#include <stdio.h>
#include <util/delay.h>

void GLCD_VidInit(GLCD_t *GLCD_INFO)
{
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[0].PORT, GLCD_INFO->GLCD_DATA_PINS[0].PIN, Output);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[1].PORT, GLCD_INFO->GLCD_DATA_PINS[1].PIN, Output);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[2].PORT, GLCD_INFO->GLCD_DATA_PINS[2].PIN, Output);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[3].PORT, GLCD_INFO->GLCD_DATA_PINS[3].PIN, Output);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[4].PORT, GLCD_INFO->GLCD_DATA_PINS[4].PIN, Output);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[5].PORT, GLCD_INFO->GLCD_DATA_PINS[5].PIN, Output);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[6].PORT, GLCD_INFO->GLCD_DATA_PINS[6].PIN, Output);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[7].PORT, GLCD_INFO->GLCD_DATA_PINS[7].PIN, Output);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_CONTROL_PINS[0].PORT, GLCD_INFO->GLCD_CONTROL_PINS[0].PIN, Output);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_CONTROL_PINS[1].PORT, GLCD_INFO->GLCD_CONTROL_PINS[1].PIN, Output);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_CONTROL_PINS[2].PORT, GLCD_INFO->GLCD_CONTROL_PINS[2].PIN, Output);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_CONTROL_PINS[3].PORT, GLCD_INFO->GLCD_CONTROL_PINS[3].PIN, Output);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_CONTROL_PINS[4].PORT, GLCD_INFO->GLCD_CONTROL_PINS[4].PIN, Output);
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[5].PORT, GLCD_INFO->GLCD_CONTROL_PINS[5].PIN, Low);
  _delay_ms(1);
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[5].PORT, GLCD_INFO->GLCD_CONTROL_PINS[5].PIN, High);
  _delay_ms(1);
  GLCD_VidSendCommand(GLCD_DISPLAY_OFF_COMMAND, GLCD_INFO);
  GLCD_VidSendCommand(0x3F, GLCD_INFO);
  GLCD_VidSendCommand(GLCD_DISPLAY_ON_COMMAND, GLCD_INFO);
  GLCD_VidClearDisplay(GLCD_INFO);
}

void GLCD_VidSendCommand(u8 copy_u8Command, GLCD_t *GLCD_INFO)
{
  /*Clear Register Select pin to send command*/
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[0].PORT, GLCD_INFO->GLCD_CONTROL_PINS[0].PIN, Low);
  /*Clear Read\Write pin to Write Command */
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[1].PORT, GLCD_INFO->GLCD_CONTROL_PINS[1].PIN, Low);
  /*Send Command*/
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[2].PORT, GLCD_INFO->GLCD_CONTROL_PINS[2].PIN, High);
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[0].PORT, GLCD_INFO->GLCD_DATA_PINS[0].PIN, ((copy_u8Command >> Bit_0) & 1));
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[1].PORT, GLCD_INFO->GLCD_DATA_PINS[1].PIN, ((copy_u8Command >> Bit_1) & 1));
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[2].PORT, GLCD_INFO->GLCD_DATA_PINS[2].PIN, ((copy_u8Command >> Bit_2) & 1));
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[3].PORT, GLCD_INFO->GLCD_DATA_PINS[3].PIN, ((copy_u8Command >> Bit_3) & 1));
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[4].PORT, GLCD_INFO->GLCD_DATA_PINS[4].PIN, ((copy_u8Command >> Bit_4) & 1));
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[5].PORT, GLCD_INFO->GLCD_DATA_PINS[5].PIN, ((copy_u8Command >> Bit_5) & 1));
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[6].PORT, GLCD_INFO->GLCD_DATA_PINS[6].PIN, ((copy_u8Command >> Bit_6) & 1));
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[7].PORT, GLCD_INFO->GLCD_DATA_PINS[7].PIN, ((copy_u8Command >> Bit_7) & 1));
  /*Set Enable  pin to read Command*/
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[2].PORT, GLCD_INFO->GLCD_CONTROL_PINS[2].PIN, Low);
}
void GLCD_VidSendByte(u8 copy_u8Data, u8 copy_u8y, GLCD_t *GLCD_INFO)
{
  if (copy_u8y <= 63)
  {
    DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[4].PORT, GLCD_INFO->GLCD_CONTROL_PINS[4].PIN, Low);
    DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[3].PORT, GLCD_INFO->GLCD_CONTROL_PINS[3].PIN, High);
    GLCD_VidGoToY(copy_u8y, GLCD_INFO);
  }
  else
  {
    DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[4].PORT, GLCD_INFO->GLCD_CONTROL_PINS[4].PIN, High);
    DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[3].PORT, GLCD_INFO->GLCD_CONTROL_PINS[3].PIN, Low);
    GLCD_VidGoToY(copy_u8y - GLCD_M2_OFFSET, GLCD_INFO);
  }
  GLCD_VidSendData(copy_u8Data, GLCD_INFO);
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[4].PORT, GLCD_INFO->GLCD_CONTROL_PINS[4].PIN, Low);
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[3].PORT, GLCD_INFO->GLCD_CONTROL_PINS[3].PIN, Low);
}
void GLCD_VidSendData(u8 copy_u8Data, GLCD_t *GLCD_INFO)

{

  /*Set Register Select pin to send Data*/
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[0].PORT, GLCD_INFO->GLCD_CONTROL_PINS[0].PIN, High);
  /*Clear Read\Write pin to Write Data */
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[1].PORT, GLCD_INFO->GLCD_CONTROL_PINS[1].PIN, Low);
  /*Send Data*/
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[2].PORT, GLCD_INFO->GLCD_CONTROL_PINS[2].PIN, High);
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[0].PORT, GLCD_INFO->GLCD_DATA_PINS[0].PIN, ((copy_u8Data >> Bit_0) & 1));
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[1].PORT, GLCD_INFO->GLCD_DATA_PINS[1].PIN, ((copy_u8Data >> Bit_1) & 1));
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[2].PORT, GLCD_INFO->GLCD_DATA_PINS[2].PIN, ((copy_u8Data >> Bit_2) & 1));
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[3].PORT, GLCD_INFO->GLCD_DATA_PINS[3].PIN, ((copy_u8Data >> Bit_3) & 1));
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[4].PORT, GLCD_INFO->GLCD_DATA_PINS[4].PIN, ((copy_u8Data >> Bit_4) & 1));
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[5].PORT, GLCD_INFO->GLCD_DATA_PINS[5].PIN, ((copy_u8Data >> Bit_5) & 1));
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[6].PORT, GLCD_INFO->GLCD_DATA_PINS[6].PIN, ((copy_u8Data >> Bit_6) & 1));
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[7].PORT, GLCD_INFO->GLCD_DATA_PINS[7].PIN, ((copy_u8Data >> Bit_7) & 1));
  /*Set Enable  pin to read Data*/
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[2].PORT, GLCD_INFO->GLCD_CONTROL_PINS[2].PIN, Low);
}

/* Go To Z Function */
void GLCD_VidGoToZ(u8 Copy_u8Z, GLCD_t *GLCD_INFO)
{
  if (Copy_u8Z >= 64)
    return;
  GLCD_VidSendCommand(GLCD_SET_Z_ADDRESS + Copy_u8Z, GLCD_INFO);
}

/* Go To Y Function */
void GLCD_VidGoToY(u8 Copy_u8Y, GLCD_t *GLCD_INFO)
{
  if (Copy_u8Y >= 64)
    return;
  GLCD_VidSendCommand(GLCD_SET_Y_ADDRESS + Copy_u8Y, GLCD_INFO);
}

/* Go To Page Function */
void GLCD_VidGoToPage(u8 Copy_u8Page, GLCD_t *GLCD_INFO)
{
  if (Copy_u8Page >= 8)
    return;
  GLCD_VidSendCommand(GLCD_SET_X_ADDRESS + Copy_u8Page, GLCD_INFO);
}

/*Go To Page & Y*/
void GLCD_VidGoToPY(u8 Copy_u8Page, u8 copy_u8y, GLCD_t *GLCD_INFO)
{

  if (Copy_u8Page >= 8 || copy_u8y >= 64)
    return;
  GLCD_VidSendCommand(GLCD_SET_X_ADDRESS + Copy_u8Page, GLCD_INFO);
  GLCD_VidSendCommand(GLCD_SET_Y_ADDRESS + copy_u8y, GLCD_INFO);
}

/*Go To X & Y*/
void GLCD_VidGoToPixel(u8 Copy_u8Pixel, u8 copy_u8y, GLCD_t *GLCD_INFO)
{
  if (Copy_u8Pixel >= 64 || copy_u8y >= 64)
    return;
  GLCD_VidSendCommand(GLCD_SET_Z_ADDRESS + Copy_u8Pixel, GLCD_INFO);
  GLCD_VidSendCommand(GLCD_SET_Y_ADDRESS + copy_u8y, GLCD_INFO);
}

void GLCD_VidClearDisplay(GLCD_t *GLCD_INFO)
{
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[4].PORT, GLCD_INFO->GLCD_CONTROL_PINS[4].PIN, Low);
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[3].PORT, GLCD_INFO->GLCD_CONTROL_PINS[3].PIN, Low);
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 64; j++)
    {
      GLCD_VidGoToPY(i, j, GLCD_INFO);
      GLCD_VidSendData(0, GLCD_INFO);
    }
  }
  GLCD_VidGoToPY(GLCD_START_PAGE, GLCD_START_Y, GLCD_INFO);
}

/* Send Char Function */
void GLCD_VidSendChar(u8 Copy_u8Char, u8 Copy_u8UnderlineStatus, u8 copy_u8y, GLCD_t *GLCD_INFO)
{
  u8 Index = Copy_u8Char - 32;
  for (int i = 0; i < 7; i++)
  {
    if (copy_u8y + i <= 63)
    {
      DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[4].PORT, GLCD_INFO->GLCD_CONTROL_PINS[4].PIN, Low);
      DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[3].PORT, GLCD_INFO->GLCD_CONTROL_PINS[3].PIN, High);
      GLCD_VidGoToY(copy_u8y + i, GLCD_INFO);
    }
    else
    {
      DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[4].PORT, GLCD_INFO->GLCD_CONTROL_PINS[4].PIN, High);
      DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[3].PORT, GLCD_INFO->GLCD_CONTROL_PINS[3].PIN, Low);
      GLCD_VidGoToY(copy_u8y + i - GLCD_M2_OFFSET, GLCD_INFO);
    }
    GLCD_VidSendData(Font7x7[(Index * GLCD_FONT_WIDTH) + i] | ((Copy_u8UnderlineStatus == 'e' || Copy_u8UnderlineStatus == 'E') ? 0b10000000 : 0b00000000), GLCD_INFO);
  }
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[3].PORT, GLCD_INFO->GLCD_CONTROL_PINS[3].PIN, Low);
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[4].PORT, GLCD_INFO->GLCD_CONTROL_PINS[4].PIN, Low);
}

void GLCD_VidDisplayText_Pixel(u8 Copy_u8Pixel, u8 copy_u8y, const u8 *copy_u8name, u8 Copy_u8UnderlineStatus, GLCD_t *GLCD_INFO)
{
  GLCD_VidGoToPixel(Copy_u8Pixel, copy_u8y, GLCD_INFO);
  u8 Index = 0;
  while ((*copy_u8name) != '\0')
  {
    GLCD_VidSendChar(*(copy_u8name), Copy_u8UnderlineStatus, copy_u8y + (Index * GLCD_FONT_SIZE), GLCD_INFO);
    copy_u8name++;
    Index++;
  }
}

void GLCD_VidDisplayText_Page(u8 Copy_u8Page, u8 copy_u8y, const u8 *copy_u8name, u8 Copy_u8UnderlineStatus, GLCD_t *GLCD_INFO)
{
  GLCD_VidGoToPY(Copy_u8Page, copy_u8y, GLCD_INFO);
  u8 Index = 0;
  while ((*copy_u8name) != '\0')
  {
    GLCD_VidSendChar(*(copy_u8name), Copy_u8UnderlineStatus, copy_u8y + (Index * GLCD_FONT_SIZE), GLCD_INFO);
    copy_u8name++;
    Index++;
  }
}

void GLCD_VidDisplayStraitLine(u8 Copy_u8x, GLCD_t *GLCD_INFO)
{
  GLCD_VidGoToPY(Copy_u8x, 0, GLCD_INFO);
  for (int i = 0; i < 20; i++)
    GLCD_VidSendChar('_', 'd', (i * 7), GLCD_INFO);
}

void GLCD_VidDisplayHorizontalLine(u8 Copy_u8y, GLCD_t *GLCD_INFO)
{
  for (int i = 1; i < 8; i++)
  {
    GLCD_VidGoToPY(i, Copy_u8y, GLCD_INFO);
    GLCD_VidSendChar('|', 'd', i * 7, GLCD_INFO);
  }
}

void GLCD_VidDisplaySinWave(u8 Copy_u8x, u8 copy_u8y, GLCD_t *GLCD_INFO)
{
  GLCD_VidGoToPY(4, 0, GLCD_INFO);

  for (u8 i = 8; i > 0; i--)
  {
    GLCD_VidSendData(1 << (i - 1) | 0b10000000, GLCD_INFO);
  }
  for (u8 i = 0; i < 8; i++)
  {
    GLCD_VidSendData(1 << i | 0b10000000, GLCD_INFO);
  }

  GLCD_VidGoToPY(4, 16, GLCD_INFO);
  for (u8 i = 8; i > 0; i--)
  {
    GLCD_VidSendData(0b10000000, GLCD_INFO);
  }
  for (u8 i = 0; i < 8; i++)
  {
    GLCD_VidSendData(0b10000000, GLCD_INFO);
  }

  GLCD_VidGoToPY(4, 48, GLCD_INFO);
  for (u8 i = 8; i > 0; i--)
  {
    GLCD_VidSendData(0b10000000, GLCD_INFO);
  }
  for (u8 i = 0; i < 8; i++)
  {
    GLCD_VidSendData(0b10000000, GLCD_INFO);
  }

  GLCD_VidGoToPY(5, 16, GLCD_INFO);
  for (u8 i = 0; i < 8; i++)
  {
    GLCD_VidSendData(1 << i, GLCD_INFO);
  }
  for (u8 i = 8; i > 0; i--)
  {
    GLCD_VidSendData(1 << (i - 1), GLCD_INFO);
  }

  GLCD_VidGoToPY(4, 32, GLCD_INFO);
  for (u8 i = 8; i > 0; i--)
  {
    GLCD_VidSendData(1 << (i - 1) | 0b10000000, GLCD_INFO);
  }
  for (u8 i = 0; i < 8; i++)
  {
    GLCD_VidSendData(1 << i | 0b10000000, GLCD_INFO);
  }

  GLCD_VidGoToPY(5, 48, GLCD_INFO);
  for (u8 i = 0; i < 8; i++)
  {
    GLCD_VidSendData(1 << i, GLCD_INFO);
  }
  for (u8 i = 8; i > 0; i--)
  {
    GLCD_VidSendData(1 << (i - 1), GLCD_INFO);
  }
}

u8 GLCD_u8GetPage(u8 Copy_u8Page, u8 copy_u8y, GLCD_t *GLCD_INFO)
{

  if (copy_u8y >= 128 || Copy_u8Page >= 8)
    return;
  if (copy_u8y <= 63)
  {
    DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[4].PORT, GLCD_INFO->GLCD_CONTROL_PINS[4].PIN, Low);
    DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[3].PORT, GLCD_INFO->GLCD_CONTROL_PINS[3].PIN, High);
    GLCD_VidGoToPY(Copy_u8Page, copy_u8y, GLCD_INFO);
  }
  else
  {
    DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[4].PORT, GLCD_INFO->GLCD_CONTROL_PINS[4].PIN, High);
    DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[3].PORT, GLCD_INFO->GLCD_CONTROL_PINS[3].PIN, Low);
    GLCD_VidGoToPY(Copy_u8Page, copy_u8y - GLCD_M2_OFFSET, GLCD_INFO);
  }

  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[0].PORT, GLCD_INFO->GLCD_DATA_PINS[0].PIN, Input);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[1].PORT, GLCD_INFO->GLCD_DATA_PINS[1].PIN, Input);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[2].PORT, GLCD_INFO->GLCD_DATA_PINS[2].PIN, Input);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[3].PORT, GLCD_INFO->GLCD_DATA_PINS[3].PIN, Input);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[4].PORT, GLCD_INFO->GLCD_DATA_PINS[4].PIN, Input);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[5].PORT, GLCD_INFO->GLCD_DATA_PINS[5].PIN, Input);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[6].PORT, GLCD_INFO->GLCD_DATA_PINS[6].PIN, Input);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[7].PORT, GLCD_INFO->GLCD_DATA_PINS[7].PIN, Input);
  /*Set Register Select pin to send Data*/
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[0].PORT, GLCD_INFO->GLCD_CONTROL_PINS[0].PIN, High);
  /*SET Read\Write pin to Write Data */
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[1].PORT, GLCD_INFO->GLCD_CONTROL_PINS[1].PIN, High);
  /*Set Register Select pin to send Data*/
  /*Read Data*/
  u8 Data = 0;
  u8 pin = 0;

  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[2].PORT, GLCD_INFO->GLCD_CONTROL_PINS[2].PIN, High);
  _delay_ms(2);
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[2].PORT, GLCD_INFO->GLCD_CONTROL_PINS[2].PIN, Low);

  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[2].PORT, GLCD_INFO->GLCD_CONTROL_PINS[2].PIN, High);
  _delay_ms(2);
  DIO_VoidGet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[0].PORT, GLCD_INFO->GLCD_DATA_PINS[0].PIN, &pin);
  Data |= (pin << 0);
  DIO_VoidGet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[1].PORT, GLCD_INFO->GLCD_DATA_PINS[1].PIN, &pin);
  Data |= (pin << 1);
  DIO_VoidGet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[2].PORT, GLCD_INFO->GLCD_DATA_PINS[2].PIN, &pin);
  Data |= (pin << 2);
  DIO_VoidGet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[3].PORT, GLCD_INFO->GLCD_DATA_PINS[3].PIN, &pin);
  Data |= (pin << 3);
  DIO_VoidGet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[4].PORT, GLCD_INFO->GLCD_DATA_PINS[4].PIN, &pin);
  Data |= (pin << 4);
  DIO_VoidGet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[5].PORT, GLCD_INFO->GLCD_DATA_PINS[5].PIN, &pin);
  Data |= (pin << 5);
  DIO_VoidGet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[6].PORT, GLCD_INFO->GLCD_DATA_PINS[6].PIN, &pin);
  Data |= (pin << 6);
  DIO_VoidGet_Pin_Value(GLCD_INFO->GLCD_DATA_PINS[7].PORT, GLCD_INFO->GLCD_DATA_PINS[7].PIN, &pin);
  Data |= (pin << 7);
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[2].PORT, GLCD_INFO->GLCD_CONTROL_PINS[2].PIN, Low);

  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[0].PORT, GLCD_INFO->GLCD_DATA_PINS[0].PIN, Output);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[1].PORT, GLCD_INFO->GLCD_DATA_PINS[1].PIN, Output);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[2].PORT, GLCD_INFO->GLCD_DATA_PINS[2].PIN, Output);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[3].PORT, GLCD_INFO->GLCD_DATA_PINS[3].PIN, Output);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[4].PORT, GLCD_INFO->GLCD_DATA_PINS[4].PIN, Output);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[5].PORT, GLCD_INFO->GLCD_DATA_PINS[5].PIN, Output);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[6].PORT, GLCD_INFO->GLCD_DATA_PINS[6].PIN, Output);
  DIO_VoidSet_Pin_Direction(GLCD_INFO->GLCD_DATA_PINS[7].PORT, GLCD_INFO->GLCD_DATA_PINS[7].PIN, Output);
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[4].PORT, GLCD_INFO->GLCD_CONTROL_PINS[4].PIN, Low);
  DIO_VoidSet_Pin_Value(GLCD_INFO->GLCD_CONTROL_PINS[3].PORT, GLCD_INFO->GLCD_CONTROL_PINS[3].PIN, Low);
  return Data;
}

void GLCD_VidSendInteger(u64 copy_u64integer, u8 Copy_u8UnderlineStatus, u8 copy_u8y, GLCD_t *GLCD_INFO)
{
  if (copy_u64integer != 0)
  {
    GLCD_VidSendInteger(copy_u64integer / 10, Copy_u8UnderlineStatus, copy_u8y, GLCD_INFO);
    GLCD_VidSendChar((copy_u64integer % 10) + '0', Copy_u8UnderlineStatus, copy_u8y, GLCD_INFO);
  }
}

/*
void GLCD_VidSendDecimal(f64 copy_f64decimal, GLCD_t *GLCD_INFO)
{

  f64 copy_f128fraction = copy_f64decimal - ((u64)copy_f64decimal);
  copy_f128fraction = copy_f128fraction * 10;
  u64 copy_u64integer = (u64)copy_f128fraction;
  if (copy_u64integer != 0)
  {
    GLCD_VidSendChar(copy_u64integer + '0', GLCD_INFO);
    GLCD_VidSendDecimal(copy_f128fraction, GLCD_INFO);
  }
}

void GLCD_VidSendNumber(f64 copy_f64Number, GLCD_t *GLCD_INFO)
{

  if (copy_f64Number == 0)
    GLCD_VidSendChar('0', GLCD_INFO);
  if (copy_f64Number < 0)
  {
    GLCD_VidSendChar('-', GLCD_INFO);
    if ((u64)(-1 * copy_f64Number) == 0)
      GLCD_VidSendChar('0', GLCD_INFO);
    GLCD_VidSendInteger((u64)(-1 * copy_f64Number), GLCD_INFO);
    if ((-1 * copy_f64Number) > (u64)(-1 * copy_f64Number))
    {
      GLCD_VidSendChar('.', GLCD_INFO);
      GLCD_VidSendDecimal(-1 * copy_f64Number, GLCD_INFO);
    }
  }
  else if (copy_f64Number > 0)
  {
    if ((u64)copy_f64Number == 0)
      GLCD_VidSendChar('0', GLCD_INFO);
    GLCD_VidSendInteger((u64)copy_f64Number, GLCD_INFO);
    if (copy_f64Number > (u64)copy_f64Number)
    {
      GLCD_VidSendChar('.', GLCD_INFO);
      GLCD_VidSendDecimal(copy_f64Number, GLCD_INFO);
    }
  }
}
*/