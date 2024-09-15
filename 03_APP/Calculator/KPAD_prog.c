#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_private.h"
#include "DIO_init.h"
#include "KPAD_config.h"
#include "KPAD_init.h"

 u8 KPAD_arr[4][4]={
                        {'/' , '*' , '%' , '='},
                        {'8' , '9' , '+' , '-'},
                        {'4' , '5' , '6' , '7'},
                        {'0' , '1' , '2' , '3'} 
                    };
                   
 u8 col_arr[]={COL_1,COL_2,COL_3,COL_4};
 u8 row_arr[]={ROW_1,ROW_2,ROW_3,ROW_4};
 
u8 KPAD_VidGetPressedKey(void){
  u8 pressed_key=101,x;
  for (u8 col=0 ;col<COL_NUM ;col++){
    DIO_VoidSet_Pin_Value(KPAD_PORT, col_arr[col], Low);
    for(u8 row =0; row < ROW_NUM ;row++){
      DIO_VoidGet_Pin_Value(KPAD_PORT, row_arr[row], &x);
      if(x==0){
        pressed_key=KPAD_arr[row][col]; 
        while(x==0)
          DIO_VoidGet_Pin_Value(KPAD_PORT, row_arr[row], &x);
     	return pressed_key;
      }
    }
    DIO_VoidSet_Pin_Value(KPAD_PORT, col_arr[col], High);
  }
  return pressed_key;
}

