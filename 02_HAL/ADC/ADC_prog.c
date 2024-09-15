#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_init.h"
#include "ADC_config.h"
#include "ADC_private.h"
#include "ADC_init.h"

static u16 *ADC_pu16Reading = NULL;
static void (*ADC_pvCallBackNotificationFunction)(u16) = NULL;
static u8 ADC_u8BusyState = IDLE;

/* Chain Conversion Global */
static void (*ADC_pvCallBackNotificationFunctionChain)(void) = NULL;
static u8 ADC_u8Chain_Size;
static u16 *ADC_u16Chain_Result_Arr = NULL;
static u8 *ADC_u8Channel_Ids_Arr = NULL;
static u8 ADC_u8Chain_Id;
static u8 ADC_u8Chain_Flag = 0;
static u8 ADC_u8ChainConversionIndex = 0;
static u8 ACD_u8ISR_SOURCE = NONE;
/* ------------------ */

void ADC_VidInit(void)
{
  ADMUX &= CLEAR_REFERENCE_SELECTION;
  ADMUX |= ADC_REFERENCE_SELECTION;
#if ADJUST == RIGHT
  CLEAR_BIT(ADMUX, ADMUX_ADLAR);
#elif ADJUST == LEFT
  SET_BIT(ADMUX, ADMUX_ADLAR);
#endif
  ADCSRA &= CLEAR_SCALAR;
  ADCSRA |= PRE_SCALAR_VALUE;
#if AUTO_TRIGGER == ENABLE_AUTO_TRIGGER
  /*SET AUTO TRIGGER SOURCE*/
  /* CLEAR SFIOR */
  SFIOR &= CLEAR_SFIOR;
  /* SET   SFIOR */
  SFIOR |= (AUTO_TRIGGER_SOU * 32);

  /* SET AUTO TRIGGER CHANNEL */
  ADMUX &= CLEAR;
  ADMUX |= AUTO_TRIGGER_CHANNEL;
  /* Start first conversion */
  SET_BIT(ADCSRA, ADCSRA_ADSC);
#endif
  /*ENABLE ADC*/
  SET_BIT(ADCSRA, ADCSRA_ADEN);
}

u8 ADC_u8StartConversionSynchronous(u8 copy_u8channel, u16 *copy_pu16Reading)
{
  u8 Local_u8ErrorState = OK;
  if (ADC_u8BusyState == IDLE)
  {
    /* Set ADC Flag To BUSY */
    ADC_u8BusyState = BUSY;

    u32 Local_u32Counter = 0;
    if (copy_pu16Reading == NULL)
    {
      Local_u8ErrorState = NULL_POINTER;
    }
    else if (copy_u8channel > 32)
    {
      Local_u8ErrorState = NOK;
    }
    else
    {
      /* Select Channel */
      ADMUX &= CLEAR;
      ADMUX |= copy_u8channel;
      /* Start Conversion */
      SET_BIT(ADCSRA, ADCSRA_ADSC);
      /* Wait until the Conversion finish */
      while ((GET_BIT(ADCSRA, ADCSRA_ADIF) == 0) && ((Local_u32Counter) != ADC_U32TIMEOUT))
      {
        Local_u32Counter++;
      }
      if (Local_u32Counter == ADC_U32TIMEOUT)
      {
        /* Loob is broken because time out is reached */
        Local_u8ErrorState = NOK;
      }
      else
      {
        /* CLEAR FLAG */
        SET_BIT(ADCSRA, ADCSRA_ADIF);
/* Return Value */
#if RESOLUTION == BIT_10
#if ADJUST == RIGHT
        *copy_pu16Reading = (ADCL);
#elif ADJUST == LEFT
        *copy_pu16Reading = (ADCL >> 6);
#endif

#elif RESOLUTION == BIT_8
#if ADJUST == RIGHT
        *copy_pu16Reading = (ADCL) & (0x00FF);
#elif ADJUST == LEFT
        *copy_pu16Reading = (ADCH * 4);
#endif
#endif
        /* Return ADC Flag To IDLE */
        ADC_u8BusyState = IDLE;
      }
    }
  }
  else
  {
    Local_u8ErrorState = BUSY_FUNC;
  }
  return Local_u8ErrorState;
}

u8 ADC_u8StartConversionAsynchronous(u8 copy_u8channel, u16 *copy_pu16Reading, void (*copy_pvNotificationFunction)(u16))
{
  u8 Local_u8ErrorState = OK;

  if (ADC_u8BusyState == IDLE)
  {
    if (copy_pu16Reading == NULL || copy_pvNotificationFunction == NULL)
    {
      Local_u8ErrorState = NULL_POINTER;
    }
    else
    {

      /*Set The ADC Flag To Busy */
      Local_u8ErrorState = BUSY;
      /* Set ISR source Single Channel Asynchronous */
      ACD_u8ISR_SOURCE = SINGLE_CHANNEL_ASYNC;
      /*Initialize The CallBack Notification Function Globally*/
      ADC_pvCallBackNotificationFunction = copy_pvNotificationFunction;

      /*Initialize The Reading Variable Globally*/
      ADC_pu16Reading = copy_pu16Reading;

      /* Clear ADMUX */
      ADMUX &= CLEAR;

      /* Select Channel */
      ADMUX |= copy_u8channel;

      /* Start Conversion */
      SET_BIT(ADCSRA, ADCSRA_ADSC);

      /* Enable ADC Interrupt */
      SET_BIT(ADCSRA, ADCSRA_ADIE);
    }
  }
  else
  {
    Local_u8ErrorState = BUSY_FUNC;
  }
  return Local_u8ErrorState;
}

