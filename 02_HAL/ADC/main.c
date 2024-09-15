#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_private.h"
#include "DIO_init.h"
#include "LCD_config.h"
#include "LCD_init.h"
#include "ADC_init.h"
#include "GIE_init.h"
#include <util/delay.h>

void notification_function(u16 reading){
  DIO_VoidSet_Pin_Value(Port_A,Pin_7,High);
    LCD_VidClearDisplay();
    LCD_VidSendNumber((f64)reading*(0.48828125));
    _delay_ms(250);
    DIO_VoidSet_Pin_Value(Port_A,Pin_7,Low);
    _delay_ms(250);
    LCD_VidClearDisplay(); 
    LCD_VidSendNumber(10000);  
    _delay_ms(250);
    LCD_VidClearDisplay(); 
    _delay_ms(250);
}


int main(){
  GIE_VidEnable();
  LCD_VidInit();
  ADC_VidInit();
  DIO_VoidSet_Pin_Direction(Port_A,Pin_0,Input);
  DIO_VoidSet_Pin_Direction(Port_A,Pin_7,Output);
  DIO_VoidSet_Port_Direction(Port_D,Output);
  DIO_VoidSet_Port_Direction(Port_B,Output);
  u16 reading;
  while(1){
    ADC_u8StartConversionAsynchronous(0,&reading,notification_function);
  }
}
