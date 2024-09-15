#include "STD_Types.h"
#include "BIT_MATH.h"
#include "LCD_init.h"
#include <util/delay.h>

u8 Hamada1[8]={0b01110,0b01110,0b00100,0b10101,0b01110,0b00100,0b01010,0b10001};
u8 Hamada2[8]={0b01110,0b01110,0b00101,0b00110,0b01100,0b10100,0b01010,0b10000};
u8 Hamada3[8]={0b00000,0b00000,0b11100,0b11100,0b01011,0b01100,0b01000,0b10100};
u8 aship1[8]={0b00000,0b00000,0b00011,0b00100,0b11000,0b00100,0b00011,0b00000};
u8 aship2[8]={0b00100,0b01010,0b10001,0b00000,0b00000,0b00000,0b11011,0b00100};
u8 aship3[8]={0b00000,0b00000,0b11000,0b00100,0b00011,0b00100,0b11000,0b00000};
u8 Alien[8]={0b11111,0b10101,0b11111,0b11111,0b01110,0b01010,0b11011,0b00000};
u8 ship1[8]={0b00000,0b00100,0b00000,0b00100,0b00100,0b01010,0b01010,0b11111};
u8 ship2[8]={0b00100,0b00000,0b00000,0b00100,0b00100,0b01010,0b01010,0b11111};
u8 bomb[8]={0b11011,0b00111,0b11100,0b10101,0b11011,0b10110,0b01011,0b11010};
u8 bullet[8]={0b00000,0b00000,0b000000,0b00000,0b00001,0b00000,0b00000,0b00000};
u8 bell[8]={0b00000,0b00100,0b01110,0b01110,0b01110,0b11111,0b00000,0b00100};
u8 daship1[8]={0b00000,0b00010,0b00101,0b11000,0b00100,0b00011,0b00000,0b00000};
u8 daship2[8]={0b00000,0b00100,0b01011,0b10000,0b00000,0b01011,0b10100,0b00000};
u8 Hamada4[8]={0b01110,0b01110,0b00100,0b10111,0b01100,0b00100,0b01010,0b10010};
u8 Hamada5[8]={0b01110,0b01110,0b00100,0b11100,0b00110,0b00100,0b01010,0b01001};
u8 skull[8]={0b00000,0b01110,0b10101,0b11011,0b01110,0b01110,0b00000,0b00000};

int main(){
  LCD_VidInit();
  while(1){
  LCD_VidGoTo(0, 1);
  LCD_VidDisplayName("< Space War >");
  _delay_ms(1000);
  LCD_VidGoTo(0,3);
  LCD_VidDisplayName("Air forces");
    LCD_VidGoTo(1, 4);
  LCD_VidDisplayName(" Attack !");
  _delay_ms(1000);
  LCD_VidCreateSpecialChar(ship1, 0);
  LCD_VidCreateSpecialChar(ship2, 1);
  LCD_VidCreateSpecialChar(aship1,2);
  LCD_VidCreateSpecialChar(aship2,3);
  LCD_VidCreateSpecialChar(aship3,4);
  LCD_VidCreateSpecialChar(bell,  5); 
  LCD_VidCreateSpecialChar(daship1,6);
  LCD_VidCreateSpecialChar(daship2,7);
    int i=0 ,flag=0;
    for(int j=0; j<25 ; j++){
      LCD_VidClearDisplay();
     if(j<=10)
      LCD_VidSendSpecialChar(5, 0 , 15);
    if((j/14)%2==0){
       LCD_VidSendSpecialChar(2, 0, i%14);
       LCD_VidSendSpecialChar(3, 0, (i%14)+1);
       LCD_VidSendSpecialChar(4, 0, (i%14)+2);
       if(i>=2|| flag ){
          LCD_VidSendSpecialChar(i%2 ,1, (i%14) +1);
          flag=1;
        }
      i++;
      }
    else if((j/14) %2==1){
       i--;
       LCD_VidSendSpecialChar(2, 0 , i%14);
       LCD_VidSendSpecialChar(3, 0 , (i%14) +1);
       LCD_VidSendSpecialChar(4, 0 , (i%14)+2);
       if(i>=2 ||flag)
          LCD_VidSendSpecialChar(i%2 ,1, (i%14) +1);
    }
    _delay_ms(200);
  }
    LCD_VidClearDisplay();
    LCD_VidSendSpecialChar(6, 0, i%14);
    LCD_VidSendSpecialChar(7, 0, (i%14)+1);
    LCD_VidSendSpecialChar(4, 0, (i%14)+2);
    LCD_VidSendSpecialChar(0, 1, (i%14) +1);
    _delay_ms(750);
      LCD_VidClearDisplay();
    LCD_VidCreateSpecialChar(Hamada1, 0);
    LCD_VidCreateSpecialChar(Hamada2, 1);
    LCD_VidCreateSpecialChar(Hamada3, 2);
    LCD_VidCreateSpecialChar(bullet, 3);
    LCD_VidCreateSpecialChar(Alien, 4);
    LCD_VidClearDisplay();
    LCD_VidGoTo(0, 0);
    LCD_VidDisplayName(">They Landed,Sir");
    _delay_ms(1000);
    LCD_VidGoTo(0, 0);
    LCD_VidDisplayName("Soldiers, attack!");
    _delay_ms(1000);
    i=0;
    for( ;i<25 ;i++){
        LCD_VidClearDisplay();
        (i>=8)? flag=0 : LCD_VidSendSpecialChar(5, 0, 15);
        if (i<=4)
          LCD_VidSendSpecialChar(4, 1, 15 -(i%5));
        else
          LCD_VidSendSpecialChar(4, 1, 11); 
        if (i==1)
          LCD_VidSendSpecialChar(0, 1, i-1);
        else if (i==2 || i==3)
          LCD_VidSendSpecialChar(1, 1, i-1);
        else if (i>=4)
          LCD_VidSendSpecialChar(2, 1, 3);
        if(i>4)
          LCD_VidSendSpecialChar(3, 1 , (i%6) +5);
        _delay_ms(250);
    }
    LCD_VidCreateSpecialChar(skull, 4);
    LCD_VidSendSpecialChar(4, 1, 11);
    _delay_ms(1000);
    LCD_VidClearDisplay(); 
    LCD_VidCreateSpecialChar(Hamada4, 1);
    LCD_VidCreateSpecialChar(Hamada5, 2);
    LCD_VidClearDisplay();
    LCD_VidGoTo(0, 5);
    LCD_VidDisplayName("gg Ez");
    _delay_ms(1000);
    i=0;
    for(;i<25 ;i++){
      LCD_VidClearDisplay();
      LCD_VidGoTo(0, 3);
      LCD_VidDisplayName(" We Won <3 ");
      LCD_VidSendSpecialChar(i%3, 1, i);
      _delay_ms(300);
    }
    LCD_VidClearDisplay();
  }
}
