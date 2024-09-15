#include "STD_Types.h"
#include "BIT_Math.h"
#include "DIO_init.h"
#include "UART_private.h"
#include "timer_config.h"
#include "timer_private.h"
#include <util/delay.h>

                               void TIMER1_voidSetCompareMatchValueForA();
void Timer1_VidInit(void);
u8 UART_u8Recieve(void);
void UART_VidInit(void);

int main()                       


{
Timer1_VidInit();
    UART_VidInit();
    DIO_VoidSet_Pin_Direction( Port_D, Pin_0, Input);
    DIO_VoidSet_Pin_Direction( Port_D, Pin_5, Output); 
    u8 status;
  while(1){
    status=UART_u8Recieve();
    if(status=='I'){
      TIMER1_voidSetCompareMatchValueForA();
    }
  }
}


void Timer1_VidInit(void)
{
  /* Clear Timer_1 Mode Bits and prescaller */
  TCCR1A &= TIMER_1_CLEAR_TCCR1A;
  TCCR1B &= TIMER_1_CLEAR_TCCR1B;
  /* Set Timer_1 Mode */
  TCCR1A |= ((TIMER_1_PWM_PHASE_CORRECT_ICR1_MODE & TIMER_1_SET_WAVEGEN_LAST_TWO));
  TCCR1B |= (((TIMER_1_PWM_PHASE_CORRECT_ICR1_MODE << 1) & TIMER_1_CLEAR_WAVEGEN_FIRST_THREE));
  /* Set Compare Output Mode */
  TCCR1A |= (TIMER_1_PHASE_CORRECT_COMPARE_OUTPUT_MODE_A << 6);
  TCCR1A |= (TIMER_1_PHASE_CORRECT_COMPARE_OUTPUT_MODE_A << 4);

  TCNT1 = TIMER_1_PRELOAD_VALUE;         /* SET Preload Value For Timer 1 */

  ICR1 = TIMER_1_ICR1_VALUE;             /* Set ICR1 Value */

  OCR1A = TIMER_1_COMPARE_MATCH_VALUE_A; /* SET Compare Match Value for Timer 1 Bin A */

  /* SELECT Prescalle*/
  TCCR1B |= TIMER_1_PRE_SCALAR_VALUE;

}

void UART_VidInit(void){ 
  u8 Local_UCSRC=0;
  SET_BIT(Local_UCSRC,7);
  SET_BIT(Local_UCSRC,0);
  SET_BIT(Local_UCSRC,1);
  SET_BIT(UCSRB, UCSRB_RXEN);
  SET_BIT(UCSRB, UCSRB_TXEN);
}

u8 UART_u8Recieve(void){
  while(GET_BIT(UCSRA,UCSRA_RXC)==0);
  return UDR;
}


void TIMER1_voidSetCompareMatchValueForA()
{
  OCR1A *=1.02 ; /* increase Speed */
}
