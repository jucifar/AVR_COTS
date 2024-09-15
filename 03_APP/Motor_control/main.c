#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_init.h"
#include "LCD_config.h"
#include "LCD_init.h"
#include "KPAD_config.h"
#include "KPAD_init.h"
#include "MOT_config.h"
#include "MOT_init.h"
#include <util/delay.h>

int main (){
  LCD_VidInit();
  KPAD_VidInit();
  MOT_VidInit();
  u8 input,last='0',direction;
  while (1){
    input='0';
    LCD_VidClearDisplay();
    LCD_VidDisplayName("'R' For Right");
    _delay_ms(1000);
    LCD_VidClearDisplay();
    LCD_VidDisplayName("'L' For Left");
    _delay_ms(1000);
    LCD_VidClearDisplay();
    LCD_VidDisplayName("'S' To Stop");
    _delay_ms(1000);
    LCD_VidClearDisplay();
    LCD_VidDisplayName("'I' TO invert");
    _delay_ms(1000);
    LCD_VidClearDisplay();
    LCD_VidDisplayName("Your Choice!");
    _delay_ms(1000);
    LCD_VidClearDisplay();
    while(input =='0')
      input = KPAD_VidGetPressedKey();
    if(input !='0'){
      direction=input;
      if(direction =='L'){
       LCD_VidClearDisplay();
       LCD_VidSendData('L');
        MOT_VidStop();
       _delay_ms(15);
       MOT_VidRotateLeft();
      _delay_ms(1111);
       last='L';
       }
      else if (direction =='R'){
       LCD_VidClearDisplay();
       LCD_VidSendData('R');
        MOT_VidStop();
       _delay_ms(15);
        MOT_VidRotateRight();
        _delay_ms(1111);
        last='R';
      }
      else if (direction =='S'){
        LCD_VidClearDisplay();
        LCD_VidDisplayName("Stopping");
        MOT_VidStop();
        _delay_ms(1111);
      }
      else if(direction=='I'){
         if(last=='L'){
          LCD_VidClearDisplay();
           LCD_VidDisplayName("Rotate Right");
            MOT_VidStop();
            _delay_ms(15);
            MOT_VidRotateRight();
          _delay_ms(1111);
           last='R';
          }else if(last=='R'){
            LCD_VidClearDisplay();
            LCD_VidDisplayName("Rotate Left");
             MOT_VidStop();
            _delay_ms(15);
            MOT_VidRotateLeft();
            last='L';
          _delay_ms(1111);
          }else{
          LCD_VidDisplayName("Motor Not Working");
          _delay_ms(1111);
          LCD_VidClearDisplay();
        } 
        
      }
    }
  }
}
