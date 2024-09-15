#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_init.h"
#include "UART_init.h"
#include "GIE_init.h"
#include <util/delay.h>

void ISR() {}

int main()
{
    DIO_VoidSet_Pin_Direction(Port_B, Pin_0, Output);
    DIO_VoidSet_Pin_Direction(Port_D, Pin_1, Output);
    DIO_VoidSet_Pin_Direction(Port_D, Pin_0, Input);
    DIO_VoidSet_Pin_Value(Port_B, Pin_0, Low);
    GIE_VidEnable();
    USART_VidInit();
    while (1)
    {
    }
}
