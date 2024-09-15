#include "STD_Types.h"
#include "BIT_MATH.h"
#include "GIE_init.h"
#include "EXTI_init.h"
#include "DIO_init.h"
#include "EXTI_config.h"
#include <util/delay.h>

int main (){
  DIO_VoidSet_Pin_Direction(INT_0_1_PORT, INT_0_PIN, Input);
  DIO_VoidSet_Pin_Value(INT_0_1_PORT, INT_0_PIN, High);
  DIO_VoidSet_Pin_Direction(Port_D, Pin_0, Output);
  GIE_VidEnable();
  EXTI_VidEnable();
  while (1);
}

void __vector_1 (void) __attribute__((signal));
void __vector_1 (void){
  static u8 state=0;
  DIO_VoidSet_Pin_Value(Port_D,Pin_0, state^=1);
  _delay_ms(20);
}
