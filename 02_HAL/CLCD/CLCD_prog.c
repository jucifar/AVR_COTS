/****************************************************************************
 ****************************************************************************
 *******************   SWC    :       CLCD Driver         ********************
 *******************    By    : Youssef Mostafa Mohamed  ********************
 *******************   Date   :       31/3/2023          ********************
 *******************  Version :          V2.0            ********************
 ****************************************************************************
 ***************************************************************************/
#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_private.h"
#include "DIO_init.h"
#include "CLCD_private.h"
#include "CLCD_config.h"
#include "CLCD_init.h"
#include <util/delay.h>

void CLCD_VidSendCommand(u8 copy_u8Command, CLCD_t *CLCD_INFO)
{

  /*Clear Register Select pin to send command*/
  DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_CONTROL_PINS[0].PORT, CLCD_INFO->CLCD_CONTROL_PINS[0].PIN, Low);
  /*Clear Read\Write pin to Write Command */
  DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_CONTROL_PINS[1].PORT, CLCD_INFO->CLCD_CONTROL_PINS[1].PIN, Low);
  /*Send Command*/
  if (CLCD_INFO->CLCD_MODE == CLCD_8_BIT_MODE)
  {
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[0].PORT, CLCD_INFO->CLCD_DATA_PINS[0].PIN, ((copy_u8Command >> Bit_0) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[1].PORT, CLCD_INFO->CLCD_DATA_PINS[1].PIN, ((copy_u8Command >> Bit_1) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[2].PORT, CLCD_INFO->CLCD_DATA_PINS[2].PIN, ((copy_u8Command >> Bit_2) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[3].PORT, CLCD_INFO->CLCD_DATA_PINS[3].PIN, ((copy_u8Command >> Bit_3) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[4].PORT, CLCD_INFO->CLCD_DATA_PINS[4].PIN, ((copy_u8Command >> Bit_4) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[5].PORT, CLCD_INFO->CLCD_DATA_PINS[5].PIN, ((copy_u8Command >> Bit_5) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[6].PORT, CLCD_INFO->CLCD_DATA_PINS[6].PIN, ((copy_u8Command >> Bit_6) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[7].PORT, CLCD_INFO->CLCD_DATA_PINS[7].PIN, ((copy_u8Command >> Bit_7) & 1));
    /*Set Enable  pin to read Command*/
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_CONTROL_PINS[2].PORT, CLCD_INFO->CLCD_CONTROL_PINS[2].PIN, High);
    _delay_ms(2);
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_CONTROL_PINS[2].PORT, CLCD_INFO->CLCD_CONTROL_PINS[2].PIN, Low);
  }
  else if (CLCD_INFO->CLCD_MODE == CLCD_4_BIT_MODE)
  {
    /*Send Last 4bit of Command*/
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[7].PORT, CLCD_INFO->CLCD_DATA_PINS[7].PIN, ((copy_u8Command >> Bit_7) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[6].PORT, CLCD_INFO->CLCD_DATA_PINS[6].PIN, ((copy_u8Command >> Bit_6) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[5].PORT, CLCD_INFO->CLCD_DATA_PINS[5].PIN, ((copy_u8Command >> Bit_5) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[4].PORT, CLCD_INFO->CLCD_DATA_PINS[4].PIN, ((copy_u8Command >> Bit_4) & 1));

    /*Set Enable  pin to read Data*/
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_CONTROL_PINS[2].PORT, CLCD_INFO->CLCD_CONTROL_PINS[2].PIN, High);
    _delay_ms(2);
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_CONTROL_PINS[2].PORT, CLCD_INFO->CLCD_CONTROL_PINS[2].PIN, Low);

    /*Send First 4bit of Command*/
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[7].PORT, CLCD_INFO->CLCD_DATA_PINS[7].PIN, ((copy_u8Command >> Bit_3) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[6].PORT, CLCD_INFO->CLCD_DATA_PINS[6].PIN, ((copy_u8Command >> Bit_2) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[5].PORT, CLCD_INFO->CLCD_DATA_PINS[5].PIN, ((copy_u8Command >> Bit_1) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[4].PORT, CLCD_INFO->CLCD_DATA_PINS[4].PIN, ((copy_u8Command >> Bit_0) & 1));

    /*Set Enable  pin to read Data*/
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_CONTROL_PINS[2].PORT, CLCD_INFO->CLCD_CONTROL_PINS[2].PIN, High);
    _delay_ms(2);
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_CONTROL_PINS[2].PORT, CLCD_INFO->CLCD_CONTROL_PINS[2].PIN, Low);
  }
}

void CLCD_VidSendData(u8 copy_u8Data, CLCD_t *CLCD_INFO)
{
  /*Set Register Select pin to send Data*/
  DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_CONTROL_PINS[0].PORT, CLCD_INFO->CLCD_CONTROL_PINS[0].PIN, High);
  /*Clear Read\Write pin to Write Data */
  DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_CONTROL_PINS[1].PORT, CLCD_INFO->CLCD_CONTROL_PINS[1].PIN, Low);
  /*Send Data*/

  if (CLCD_INFO->CLCD_MODE == CLCD_8_BIT_MODE)
  {
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[0].PORT, CLCD_INFO->CLCD_DATA_PINS[0].PIN, ((copy_u8Data >> Bit_0) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[1].PORT, CLCD_INFO->CLCD_DATA_PINS[1].PIN, ((copy_u8Data >> Bit_1) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[2].PORT, CLCD_INFO->CLCD_DATA_PINS[2].PIN, ((copy_u8Data >> Bit_2) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[3].PORT, CLCD_INFO->CLCD_DATA_PINS[3].PIN, ((copy_u8Data >> Bit_3) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[4].PORT, CLCD_INFO->CLCD_DATA_PINS[4].PIN, ((copy_u8Data >> Bit_4) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[5].PORT, CLCD_INFO->CLCD_DATA_PINS[5].PIN, ((copy_u8Data >> Bit_5) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[6].PORT, CLCD_INFO->CLCD_DATA_PINS[6].PIN, ((copy_u8Data >> Bit_6) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[7].PORT, CLCD_INFO->CLCD_DATA_PINS[7].PIN, ((copy_u8Data >> Bit_7) & 1));
    /*Set Enable  pin to read Data*/
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_CONTROL_PINS[2].PORT, CLCD_INFO->CLCD_CONTROL_PINS[2].PIN, High);
    _delay_ms(2);
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_CONTROL_PINS[2].PORT, CLCD_INFO->CLCD_CONTROL_PINS[2].PIN, Low);
  }
  else if (CLCD_INFO->CLCD_MODE == CLCD_4_BIT_MODE)
  {
    /*Send Data Last 4 BIT of Data*/
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[7].PORT, CLCD_INFO->CLCD_DATA_PINS[7].PIN, ((copy_u8Data >> Bit_7) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[6].PORT, CLCD_INFO->CLCD_DATA_PINS[6].PIN, ((copy_u8Data >> Bit_6) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[5].PORT, CLCD_INFO->CLCD_DATA_PINS[5].PIN, ((copy_u8Data >> Bit_5) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[4].PORT, CLCD_INFO->CLCD_DATA_PINS[4].PIN, ((copy_u8Data >> Bit_4) & 1));

    /*Set Enable  pin to read Data*/
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_CONTROL_PINS[2].PORT, CLCD_INFO->CLCD_CONTROL_PINS[2].PIN, High);
    _delay_ms(2);
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_CONTROL_PINS[2].PORT, CLCD_INFO->CLCD_CONTROL_PINS[2].PIN, Low);

    /*Send Data first 4 BIT of Data*/
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[7].PORT, CLCD_INFO->CLCD_DATA_PINS[7].PIN, ((copy_u8Data >> Bit_3) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[6].PORT, CLCD_INFO->CLCD_DATA_PINS[6].PIN, ((copy_u8Data >> Bit_2) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[5].PORT, CLCD_INFO->CLCD_DATA_PINS[5].PIN, ((copy_u8Data >> Bit_1) & 1));
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[4].PORT, CLCD_INFO->CLCD_DATA_PINS[4].PIN, ((copy_u8Data >> Bit_0) & 1));

    /*Set Enable  pin to read Data*/
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_CONTROL_PINS[2].PORT, CLCD_INFO->CLCD_CONTROL_PINS[2].PIN, High);
    _delay_ms(2);
    DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_CONTROL_PINS[2].PORT, CLCD_INFO->CLCD_CONTROL_PINS[2].PIN, Low);
  }
}

void CLCD_VidInit(CLCD_t *CLCD_INFO)
{
  DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[4].PORT, CLCD_INFO->CLCD_DATA_PINS[4].PIN, Output);
  DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[5].PORT, CLCD_INFO->CLCD_DATA_PINS[5].PIN, Output);
  DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[6].PORT, CLCD_INFO->CLCD_DATA_PINS[6].PIN, Output);
  DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[7].PORT, CLCD_INFO->CLCD_DATA_PINS[7].PIN, Output);
  DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_CONTROL_PINS[0].PORT, CLCD_INFO->CLCD_CONTROL_PINS[0].PIN, Output);
  DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_CONTROL_PINS[1].PORT, CLCD_INFO->CLCD_CONTROL_PINS[1].PIN, Output);
  DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_CONTROL_PINS[2].PORT, CLCD_INFO->CLCD_CONTROL_PINS[2].PIN, Output);
  _delay_ms(31);
  u8 Function_Set = FUNCTION_SET_INIT;
  if (CLCD_INFO->CLCD_MODE == CLCD_8_BIT_MODE)
  {
    /*Set 8_BIT Mode*/
    SET_BIT(Function_Set, CLCD_SEND_MODE_BIT);
    DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[0].PORT, CLCD_INFO->CLCD_DATA_PINS[0].PIN, Output);
    DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[1].PORT, CLCD_INFO->CLCD_DATA_PINS[1].PIN, Output);
    DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[2].PORT, CLCD_INFO->CLCD_DATA_PINS[2].PIN, Output);
    DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[3].PORT, CLCD_INFO->CLCD_DATA_PINS[3].PIN, Output);
  }
  else if (CLCD_INFO->CLCD_MODE == CLCD_4_BIT_MODE)
  {
    /*Set 4_BIT Mode*/
    CLEAR_BIT(Function_Set, CLCD_SEND_MODE_BIT);
  }
