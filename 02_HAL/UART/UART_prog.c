#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_init.h"

#include "UART_private.h"

#include "UART_config.h"
#include "UART_init.h"
#include <util/delay.h>

static USART_INTERUPT_SOURCE = 0;
static u8 USART_Busy_Status = IDLE;
static void (*USART_pvCallBackFunc)(void) = NULL;
static u8 USART_u8BufferSize = 0;

/// send
static u16 USART_u16SentData = 0;
static u8 Copy_u8SendCharIndex = 0;
static u8 *Copy_u8SendStrPtr = NULL;
static u16 *Copy_u16SendBufferPtr = NULL;

// Receive
static u8 Copy_u8ReceiveCharIndex = 0;
static u16 *Copy_u16ReceivedDataptr = NULL;
static u8 *Copy_u16ReceivedStringPtr = NULL;
static u16 *Copy_u16ReceivedBufferPtr = NULL;

void USART_VidInit(void)
{
  u8 LOCAL_UCSRC = 0;
  u16 LOCAL_UBRR = 0;
  f32 UBRR_CALC = 0;
/* ENABLE DOUBLE SPEED and Clock polarity */
#if USART_MODE_SELECT == USART_ENABLE_ASYNCHRONOUS

#if USART_DOUBLE_SPEED_MODE == USART_ENABLE_DOUBLE_SPEED
  SET_BIT(UCSRA, UCSRA_U2X);
  UBRR_CALC = ((f32)((f32)SYSTEM_OSCILLATOR_FREQUENCY / (8 * (f32)USART_BAUD_RATE)) - 1);
#elif USART_DOUBLE_SPEED_MODE == USART_DISABLE_DOUBLE_SPEED
  CLEAR_BIT(UCSRA, UCSRA_U2X);
  UBRR_CALC = ((f32)((f32)SYSTEM_OSCILLATOR_FREQUENCY / (16 * (f32)USART_BAUD_RATE)) - 1);

#endif

#elif USART_MODE_SELECT == USART_ENABLE_SYNCHRONOUS
  CLEAR_BIT(UCSRA, UCSRA_U2X);
  UBRR_CALC = ((f32)((f32)SYSTEM_OSCILLATOR_FREQUENCY / (2 * (f32)USART_BAUD_RATE)) - 1);

#if USART_CLOCK_POLARITY == USART_TRANSMITTED_DATA_CHANGED_IN_RISING
  CLEAR_BIT(LOCAL_UCSRC, UCSRC_UCPOL);
#elif USART_CLOCK_POLARITY == USART_TRANSMITTED_DATA_CHANGED_IN_FALLING
  SET_BIT(LOCAL_UCSRC, UCSRC_UCPOL);
#endif

#endif

/* Enable MULTI PROCESSOR Mode */
#if USART_MULTI_PROCESSOR_MODE == USART_ENABLE_MULTI_PROCESSOR_MODE
  SET_BIT(UCSRA, UCSRA_MPCM);
#elif USART_MULTI_PROCESSOR_MODE == USART_DISABLE_MULTI_PROCESSOR_MODE
  CLEAR_BIT(UCSRA, UCSRA_MPCM);
#endif

/* Enable UART_RX_COMPLETE_INTERRUPT */
#if USART_RX_COMPLETE_INTERRUPT == USART_ENABLE_RX_COMPLETE_INTERRUPT
  SET_BIT(UCSRB, UCSRB_RXCIE);
#elif USART_RX_COMPLETE_INTERRUPT == USART_DISABLE_RX_COMPLETE_INTERRUPT
  CLEAR_BIT(UCSRB, UCSRB_RXCIE);
#endif

/*Enable UART_TX_COMPLETE_INTERRUPT*/
#if USART_TX_COMPLETE_INTERRUPT == USART_ENABLE_TX_COMPLETE_INTERRUPT
  SET_BIT(UCSRB, UCSRB_TXCIE);
#elif USART_TX_COMPLETE_INTERRUPT == USART_DISABLE_TX_COMPLETE_INTERRUPT
  CLEAR_BIT(UCSRB, UCSRB_TXCIE);
#endif

/*Enable UART_REGISTER_EMPTY_INTERRUPT*/
#if USART_REGISTER_EMPTY_INTERRUPT == USART_ENABLE_REGISTER_EMPTY_INTERRUPT
  SET_BIT(UCSRB, UCSRB_UDRIE);
#elif USART_REGISTER_EMPTY_INTERRUPT == USART_DISABLE_REGISTER_EMPTY_INTERRUPT
  CLEAR_BIT(UCSRB, UCSRB_UDRIE);
#endif

/* SET  UCSRB_UCSZ2 WHEN NINE BIT TRANSFER*/
#if DATA_AMOUNT == USART_NINE_BIT
  SET_BIT(UCSRB, UCSRB_UCSZ2);
#else
  CLEAR_BIT(UCSRB, UCSRB_UCSZ2);
#endif

  SET_BIT(LOCAL_UCSRC, UCSRC_URSEL);
#if USART_MODE_SELECT == USART_ENABLE_ASYNCHRONOUS
  CLEAR_BIT(LOCAL_UCSRC, UCSRC_UMSEL);
#elif USART_MODE_SELECT == USART_ENABLE_SYNCHRONOUS
  SET_BIT(LOCAL_UCSRC, UCSRC_UMSEL);
#endif

/*Parity check bit*/
#if USART_PARITY_CHECK_MODE == USART_DISABLE_PARITY
  CLEAR_BIT(LOCAL_UCSRC, UCSRC_UPM0);
  CLEAR_BIT(LOCAL_UCSRC, UCSRC_UPM1);

#elif USART_PARITY_CHECK_MODE == USART_EVEN_PARITY
  CLEAR_BIT(LOCAL_UCSRC, UCSRC_UPM0);
  SET_BIT(LOCAL_UCSRC, UCSRC_UPM1);

#elif USART_PARITY_CHECK_MODE == USART_ODD_PARITY
  SET_BIT(LOCAL_UCSRC, UCSRC_UPM0);
  SET_BIT(LOCAL_UCSRC, UCSRC_UPM1);
#endif

/*Number of Stop bits*/
#if USART_STOP_BIT == USART_ONE_STOP_BIT
  CLEAR_BIT(LOCAL_UCSRC, UCSRC_USBS);

#elif USART_STOP_BIT == USART_TWO_STOP_BIT
  SET_BIT(LOCAL_UCSRC, UCSRC_USBS);

#endif

  /*number of data transfer || receive*/
  LOCAL_UCSRC |= ((DATA_AMOUNT << 1));

  UCSRC = LOCAL_UCSRC;
  LOCAL_UBRR = (u16)UBRR_CALC;
  UBRRL = (u8)(LOCAL_UBRR & CLEAR_LEFT_UBRR_CALC);
  UBRRH = (u8)((LOCAL_UBRR & CLEAR_RIGHT_UBRR_CALC) >> 8);

/*Enable UART_RECEIVER_STATUS*/
#if USART_RECEIVER_STATUS == USART_ENABLE_RECEIVER
  SET_BIT(UCSRB, UCSRB_RXEN);

#elif USART_RECEIVER_STATUS == USART_DISABLE_RECEIVER
  CLEAR_BIT(UCSRB, UCSRB_RXEN);
#endif

/*Enable UART_TRANSMITTER_STATUS*/
#if USART_TRANSMITTER_STATUS == USART_ENABLE_TRANSMITTER
  SET_BIT(UCSRB, UCSRB_TXEN);

#elif USART_TRANSMITTER_STATUS == USART_DISABLE_TRANSMITTER
  CLEAR_BIT(UCSRB, UCSRB_TXEN);
#endif
}

