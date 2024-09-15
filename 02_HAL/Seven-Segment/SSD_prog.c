
/****************************************************************************
*****************************************************************************
*******************   SWC    :       SSD Driver         *********************
*******************    By    : Youssef Mostafa Mohamed  *********************
*******************   Date   :       3/9/2022          *********************
*******************  Version :          V1.0            *********************
*****************************************************************************
****************************************************************************/

#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_init.h"
#include "DIO_private.h"
#include "SSD_private.h"
#include "SSD_config.h"
#include "SSD_interface.h"

void SSD_VidInit(u8 SSD_Copy_u8Id)
{
  switch (SSD_Copy_u8Id)
  {
  case SSD_ID0:
    DIO_VoidSet_Port_Direction(SSD0_PORT, Output);
    break;
  case SSD_ID1:
    DIO_VoidSet_Port_Direction(SSD1_PORT, Output);
    break;
  }
}

void SSD_VidDisplayNumber(u8 SSD_Copy_u8Id, u8 Copy_u8Number)
{
  switch (SSD_Copy_u8Id)
  {
  case SSD_ID0:
    DIO_VoidSet_Port_Value(SSD0_PORT, seven_segment_cathode[Copy_u8Number]);
    break;
  case SSD_ID1:
    DIO_VoidSet_Port_Value(SSD1_PORT, seven_segment_cathode[Copy_u8Number]);
    break;
  }
}

void SSD_VidTurnOff(u8 SSD_Copy_u8Id)
{
  switch (SSD_Copy_u8Id)
  {
  case SSD_ID0:
    DIO_VoidSet_Port_Value(SSD0_PORT, Null);
    break;
  case SSD_ID1:
    DIO_VoidSet_Port_Value(SSD1_PORT, Null);
    break;
  }
}