/*Set Number Of Lines*/
#if CLCD_LINE_MODE == CLCD_2_LINE_MODE
  SET_BIT(Function_Set, CLCD_NUMBER_OF_LINES_BIT);
#elif CLCD_LINE_MODE == CLCD_1_LINE_MODE
  CLEAR_BIT(Function_Set, CLCD_NUMBER_OF_LINES_BIT);
#endif

/*Set Font Size*/
#if CLCD_FONT_SIZE == CLCD_FONT_5_11
  SET_BIT(Function_Set, CLCD_FONT_BIT);
#elif CLCD_FONT_SIZE == CLCD_FONT_5_8
  CLEAR_BIT(Function_Set, CLCD_FONT_BIT);
#endif

  u8 Display_on_off_Control = DISPLAY_ON_OFF_CONTROL_INIT;

/*Set display Status */
#if CLCD_DISPLAY_STATUS == CLCD_ENABLE_DISPLAY
  SET_BIT(Display_on_off_Control, CLCD_DISPLAY_STATUS_BIT);
#elif CLCD_DISPLAY_STATUS == CLCD_DISABLE_DISPLAY
  CLEAR_BIT(Display_on_off_Control, CLCD_DISPLAY_STATUS_BIT);
#endif

/*Set Cursor status*/
#if CLCD_CURSOR_STATUS == CLCD_ENABLE_CURSOR
  SET_BIT(Display_on_off_Control, CLCD_CURSOR_STATUS_BIT);
