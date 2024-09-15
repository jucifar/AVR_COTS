#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_private.h"
#include "DIO_init.h"
#include "KPAD_private.h"
#include "KPAD_config.h"
#include "KPAD_init.h"
#include "LCD_config.h"
#include "LCD_init.h"
#include "util/delay.h"

int main(){
LCD_VidInit();
  
  DIO_VoidSet_Custom_Port_Direction(KPAD_PORT,0x0f);
  DIO_VoidSet_Port_Value(KPAD_PORT, 0xff); 
  
  while(1){
    u8 input=0,inputs[51]={0},ops[50]={0},i=0;
    f64 nums[50]={0},num=0;
    while(input!='=' && i<51){
      input=KPAD_VidGetPressedKey();
      if(input!=101){
       	if(i==0 && !(input-48>=0 && input-48 <=9))
       		continue;
        else if ((!(input-48>=0 &&input-48 <=9)) && (!(inputs[i-1]-48>=0 && inputs[i-1]-48<=9)))
        	continue;
       	else{
       		LCD_VidSendData(input);
        	inputs[i++]=input;
        }
      }
    }
    	LCD_VidClearDisplay();
    	if(input!='=') 
  		LCD_VidDisplayName("Invalid Equation");
  	_delay_ms(1111);	      
  	LCD_VidClearDisplay();
    if (input != 101 && input =='='){
        inputs[i++]='\0';
        LCD_VidDisplayName(inputs);
        _delay_ms(2222);
        LCD_VidClearDisplay();
        u8 m=1,flag=1;
        if (!(inputs[0]-'0'>=0 && inputs[0]-'0' <=9)){
          LCD_VidDisplayName("Invalid Equation");
          _delay_ms(1111);
          LCD_VidClearDisplay();
          flag=0;
        }
        while(inputs[m] != '\0' && flag){
          LCD_VidClearDisplay();
          if ((!((inputs[0]-'0')>=0 && (inputs[0]-'0') <=9)) || (!(inputs[m-1]-'0' >=0 && inputs[m-1]-'0' <=9 ) && (!(inputs[m]-'0'>=0 && inputs[m]-'0' <=9)))){
            LCD_VidDisplayName("Invalid Equation");
            _delay_ms(1111);
            flag=0;
            LCD_VidClearDisplay();
          }
          m++;
        }

        if(flag){
          u8 n=0;
          for(u8 k=0 ;inputs[k]!='\0';k++){
            if (((inputs[k]-'0')>=0 && (inputs[k]-'0') <=9))
                num=num*10+(inputs[k]-'0');
            if( !((inputs[k]-'0')>=0 && (inputs[k]-'0') <=9)){
              ops[n]=inputs[k];
              nums[n++]= num;
              num=0;
            }
          }
        
          for (u8 m=0 ;ops[m]!='\0';m++){
          switch(ops[m]){
            case '*': nums[m+1]=nums[m]*nums[m+1];if (m!=0)ops[m]=ops[m-1]; else  ops[m] ='+' ;nums[m]=0;break;
            case '/': nums[m+1]=nums[m]/nums[m+1];if (m!=0)ops[m]=ops[m-1]; else  ops[m] ='+'; nums[m]=0;break;
            case '%': nums[m+1]=(u64)nums[m]%(u64)nums[m+1];if (m!=0)ops[m]=ops[m-1]; else  ops[m] ='+' ;nums[m]=0;break;
          }
        }

          f64 result =nums[0];
          for(u8 m=1; ops[m-1]!='\0'; m++)
             switch(ops[m-1]){
               case '+': result+=nums[m];break;
               case '-': result-=nums[m];break;
               case '=': LCD_VidClearDisplay(); LCD_VidSendNumber(result) ;_delay_ms(3333); LCD_VidClearDisplay(); break; 
          }
        }
     }
   }
}

