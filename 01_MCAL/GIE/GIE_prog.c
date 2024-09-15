#include "STD_Types.h"
#include "BIT_MATH.h"
#include "GIE_private.h"
#include "GIE_init.h"

void GIE_VidEnable(void)
{
  SET_BIT(SREG, SREG_I);
}

void GIE_VidDisable(void)
{
  CLEAR_BIT(SREG, SREG_I);
}