#elif CLCD_CURSOR_STATUS == CLCD_DISABLE_CURSOR
  CLEAR_BIT(Display_on_off_Control, CLCD_CURSOR_STATUS_BIT);
#endif

/*Set Cursor Blink status*/
#if CLCD_CURSOR_PLINK_STATUS == CLCD_ENABLE_CURSOR_PLINK
  SET_BIT(Display_on_off_Control, CLCD_CURSOR_BLINK_STATUS_BIT);
#elif CLCD_CURSOR_PLINK_STATUS == CLCD_DISABLE_CURSOR_PLINK
  CLEAR_BIT(Display_on_off_Control, CLCD_CURSOR_BLINK_STATUS_BIT);
#endif

  u8 Entry_Mode_Set = ENTRY_MODE_SET_INIT;
#if CLCD_CURSOR_ACTION == CLCD_CURSOR_INCREMENT
  SET_BIT(Entry_Mode_Set, CLCD_CURSOR_ACTION_BIT);
#elif CLCD_CURSOR_ACTION == CLCD_CURSOR_DECREMENT
  CLEAR_BIT(Entry_Mode_Set, CLCD_CURSOR_ACTION_BIT);
#endif

#if CLCD_DISPLAY_ACTION == CLCD_DISPLAY_SHIFT_RIGHT
  SET_BIT(Entry_Mode_Set, CLCD_DISPLAY_ACTION_BIT);