// Synchronous mode Functions

u8 USART_u8SendDataSynchronous(u16 Copy_u16Data)
{
  u32 Local_u8TimeOut = 0;
  u8 Local_u8ErrorStatus = OK;
  if (Copy_u16Data > MAXIMUM_SENT_DATA)
  {
    Local_u8ErrorStatus = USART_MAXDATA_ERROR_FLAG;
  }

  if (USART_Busy_Status == IDLE)
  {
    USART_Busy_Status = BUSY;
    while ((GET_BIT(UCSRA, UCSRA_UDRE) == 0) && (Local_u8TimeOut < USART_TIME_OUT_MAX))
    {
      Local_u8TimeOut++;
    }
    if (Local_u8TimeOut == USART_TIME_OUT_MAX)
    {
      Local_u8ErrorStatus = USART_TIME_OUT_FLAG;
    }
    else
    {
      /*clear transmit complete flag*/
      SET_BIT(UCSRA, UCSRA_UDRE);
      /*Send Data*/
#if DATA_AMOUNT == USART_NINE_BIT
      UDR = (u8)Copy_u16Data;
      SET_BIT(UCSRB, UCSRB_TXB8);
      USART_Sending_Busy_Status = IDLE;
#elif DATA_AMOUNT < USART_NINE_BIT
      UDR = (u8)Copy_u16Data;
      USART_Busy_Status = IDLE;
#endif
    }
  }
  else
  {
    Local_u8ErrorStatus = BUSY_FUNC;
  }
  return Local_u8ErrorStatus;
}

