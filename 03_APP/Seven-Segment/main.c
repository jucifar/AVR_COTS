#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_init.h"
#include "DIO_private.h"
#include <util/delay.h>
#define Null  0b00000000 
#define ZERO  0b00111111
#define ONE   0b00000110
#define TWO   0b01011011
#define THREE 0b01001111
#define FOUR  0b01100110
#define FIVE  0b01101101
#define SIX   0b01111101
#define SEVEN 0b00000111
#define EIGHT 0b01111111
#define NINE  0b01101111
int main(){
	u8 seven_segment_c[10]={ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE};
  u8 seven_segment_a[10]={~ZERO,~ONE,~TWO,~THREE,~FOUR,~FIVE,~SIX,~SEVEN,~EIGHT,~NINE};
	DIO_VoidSet_Port_Direction(Port_A,Output);
	DIO_VoidSet_Port_Direction(Port_C,Output);
  DIO_VoidSet_Pin_Direction(Port_B,Pin_0,Input);
  DIO_VoidSet_Pin_Value(Port_B,Pin_0,High);
  u8 x;
  while(1){
    DIO_VoidGet_Pin_Value(Port_B,Pin_0,&x);
    if(x==0){
	 for(int j =0;j<10;j++){
         DIO_VoidSet_Port_Value(Port_C,seven_segment_c[j]);
        _delay_ms(250);
         for(int i =0;i<10;i++){
			    	DIO_VoidSet_Port_Value(Port_A,seven_segment_c[i]);
				    _delay_ms(250);
			   }
		  }
    }
    DIO_VoidSet_Port_Value(Port_C,seven_segment_c[0]);                             
    DIO_VoidSet_Port_Value(Port_A,seven_segment_c[0]);                             

	}
return 0;
}
