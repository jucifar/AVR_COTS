#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_init.h"
#include "SPI_private.h"
#include "SPI_config.h"
#include "SPI_init.h"

static u8 *Copy_u8ReceivedDataPtr = NULL;
static void (*USART_pvCallBackSPI)(void) = NULL;
void SPI_VidInit(void)
{
  /*C LEAR SPCR REGISTER */
  SPCR &= SPI_CLEAR_SPCR_REGISTER;

  /* Select The SPI Mode */
#if SPI_MODE_SELECT == SPI_MASTER_MODE
  SET_BIT(SPCR, SPCR_MSTR);
#elif SPI_MODE_SELECT == SPI_SLAVE_MODE
  CLEAR_BIT(SPCR, SPCR_MSTR);
#endif

  /* Enable SPI Interrupt */
#if SPI_INTERRUPT_STATUS == ENABLE_SPI_INTERRUPT
  SET_BIT(SPCR, SPCR_SPIE);
#elif SPI_INTERRUPT_STATUS == DISABLE_SPI_INTERRUPT
  CLEAR_BIT(SPCR, SPCR_SPIE);
#endif

  /* DATA ORDER TRANSMIT FIRST */
#if DATA_ORDER_TRANSMIT_FIRST == DATA_ORDER_LSB_FIRST
  SET_BIT(SPCR, SPCR_DORD);
#elif DATA_ORDER_TRANSMIT_FIRST == DATA_ORDER_MSB_FIRST
  CLEAR_BIT(SPCR, SPCR_DORD);
#endif

  /* Clock polarity Idle Status Select */
#if CLOCK_POLARITY_IDLE_STATUS == CLOCK_POLARITY_IDLE_HIGH
  SET_BIT(SPCR, SPCR_CPOL);
#elif CLOCK_POLARITY_IDLE_STATUS == CLOCK_POLARITY_IDLE_LOW
  CLEAR_BIT(SPCR, SPCR_CPOL);
#endif

  /**/
#if CLOCK_PHASE_LEADING_ACTION == CLOCK_PHASE_SETUP_ON_LEADING
  SET_BIT(SPCR, SPCR_CPHA);
#elif CLOCK_PHASE_LEADING_ACTION == CLOCK_PHASE_SAMPLE_ON_LEADING
  CLEAR_BIT(SPCR, SPCR_CPHA);
#endif

  /* SET PreScaller */
  SPCR |= MASTER_SPI_CLOCK_RATE;
#if MASTER_SPI_CLOCK_RATE > 3
  SET_BIT(SPSR, SPSR_SPI2X);
#endif

/* Enable SPI */
#if SPI_STATUS == ENABLE_SPI
  SET_BIT(SPCR, SPCR_SPE);
#elif SPI_STATUS == DISABLE_SPI
  CLEAR_BIT(SPCR, SPCR_SPE);
#endif
}

u8 SPI_u8TransceiveSynchronous(u8 *Copy_u8ReceivedData, u8 Copy_u8SentData)
{
  u8 Local_u8ErrorStatus = OK;
  if (Copy_u8ReceivedData == NULL)
  {
    Local_u8ErrorStatus = NULL_POINTER;
  }
  *Copy_u8ReceivedData = SPDR;
  SPDR = Copy_u8SentData;
  while (GET_BIT(SPSR, SPSR_SPIF) == 0)
    ;
  return Local_u8ErrorStatus;
}

u8 SPI_u8TransceiveAsynchronous(u8 *Copy_u8ReceivedData, u8 Copy_u8SentData, void (*Copy_pvCallBackFunc)(void))
{
  u8 Local_u8ErrorStatus = OK;
  if (Copy_pvCallBackFunc == NULL || Copy_u8ReceivedData == NULL)
  {
    Local_u8ErrorStatus = NULL_POINTER;
  }
  USART_pvCallBackSPI = Copy_pvCallBackFunc;
  Copy_u8ReceivedDataPtr = Copy_u8ReceivedData;

  *Copy_u8ReceivedData = SPDR;
  SPDR = Copy_u8SentData;

  SET_BIT(SPCR, SPCR_SPIE);

  return Local_u8ErrorStatus;
}

void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{
  *Copy_u8ReceivedDataPtr = SPDR;
  CLEAR_BIT(SPCR, SPCR_SPIE);
}