u8 USART_u8ReceiveDataSynchronous(u16 *Copy_u16Data)
{
  u16 result;
  u8 Local_u8ErrorStatus = OK;

  while (GET_BIT(UCSRA, UCSRA_RXC) == 0)
    ;

#if USART_PARITY_CHECK_MODE != USART_DISABLE_PARITY
  if (GET_BIT(UCSRA, UCSRA_PE) == 1)
    Local_u8ErrorStatus = USART_PARITY_ERROR_DETECTED;
#endif

#if DATA_AMOUNT == USART_NINE_BIT
  result |= ((UCSRB & (1 << UCSRB_RXB8)) << 7);
#endif
  result |= UDR;
  *(Copy_u16Data) = result;

  return Local_u8ErrorStatus;
}

u8 USART_u8SendStringSynchronous(const char *Copy_u16StrPtr)
{
  u8 Local_u8ErrorStatus = OK;
  if (Copy_u16StrPtr == NULL)
  {
    Local_u8ErrorStatus = NULL_POINTER;
  }
  else
  {
    while (*Copy_u16StrPtr != '\0')
    {
      Local_u8ErrorStatus = USART_u8SendDataSynchronous((u16)*Copy_u16StrPtr++);
    }
    Local_u8ErrorStatus = USART_u8SendDataSynchronous((u16)*Copy_u16StrPtr++);
  }
  return Local_u8ErrorStatus;
}

u8 USART_u8ReceiveStringSynchronous(const u8 *Copy_uStringPtr)
{
  u8 Local_u8ErrorStatus = OK;
  u8 Local_u8Counter = 0;
  if (Copy_uStringPtr == NULL)
  {
    Local_u8ErrorStatus = NULL_POINTER;
  }
  while (1)
  {
    /*Receive string in Array*/
    USART_u8ReceiveDataSynchronous(&Copy_uStringPtr[Local_u8Counter++]);
    if (Copy_uStringPtr[Local_u8Counter - 1] == '\0')
      break;
  }
  return Local_u8ErrorStatus;
}

u8 USART_u8ReceiveBufferSynchronous(const u16 *Copy_u16BufferPtr, u8 Copy_u8BufferSize)
{
  u8 Local_u8ErrorStatus = OK;
  u8 Local_u8Counter = 0;
  if (Copy_u16BufferPtr == NULL)
  {
    Local_u8ErrorStatus = NULL_POINTER;
  }
  for (Local_u8Counter = 0; Local_u8Counter < Copy_u8BufferSize; Local_u8Counter++)
  {
    /*Receive Buffer in Array*/
    USART_u8ReceiveDataSynchronous(&Copy_u16BufferPtr[Local_u8Counter]);
  }
  return Local_u8ErrorStatus;
}

