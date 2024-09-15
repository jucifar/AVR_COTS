#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_init.h"
#include "CLCD_init.h"
#include <util/delay.h>

int main()
{
    CLCD_t CLCD_1 = {CLCD_TWO_16, CLCD_8_BIT_MODE, {{Port_C, Pin_0}, {Port_C, Pin_1}, {Port_C, Pin_2}, {Port_C, Pin_3}, {Port_C, Pin_4}, {Port_C, Pin_5}, {Port_C, Pin_6}, {Port_C, Pin_7}}, {{Port_B, Pin_0}, {Port_B, Pin_1}, {Port_B, Pin_2}}};
    CLCD_VidInit(&CLCD_1);
    u8 data;
    while (1)
    {
        CLCD_VidGoTo(0, 0, &CLCD_1);
        CLCD_VidDisplayName("Ahmed", &CLCD_1);
        _delay_ms(2222);
        for (int i = 0; i < 16; i++)
        {
            data = CLCD_VidReadDisplay(0, i, &CLCD_1);
            CLCD_VidGoTo(1, i, &CLCD_1);
            CLCD_VidSendData(data, &CLCD_1);
        }
        _delay_ms(2222);
        CLCD_VidClearDisplay(&CLCD_1);
        _delay_ms(2222);
    }
}
