#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_private.h"
#include "DIO_init.h"
#include "MOT_config.h"
#include "MOT_private.h"
#include "MOT_init.h"
#include <util/delay.h>

void MOT_VidInit(void)
{
  DIO_VoidSet_Pin_Direction(MOT_PORT, TOP_LEFT, Output);
  DIO_VoidSet_Pin_Direction(MOT_PORT, BOTTOM_RIGHT, Output);
  DIO_VoidSet_Pin_Direction(MOT_PORT, TOP_RIGHT, Output);
  DIO_VoidSet_Pin_Direction(MOT_PORT, BOTTOM_LEFT, Output);
}

void MOT_VidRotateRight(void)
{
  DIO_VoidSet_Pin_Value(MOT_PORT, TOP_LEFT, High);
  DIO_VoidSet_Pin_Value(MOT_PORT, BOTTOM_RIGHT, High);
  DIO_VoidSet_Pin_Value(MOT_PORT, TOP_RIGHT, Low);
  DIO_VoidSet_Pin_Value(MOT_PORT, BOTTOM_LEFT, Low);
}

void MOT_VidRotateLeft(void)
{
  DIO_VoidSet_Pin_Value(MOT_PORT, TOP_LEFT, Low);
  DIO_VoidSet_Pin_Value(MOT_PORT, BOTTOM_RIGHT, Low);
  DIO_VoidSet_Pin_Value(MOT_PORT, TOP_RIGHT, High);
  DIO_VoidSet_Pin_Value(MOT_PORT, BOTTOM_LEFT, High);
}

void MOT_VidStop(void)
{
  DIO_VoidSet_Pin_Value(MOT_PORT, TOP_LEFT, Low);
  DIO_VoidSet_Pin_Value(MOT_PORT, BOTTOM_RIGHT, Low);
  DIO_VoidSet_Pin_Value(MOT_PORT, TOP_RIGHT, Low);
  DIO_VoidSet_Pin_Value(MOT_PORT, BOTTOM_LEFT, Low);
}