// Asynchronous mode Functions

u8 USART_u8SendDataAsynchronous(u16 Copy_u16Data, void (*USART_pvCallBackNotificationFunction)(void))
{
  u8 Local_u8ErrorStatus = OK;
  if (USART_Busy_Status == IDLE)
  {
    if (USART_pvCallBackNotificationFunction == NULL)
    {
      Local_u8ErrorStatus = NULL_POINTER;
    }
    else
    {
      /*Busy Waiting For Data Register Empty*/
      USART_Busy_Status = BUSY;
      /*Configure ISR Source As Sending Character*/
      USART_INTERUPT_SOURCE = USART_INTERUPT_SOURCE_SEND_DATA_ASYNC;
      USART_pvCallBackFunc = USART_pvCallBackNotificationFunction;
      USART_u16SentData = Copy_u16Data;
      /*USART Data Register Empty Interrupt Enable*/
      SET_BIT(UCSRB, UCSRB_UDRIE);
    }
  }
  return Local_u8ErrorStatus;
}

u8 USART_u8SendBufferAsynchronous(const u16 *Copy_u16Data, u8 Copy_u8Buffer_Size, void (*USART_pvCallBackNotificationFunction)(void))
{
  u8 Local_u8ErrorStatus = 0;
  if (USART_Busy_Status == IDLE)
  {
    if ((Copy_u16Data == NULL) || (USART_pvCallBackNotificationFunction == NULL))
    {
      Local_u8ErrorStatus = NULL_POINTER;
    }
    else
    {
      /*Make USART Busy*/
      USART_Busy_Status = BUSY;
      /*Configure ISR Source As Sending String*/
      USART_INTERUPT_SOURCE = USART_INTERUPT_SOURCE_SEND_BUFFER_ASYNC;
      /*Initialize the variables & CallBack Notification Function Globally*/
      Copy_u16SendBufferPtr = Copy_u16Data;
      USART_pvCallBackFunc = USART_pvCallBackNotificationFunction;
      Copy_u8SendCharIndex = 0;
      USART_u8BufferSize = Copy_u8Buffer_Size;
      /*USART Data Register Empty Interrupt Enable*/
      SET_BIT(UCSRB, UCSRB_UDRIE);
    }
  }
  else
  {
    Local_u8ErrorStatus = BUSY_FUNC;
  }
  return Local_u8ErrorStatus;
}

u8 USART_u8SendStringAsynchronous(const u8 *Copy_u8StrPtr, void (*USART_pvCallBackNotificationFunction)(void))
{
  u8 Local_u8ErrorStatus = 0;
  if (USART_Busy_Status == IDLE)
  {
    if ((Copy_u8StrPtr == NULL) || (USART_pvCallBackNotificationFunction == NULL))
    {
      Local_u8ErrorStatus = NULL_POINTER;
    }
    else
    {
      /*Make USART Busy*/
      USART_Busy_Status = BUSY;
      /*Configure ISR Source As Sending String*/
      USART_INTERUPT_SOURCE = USART_INTERUPT_SOURCE_SEND_STRING_ASYNC;
      /*Initialize the variables & CallBack Notification Function Globally*/
      Copy_u8SendStrPtr = Copy_u8StrPtr;
      USART_pvCallBackFunc = USART_pvCallBackNotificationFunction;
      Copy_u8SendCharIndex = 0;
      /*USART Data Register Empty Interrupt Enable*/
      SET_BIT(UCSRB, UCSRB_UDRIE);
    }
  }
  else
  {
    Local_u8ErrorStatus = BUSY_FUNC;
  }
  return Local_u8ErrorStatus;
}

