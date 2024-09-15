#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_init.h"
#include "SPI_init.h"
#include "util/delay.h"
/*Master*/
int main(void)
{
  DIO_VoidSet_Pin_Direction(Port_B, SCK_PIN, Output);
  DIO_VoidSet_Pin_Direction(Port_B, MOSI_PIN, Output);
  DIO_VoidSet_Pin_Direction(Port_B, MISO_PIN, Input);
  DIO_VoidSet_Pin_Direction(Port_B, SS_PIN, Input);

  DIO_VoidSet_Pin_Value(Port_B, SS_PIN, High);
  DIO_VoidSet_Port_Direction(Port_C, Output);
  LCD_VidInit();
  SPI_VidInit();
  u8 DATA = 0;
  while (1)
  {
    DATA = SPI_u8Transceive(10);
    LCD_VidSendNumber((f64)DATA);
    _delay_ms(50);
    LCD_VidClearDisplay();
  }
}
