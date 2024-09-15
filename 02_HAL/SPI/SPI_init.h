#ifndef SPI_INIT_H
#define UART_INIT_H

#define SPI_PORT Port_B
#define SS_PIN Pin_4
#define MOSI_PIN Pin_5
#define MISO_PIN Pin_6
#define SCK_PIN Pin_7

void SPI_VidInit(void);
u8 SPI_u8TransceiveSynchronous(u8 *Copy_u8ReceivedData, u8 Copy_u8SentData);
u8 SPI_u8TransceiveAsynchronous(u8 *Copy_u8ReceivedData, u8 Copy_u8SentData);

#endif