u8 USART_u8ReceiveDataAsynchronous(u16 *Copy_u16DataPtr, void (*USART_pvCallBackNotificationFunction)(void))
{
  u8 Local_u8StateError = OK;
  if (USART_Busy_Status == IDLE)
  {
    if ((Copy_u16DataPtr == NULL) || (USART_pvCallBackNotificationFunction == NULL))
    {
      Local_u8StateError = NULL_POINTER;
    }
    else
    {
      /*Make USART Busy*/
      USART_Busy_Status = BUSY;
      /*Configure ISR Source As Receiving Character*/
      USART_INTERUPT_SOURCE = USART_RXC_INTERUPT_SOURCE_RECEIVE_DATA_ASYNC;
      Copy_u16ReceivedDataptr = Copy_u16DataPtr;
      USART_pvCallBackFunc = USART_pvCallBackNotificationFunction;
      /*Receive Complete Interrupt Enable*/
      SET_BIT(UCSRB, UCSRB_RXCIE);
    }
  }
  else
  {
    Local_u8StateError = BUSY_FUNC;
  }
  return Local_u8StateError;
}

u8 USART_u8ReceiveStringAsynchronous(u8 *Copy_u8StrPtr, u8 Copy_u8Buffer_Size, void (*USART_pvCallBackNotificationFunction)(void))
{
  u8 Local_u8StateError = OK;
  if (USART_Busy_Status == IDLE)
  {
    if ((Copy_u8StrPtr == NULL) || (USART_pvCallBackNotificationFunction == NULL))
    {
      Local_u8StateError = NULL_POINTER;
    }
    else
    {
      /*Make USART Busy*/
      USART_Busy_Status = BUSY;
      /*Configure ISR Source As Receiving String*/
      USART_INTERUPT_SOURCE = USART_RXC_INTERUPT_SOURCE_RECEIVE_STRING_ASYNC;
      /*Initialize the variables & CallBack Notification Function Globally*/
      Copy_u8ReceiveCharIndex = 0;
      Copy_u16ReceivedBufferPtr = Copy_u8StrPtr;
      USART_pvCallBackFunc = USART_pvCallBackNotificationFunction;
      USART_u8BufferSize = Copy_u8Buffer_Size;
      /*Receive Complete Interrupt Enable*/
      SET_BIT(UCSRB, UCSRB_RXCIE);
    }
  }
  else
  {
    Local_u8StateError = BUSY_FUNC;
  }
  return Local_u8StateError;
}

u8 USART_u8ReceiveBufferAsynchronous(u8 *Copy_u16BufferPtr, u8 Copy_u8Buffer_Size, void (*USART_pvCallBackNotificationFunction)(void))
{

  u8 Local_u8StateError = OK;
  if (USART_Busy_Status == IDLE)
  {
    if ((Copy_u16BufferPtr == NULL) || (USART_pvCallBackNotificationFunction == NULL))
    {
      Local_u8StateError = NULL_POINTER;
    }
    else
    {
      /*Make USART Busy*/
      USART_Busy_Status = BUSY;
      /*Configure ISR Source As Receiving String*/
      USART_INTERUPT_SOURCE = USART_RXC_INTERUPT_SOURCE_RECEIVE_BUFFER_ASYNC;
      /*Initialize the variables & CallBack Notification Function Globally*/
      Copy_u8ReceiveCharIndex = 0;
      Copy_u16ReceivedBufferPtr = Copy_u16BufferPtr;
      USART_pvCallBackFunc = USART_pvCallBackNotificationFunction;
      USART_u8BufferSize = Copy_u8Buffer_Size;
      /*Receive Complete Interrupt Enable*/
      SET_BIT(UCSRB, UCSRB_RXCIE);
    }
  }
  else
  {
    Local_u8StateError = BUSY_FUNC;
  }
  return Local_u8StateError;
}

// *********************************************************************

