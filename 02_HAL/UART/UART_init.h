#ifndef UART_INIT_H
#define UART_INIT_H

void USART_VidInit(void);

u8 USART_u8SendDataSynchronous(u16 Copy_u16Data);
u8 USART_u8SendStringSynchronous(const char *Copy_u16Data);

u8 USART_u8SendDataAsynchronous(u16 Copy_u16Data, void (*USART_pvCallBackNotificationFunction)(void));
u8 USART_u8SendStringAsynchronous(const u8 *Copy_u8Data, void (*USART_pvCallBackNotificationFunction)(void));
u8 USART_u8SendBufferAsynchronous(const u16 *Copy_u16Data, u8 Copy_u8Buffer_Size, void (*USART_pvCallBackNotificationFunction)(void));

u8 USART_u8ReceiveDataSynchronous(u16 *Copy_u16Data);
u8 USART_u8ReceiveStringSynchronous(const u8 *Copy_uStringPtr);
u8 USART_u8ReceiveBufferSynchronous(const u16 *Copy_u16BufferPtr, u8 Copy_u8BufferSize);

u8 USART_u8ReceiveDataAsynchronous(u16 *Copy_u16DataPtr, void (*USART_pvCallBackNotificationFunction)(void));
u8 USART_u8ReceiveStringAsynchronous(u8 *Copy_u8StrPtr, u8 Copy_u8Buffer_Size, void (*USART_pvCallBackNotificationFunction)(void));
u8 USART_u8ReceiveBufferAsynchronous(u8 *Copy_u16BufferPtr, u8 Copy_u8Buffer_Size, void (*USART_pvCallBackNotificationFunction)(void));

u8 USART_u8SetCallBackForRxComplete(void (*Copy_pvCallBackFunc)(void));
u8 USART_u8SetCallBackForTxComplete(void (*Copy_pvCallBackFunc)(void));
u8 USART_u8SetCallBackForDataRegisterEmpty(void (*Copy_pvCallBackFunc)(void));

#endif
