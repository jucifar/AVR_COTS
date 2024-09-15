#include "STD_Types.h"
#include "BIT_Math.h"
#include "DIO_init.h"
#include "UART_private.h"
#include <util/delay.h>

void UART_VidSend(u8 Copy_u8Data);
void UART_VidInit(void);

int main() {

    /* Uart */
    UART_VidInit();
  /* Set Button */
    DIO_VoidSet_Pin_Direction( Port_A, Pin_0, Input);
    DIO_VoidSet_Pin_Value( Port_A, Pin_0, High);
    DIO_VoidSet_Pin_Direction(Port_D,Pin_1,Output);
    u8 status=1;
  while(1){
    DIO_VoidGet_Pin_Value( Port_A, Pin_0,&status);
    if(status==0){
      _delay_ms(20);
      DIO_VoidGet_Pin_Value( Port_A, Pin_0,&status);
      if(status==0){
        UART_VidSend('I');
      }
    }else{
      UART_VidSend('S');
    }
  }
}

void UART_VidInit(void){ 
  u8 Local_UCSRC=0;
  SET_BIT(Local_UCSRC,7);
  SET_BIT(Local_UCSRC,0);
  SET_BIT(Local_UCSRC,1);
  SET_BIT(UCSRB, UCSRB_RXEN);
  SET_BIT(UCSRB, UCSRB_TXEN);
}

void UART_VidSend(u8 Copy_u8Data){
  while(GET_BIT(UCSRA,UCSRA_UDRE)==0);
  UDR=Copy_u8Data;
}