#elif CLCD_DISPLAY_ACTION == CLCD_DISPLAY_SHIFT_LEFT
  CLEAR_BIT(Entry_Mode_Set, CLCD_DISPLAY_ACTION_BIT);
#endif
  CLCD_VidSendCommand(CLCD_RETURN_HOME_COMMAND, CLCD_INFO);
  CLCD_VidSendCommand(Function_Set, CLCD_INFO);
  CLCD_VidSendCommand(Display_on_off_Control, CLCD_INFO);
  CLCD_VidSendCommand(CLCD_CLEAR_DISPLAY_COMMAND, CLCD_INFO);
  // CLCD_VidSendCommand(Entry_Mode_Set, CLCD_INFO);
}

void CLCD_VidDisplayName(const u8 *copy_u8name, CLCD_t *CLCD_INFO)
{

  while ((*copy_u8name) != '\0')
  {
    CLCD_VidSendData(*(copy_u8name), CLCD_INFO);
    copy_u8name++;
    if (((*copy_u8name) == ' '))
    {
#if CLCD_DISPLAY_ACTION == CLCD_DISPLAY_SHIFT_RIGHT
      _delay_ms(50);
#endif
    }
  }
}

void CLCD_VidGoTo(u8 copy_u8X, u8 copy_u8Y, CLCD_t *CLCD_INFO)
{
  u8 Local_u8Location = 0;

  if (CLCD_INFO->CLCD_TYPE == CLCD_TWO_16)
  {
    if (copy_u8X < 0 || copy_u8X > 1)
      return;
    if (copy_u8X == 0)
      Local_u8Location = copy_u8Y;
    if (copy_u8X == 1)
      Local_u8Location = copy_u8Y + CLCD_START_ADDRESS_SECOND_ROW;
  }
  else if (CLCD_INFO->CLCD_TYPE == CLCD_FOUR_20)
  {
    if (copy_u8X < 0 || copy_u8X > 3)
      return;
    if (copy_u8X == 0)
      Local_u8Location = copy_u8Y;
    if (copy_u8X == 1)
      Local_u8Location = copy_u8Y + CLCD_START_ADDRESS_SECOND_ROW;
    else if (copy_u8X == 2)
      Local_u8Location = copy_u8Y + CLCD_START_ADDRESS_THIRD_ROW;
    else if (copy_u8X == 3)
      Local_u8Location = copy_u8Y + CLCD_START_ADDRESS_FOURTH_ROW;
  }
  CLCD_VidSendCommand(Local_u8Location + SET_DDRAM_ADDRESS_INIT, CLCD_INFO);
}