/*  USART Data Register Empty  */
void __vector_14(void) __attribute__((signal));
void __vector_14(void)
{
  if (USART_INTERUPT_SOURCE == USART_INTERUPT_SOURCE_SEND_DATA_ASYNC)
  {
    /*Send Data*/
#if DATA_AMOUNT == USART_NINE_BIT
    UDR = (u8)USART_u16SentData;
    UCSRB |= (USART_u16SentData >> 8);
#elif DATA_AMOUNT < USART_NINE_BIT
    UDR = (u8)USART_u16SentData;
#endif
    /*Make USART Busy State Idle*/
    USART_Busy_Status = IDLE;
    /*Disable USART Data Register Empty Interrupt*/
    CLEAR_BIT(UCSRB, UCSRB_UDRIE);
    /*Invoke the call Back Notification*/
    USART_pvCallBackFunc();
  }

  else if (USART_INTERUPT_SOURCE == USART_INTERUPT_SOURCE_SEND_STRING_ASYNC)
  {

    UDR = Copy_u8SendStrPtr[Copy_u8SendCharIndex];
    Copy_u8SendCharIndex++;
    if (Copy_u8SendStrPtr[Copy_u8SendCharIndex] == '\0')
    {
      /*Make USART Busy State Idle*/
      USART_Busy_Status = IDLE;
      /*Disable USART Data Register Empty Interrupt*/
      CLEAR_BIT(UCSRB, UCSRB_UDRIE);
      /*Invoke the call Back Notification*/
      USART_pvCallBackFunc();
    }
  }
  else if (USART_INTERUPT_SOURCE == USART_INTERUPT_SOURCE_SEND_BUFFER_ASYNC)
  {
#if DATA_AMOUNT == USART_NINE_BIT
    UDR = (u8)Copy_u16SendBufferPtr[Copy_u8SendCharIndex];
    UCSRB |= (USART_u16SentData >> 8);
#elif DATA_AMOUNT < USART_NINE_BIT
    UDR = (u8)Copy_u16SendBufferPtr[Copy_u8SendCharIndex];
#endif
    Copy_u8SendCharIndex++;
    if (Copy_u8SendCharIndex > USART_u8BufferSize)
    {
      /*Make USART Busy State Idle*/
      USART_Busy_Status = IDLE;
      /*Disable USART Data Register Empty Interrupt*/
      CLEAR_BIT(UCSRB, UCSRB_UDRIE);
      /*Invoke the call Back Notification*/
      USART_pvCallBackFunc();
    }
  }
}
/* USART, Rx Complete */
void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{
  if (USART_INTERUPT_SOURCE == USART_RXC_INTERUPT_SOURCE_RECEIVE_DATA_ASYNC)
  {
    *Copy_u16ReceivedDataptr = UDR;
    /*Make USART Busy State Idle*/
    USART_Busy_Status = IDLE;
    /*Receive Complete Interrupt Disable*/
    CLEAR_BIT(UCSRB, UCSRB_RXCIE);
    /*Invoke the call Back Notification*/
    USART_pvCallBackFunc();
  }
  else if (USART_INTERUPT_SOURCE == USART_RXC_INTERUPT_SOURCE_RECEIVE_STRING_ASYNC)
  {
    Copy_u16ReceivedStringPtr[Copy_u8ReceiveCharIndex] = UDR;
    Copy_u8ReceiveCharIndex++;
    if (Copy_u8ReceiveCharIndex == USART_u8BufferSize)
    {
      USART_Busy_Status = IDLE;
      /*Receive Complete Interrupt Disable*/
      CLEAR_BIT(UCSRB, UCSRB_RXCIE);
      /*Invoke the call Back Notification*/
      USART_pvCallBackFunc();
    }
  }
  else if (USART_INTERUPT_SOURCE == USART_RXC_INTERUPT_SOURCE_RECEIVE_BUFFER_ASYNC)
  {
    Copy_u16ReceivedBufferPtr[Copy_u8ReceiveCharIndex] = UDR;
    Copy_u8ReceiveCharIndex++;
    if (Copy_u8ReceiveCharIndex == USART_u8BufferSize)
    {
      USART_Busy_Status = IDLE;
      /*Receive Complete Interrupt Disable*/
      CLEAR_BIT(UCSRB, UCSRB_RXCIE);
      /*Invoke the call Back Notification*/
      USART_pvCallBackFunc();
    }
  }
}