u8 ADC_StartChainConversion(ADC_CHAIN *Copy_ADC_CHAIN)
{

  u8 Local_u8ErrorState = OK;
  if (Copy_ADC_CHAIN == NULL)
  {
    Local_u8ErrorState = NULL_POINTER;
  }
  else
  {
    if (ADC_u8BusyState == IDLE)
    {
      /*Set The ADC Flag To Busy */
      ADC_u8BusyState = BUSY;
      /* Set ISR source to Chain Asynchronous */
      ACD_u8ISR_SOURCE = CHAIN_ASYNC;
      /* Initialize The chain Id Globally  */
      ADC_u8Chain_Id = Copy_ADC_CHAIN->CHAIN_ID;
      /* Initialize The Size Globally  */
      ADC_u8Chain_Size = Copy_ADC_CHAIN->SIZE;
      /* Initialize The Channels Id Globally */
      ADC_u8Channel_Ids_Arr = Copy_ADC_CHAIN->Channel_Ids;
      /* Initialize The Reading Array Globally */
      ADC_u16Chain_Result_Arr = Copy_ADC_CHAIN->RESULTS;
      /* Initialize The CallBack Notification Function Globally */
      ADC_pvCallBackNotificationFunctionChain = Copy_ADC_CHAIN->NOTIFICATION_FUNCTION;
      ADC_u8Chain_Flag = TRUE;
      ADC_u8ChainConversionIndex = 0;

      /* Clear ADMUX */
      ADMUX &= CLEAR;

      /* Select Channel */
      ADMUX |= ADC_u8Channel_Ids_Arr[ADC_u8ChainConversionIndex];

      /* Start Conversion */
      SET_BIT(ADCSRA, ADCSRA_ADSC);

      /* Enable ADC Interrupt */
      SET_BIT(ADCSRA, ADCSRA_ADIE);
    }
    else
    {
      Local_u8ErrorState = BUSY_FUNC;
    }
  }
  return Local_u8ErrorState;
}

/* ISR OF ADC Conversion Complete Interrupt */
void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
  if (ACD_u8ISR_SOURCE == CHAIN_ASYNC)
  {

#if RESOLUTION == BIT_10
#if ADJUST == RIGHT
    ADC_u16Chain_Result_Arr[ADC_u8ChainConversionIndex] = (ADCL);
#elif ADJUST == LEFT
    ADC_u16Chain_Result_Arr[ADC_u8ChainConversionIndex] = (ADCL >> 6);
#endif

#elif RESOLUTION == BIT_8
#if ADJUST == RIGHT
    ADC_u16Chain_Result_Arr[ADC_u8ChainConversionIndex] = (ADCL) & (0x00FF);
#elif ADJUST == LEFT
    ADC_u16Chain_Result_Arr[ADC_u8ChainConversionIndex] = (ADCH * 4);
#endif
#endif

    ADC_u8ChainConversionIndex++;
    if (ADC_u8ChainConversionIndex == ADC_u8Chain_Size)
    {
      ADC_u8BusyState = IDLE;
      ADC_pvCallBackNotificationFunctionChain();
      /* Close ADC Conversion Complete Interrupt */
      CLEAR_BIT(ADCSRA, ADCSRA_ADIE);
    }
    else
    {
      /* Clear ADMUX */
      ADMUX &= CLEAR;

      /* Select Channel */
      ADMUX |= ADC_u8Channel_Ids_Arr[ADC_u8ChainConversionIndex];

      /* Start Conversion */
      SET_BIT(ADCSRA, ADCSRA_ADSC);

      /* Enable ADC Interrupt */
      SET_BIT(ADCSRA, ADCSRA_ADIE);
    }
  }
  else if (ACD_u8ISR_SOURCE == SINGLE_CHANNEL_ASYNC)
  {

/* Read ADC Result */
#if RESOLUTION == BIT_10
#if ADJUST == RIGHT
    *ADC_pu16Reading = (ADCL);
#elif ADJUST == LEFT
    *ADC_pu16Reading = (ADCL >> 6);
#endif

#elif RESOLUTION == BIT_8
#if ADJUST == RIGHT
    *ADC_pu16Reading = (ADCL) & (0x00FF);
#elif ADJUST == LEFT
    *ADC_pu16Reading = (ADCH * 4);
#endif
#endif

    /* Reset ADC Flag */
    ADC_u8BusyState = IDLE;
    /* Run CallBack Notification Function */
    ADC_pvCallBackNotificationFunction();
    /* Close ADC Conversion Complete Interrupt */
    CLEAR_BIT(ADCSRA, ADCSRA_ADIE);
  }
}