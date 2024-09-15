  
  /****************************************************************************
  ***************************************************************************** 
  *******************   SWC    :       DIO Driver         ********************                             
  *******************    By    : Youssef Mostafa Mohamed  ********************                             
  *******************   Date   :       27/8/2022          ********************                            
  *******************  Version :          V1.0            ********************                            
  **************************************************************************** 
  ***************************************************************************/ 
#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_init.h"
#include "DIO_private.h"

/* Setting PIN Direction */
  void DIO_VoidSet_Pin_Direction(u8 copy_u8port, u8 copy_u8pin, u8 copy_u8direction){
        if(copy_u8direction == Input){
            switch(copy_u8port){
              case Port_A: CLEAR_BIT(DDRA,copy_u8pin);break;
              case Port_B: CLEAR_BIT(DDRB,copy_u8pin);break;
              case Port_C: CLEAR_BIT(DDRC,copy_u8pin);break;
              case Port_D: CLEAR_BIT(DDRD,copy_u8pin);break;
            }
        }
        else if(copy_u8direction == Output){
             switch(copy_u8port){
	      case Port_A: SET_BIT(DDRA,copy_u8pin);break;
              case Port_B: SET_BIT(DDRB,copy_u8pin);break;
              case Port_C: SET_BIT(DDRC,copy_u8pin);break;
              case Port_D: SET_BIT(DDRD,copy_u8pin);break;
             }
        }
      }

    /* Setting PIN Value */
     void DIO_VoidSet_Pin_Value(u8 copy_u8port, u8 copy_u8pin, u8 copy_u8Value){
        if(copy_u8Value == High){
            switch(copy_u8port){
              case Port_A: SET_BIT(PORTA,copy_u8pin);break;
              case Port_B: SET_BIT(PORTB,copy_u8pin);break;
              case Port_C: SET_BIT(PORTC,copy_u8pin);break;
              case Port_D: SET_BIT(PORTD,copy_u8pin);break;
            }
        }
        else if(copy_u8Value == Low){
           switch(copy_u8port){
	      case Port_A: CLEAR_BIT(PORTA,copy_u8pin);break;
              case Port_B: CLEAR_BIT(PORTB,copy_u8pin);break;
              case Port_C: CLEAR_BIT(PORTC,copy_u8pin);break;
              case Port_D: CLEAR_BIT(PORTD,copy_u8pin);break;
           }
         }
    }
         
    /* Getting PIN Value */                                                             
      void DIO_VoidGet_Pin_Value(u8 copy_u8port, u8 copy_u8pin,u8* copy_u8data){
          switch(copy_u8port){
            case Port_A:(*copy_u8data)=GET_BIT(PINA,copy_u8pin);break;
            case Port_B:(*copy_u8data)=GET_BIT(PINB,copy_u8pin);break;
            case Port_C:(*copy_u8data)=GET_BIT(PINC,copy_u8pin);break;
            case Port_D:(*copy_u8data)=GET_BIT(PIND,copy_u8pin);break;
          }
      }      
    /* Setting PORT Direction */
      void DIO_VoidSet_Port_Direction(u8 copy_u8port, u8 copy_u8direction){
      		if(copy_u8direction==Input){
      			switch(copy_u8port){
      				case Port_A:DDRA=0b00000000;break;
      				case Port_B:DDRB=0b00000000;break;
      				case Port_C:DDRC=0b00000000;break;
      				case Port_D:DDRD=0b00000000;break;
      			}
      		}
      		else if(copy_u8direction==Output){
     			 switch(copy_u8port){
      				case Port_A:DDRA=0b11111111;break;
      				case Port_B:DDRB=0b11111111;break;
      				case Port_C:DDRC=0b11111111;break;
      				case Port_D:DDRD=0b11111111;break;
      			}
      		}
      }
      
    /* Setting DDR ( DDR register ) with custom direction */  
     void DIO_VoidSet_Custom_Port_Direction(u8 copy_u8port,u8 copy_u8value){
      		switch(copy_u8port){
      			case Port_A:DDRA=copy_u8value;break;
      			case Port_B:DDRB=copy_u8value;break;			
      			case Port_C:DDRC=copy_u8value;break;
      			case Port_D:DDRD=copy_u8value;break;
      
    		}			
      }
      
    /* Setting PORT ( PORT register ) Value */
      void DIO_VoidSet_Port_Value(u8 copy_u8port, u8 copy_u8value){
      			switch(copy_u8port){
      				case Port_A:PORTA=copy_u8value;break;
      				case Port_B:PORTB=copy_u8value;break;
      				case Port_C:PORTC=copy_u8value;break;
      				case Port_D:PORTD=copy_u8value;break;
      			}
      	}
      	
    /* Getting PORT ( PIN  register )  */
	void DIO_VoidGet_Port_Value(u8 copy_u8port, u8* copy_u8data){
          switch(copy_u8port){
            case Port_A:(*copy_u8data)=PINA;break;
            case Port_B:(*copy_u8data)=PINB;break;
            case Port_C:(*copy_u8data)=PINC;break;
            case Port_D:(*copy_u8data)=PIND;break;
          }
      }    



