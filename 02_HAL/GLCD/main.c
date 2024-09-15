#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_init.h"
#include "GLCD_init.h"
#include <util/delay.h>

int main()
{
    GLCD_t GLCD_1 = {GLCD_8_BIT_MODE, {{Port_C, Pin_0}, {Port_C, Pin_1}, {Port_C, Pin_2}, {Port_C, Pin_3}, {Port_C, Pin_4}, {Port_C, Pin_5}, {Port_C, Pin_6}, {Port_C, Pin_7}}, {{Port_B, Pin_0}, {Port_B, Pin_1}, {Port_B, Pin_2}, {Port_B, Pin_3}, {Port_B, Pin_4}, {Port_B, Pin_5}}};
    GLCD_VidInit(&GLCD_1);
    u8 Data = 0;
    while (1)
    {
        GLCD_VidDisplayText_Page(0, 0, "Welcome", ' ', &GLCD_1);
        _delay_ms(2000);
        for (int i = 0; i < 64; i++)
        {
            Data = GLCD_u8GetPage(0, i, &GLCD_1);
            GLCD_VidGoToPY(1, i, &GLCD_1);
            GLCD_VidSendByte(Data, i, &GLCD_1);
        }
        _delay_ms(3000);

        GLCD_VidGoToPY(5, 0, &GLCD_1);
        GLCD_VidSendInteger(1, 'x', 0, &GLCD_1);
        _delay_ms(3000);

        GLCD_VidClearDisplay(&GLCD_1);
    }
}