void CLCD_VidClearDisplay(CLCD_t *CLCD_INFO)
{
  CLCD_VidSendCommand(CLCD_CLEAR_DISPLAY_COMMAND, CLCD_INFO);
}

void CLCD_VidCreateSpecialChar(u8 *copy_u8pattern, u8 copy_u8pattern_num, CLCD_t *CLCD_INFO)
{
  u8 local_CGRAM_Address = 8 * copy_u8pattern_num;
  CLCD_VidSendCommand(SET_CGRAM_ADDRESS_INIT + local_CGRAM_Address, CLCD_INFO);
  for (u8 i = 0; i < 8; i++)
    CLCD_VidSendData(copy_u8pattern[i], CLCD_INFO);
  CLCD_VidGoTo(CLCD_FIRST_ROW, CLCD_FIRST_COLUMN, CLCD_INFO);
}

void CLCD_VidSendSpecialChar(u8 copy_u8pattern, u8 copy_u8X, u8 copy_u8Y, CLCD_t *CLCD_INFO)
{
  CLCD_VidGoTo(copy_u8X, copy_u8Y, CLCD_INFO);
  CLCD_VidSendData(copy_u8pattern, CLCD_INFO);
}

void CLCD_VidSendInteger(u64 copy_u64integer, CLCD_t *CLCD_INFO)
{

  if (copy_u64integer != 0)
  {
    CLCD_VidSendInteger(copy_u64integer / 10, CLCD_INFO);
    CLCD_VidSendData((copy_u64integer % 10) + '0', CLCD_INFO);
  }
}

void CLCD_VidSendDecimal(f64 copy_f64decimal, CLCD_t *CLCD_INFO)
{

  f64 copy_f128fraction = copy_f64decimal - ((u64)copy_f64decimal);
  copy_f128fraction = copy_f128fraction * 10;
  u64 copy_u64integer = (u64)copy_f128fraction;
  if (copy_u64integer != 0)
  {
    CLCD_VidSendData(copy_u64integer + '0', CLCD_INFO);
    CLCD_VidSendDecimal(copy_f128fraction, CLCD_INFO);
  }
}

void CLCD_VidSendNumber(f64 copy_f64Number, CLCD_t *CLCD_INFO)
{
  if (copy_f64Number == 0)
    CLCD_VidSendData('0', CLCD_INFO);
  if (copy_f64Number < 0)
  {
    CLCD_VidSendData('-', CLCD_INFO);
    if ((u64)(-1 * copy_f64Number) == 0)
      CLCD_VidSendData('0', CLCD_INFO);
    CLCD_VidSendInteger((u64)(-1 * copy_f64Number), CLCD_INFO);
    if ((-1 * copy_f64Number) > (u64)(-1 * copy_f64Number))
    {
      CLCD_VidSendData('.', CLCD_INFO);
      CLCD_VidSendDecimal(-1 * copy_f64Number, CLCD_INFO);
    }
  }
  else if (copy_f64Number > 0)
  {
    if ((u64)copy_f64Number == 0)
      CLCD_VidSendData('0', CLCD_INFO);
    CLCD_VidSendInteger((u64)copy_f64Number, CLCD_INFO);
    if (copy_f64Number > (u64)copy_f64Number)
    {
      CLCD_VidSendData('.', CLCD_INFO);
      CLCD_VidSendDecimal(copy_f64Number, CLCD_INFO);
    }
  }
}

