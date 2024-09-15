#include "STD_Types.h"
#include "BIT_MATH.h"
#include "STP_init.h"
#include "DIO_init.h"
#include "STP_config.h"
#include <util/delay.h>

u8 pin[4] = {STP_Pin_0, STP_Pin_1, STP_Pin_2, STP_Pin_3};

void STP_VidRotateRight(u16 steps)
{
  for (u16 i = 0; i < steps; i++)
  {
    DIO_VoidSet_Pin_Value(STP_Port, pin[i % 4], Low);
    _delay_ms(3);
    DIO_VoidSet_Pin_Value(STP_Port, pin[i % 4], High);
  }
}

void STP_VidRotateLeft(u16 steps)
{
  for (u16 i = steps; i >= 0; i--)
  {
    DIO_VoidSet_Pin_Value(STP_Port, pin[i % 4], Low);
    _delay_ms(3);
    DIO_VoidSet_Pin_Value(STP_Port, pin[i % 4], High);
  }
}

void STP_VidInit(void)
{
  for (u8 i = 0; i < 4; i++)
  {
    DIO_VoidSet_Pin_Direction(STP_Port, pin[i], Output);
    DIO_VoidSet_Pin_Value(STP_Port, pin[i], High);
  }
}