u8 CLCD_VidReadDisplay(u8 copy_u8X, u8 copy_u8Y, CLCD_t *CLCD_INFO)
{
  CLCD_VidGoTo(copy_u8X, copy_u8Y, CLCD_INFO);
  u8 Data = 0;
  u8 pin = 0;
  DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[0].PORT, CLCD_INFO->CLCD_DATA_PINS[0].PIN, Input);
  DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[1].PORT, CLCD_INFO->CLCD_DATA_PINS[1].PIN, Input);
  DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[2].PORT, CLCD_INFO->CLCD_DATA_PINS[2].PIN, Input);
  DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[3].PORT, CLCD_INFO->CLCD_DATA_PINS[3].PIN, Input);
  DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[4].PORT, CLCD_INFO->CLCD_DATA_PINS[4].PIN, Input);
  DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[5].PORT, CLCD_INFO->CLCD_DATA_PINS[5].PIN, Input);
  DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[6].PORT, CLCD_INFO->CLCD_DATA_PINS[6].PIN, Input);
  DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[7].PORT, CLCD_INFO->CLCD_DATA_PINS[7].PIN, Input);
  DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_CONTROL_PINS[0].PORT, CLCD_INFO->CLCD_CONTROL_PINS[0].PIN, High);
  DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_CONTROL_PINS[1].PORT, CLCD_INFO->CLCD_CONTROL_PINS[1].PIN, High);
  DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_CONTROL_PINS[2].PORT, CLCD_INFO->CLCD_CONTROL_PINS[2].PIN, High);
  _delay_ms(1);
  DIO_VoidGet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[0].PORT, CLCD_INFO->CLCD_DATA_PINS[0].PIN, &pin);
  Data |= (pin << Pin_0);
  DIO_VoidGet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[1].PORT, CLCD_INFO->CLCD_DATA_PINS[1].PIN, &pin);
  Data |= (pin << Pin_1);
  DIO_VoidGet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[2].PORT, CLCD_INFO->CLCD_DATA_PINS[2].PIN, &pin);
  Data |= (pin << Pin_2);
  DIO_VoidGet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[3].PORT, CLCD_INFO->CLCD_DATA_PINS[3].PIN, &pin);
  Data |= (pin << Pin_3);
  DIO_VoidGet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[4].PORT, CLCD_INFO->CLCD_DATA_PINS[4].PIN, &pin);
  Data |= (pin << Pin_4);
  DIO_VoidGet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[5].PORT, CLCD_INFO->CLCD_DATA_PINS[5].PIN, &pin);
  Data |= (pin << Pin_5);
  DIO_VoidGet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[6].PORT, CLCD_INFO->CLCD_DATA_PINS[6].PIN, &pin);
  Data |= (pin << Pin_6);
  DIO_VoidGet_Pin_Value(CLCD_INFO->CLCD_DATA_PINS[7].PORT, CLCD_INFO->CLCD_DATA_PINS[7].PIN, &pin);
  Data |= (pin << Pin_7);
  DIO_VoidSet_Pin_Value(CLCD_INFO->CLCD_CONTROL_PINS[2].PORT, CLCD_INFO->CLCD_CONTROL_PINS[2].PIN, Low);
  DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[0].PORT, CLCD_INFO->CLCD_DATA_PINS[0].PIN, Output);
  DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[1].PORT, CLCD_INFO->CLCD_DATA_PINS[1].PIN, Output);
  DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[2].PORT, CLCD_INFO->CLCD_DATA_PINS[2].PIN, Output);
  DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[3].PORT, CLCD_INFO->CLCD_DATA_PINS[3].PIN, Output);
  DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[4].PORT, CLCD_INFO->CLCD_DATA_PINS[4].PIN, Output);
  DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[5].PORT, CLCD_INFO->CLCD_DATA_PINS[5].PIN, Output);
  DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[6].PORT, CLCD_INFO->CLCD_DATA_PINS[6].PIN, Output);
  DIO_VoidSet_Pin_Direction(CLCD_INFO->CLCD_DATA_PINS[7].PORT, CLCD_INFO->CLCD_DATA_PINS[7].PIN, Output);
  return Data;
}