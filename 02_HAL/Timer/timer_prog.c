#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_init.h"
#include "timer_private.h"
#include "timer_config.h"
#include "timer_init.h"

static void (*TIMER0_pvCallBackFunc1)(void) = NULL;
static void (*TIMER0_pvCallBackFunc2)(void) = NULL;

static void (*TIMER1_pvCallBackFunc1)(void) = NULL;
static void (*TIMER1_pvCallBackFunc2)(void) = NULL;
static void (*TIMER1_pvCallBackFunc3)(void) = NULL;
static void (*TIMER1_pvCallBackFunc4)(void) = NULL;

static void (*TIMER2_pvCallBackFunc1)(void) = NULL;
static void (*TIMER2_pvCallBackFunc2)(void) = NULL;

void TIMER1_VidInit_CTCMode(void)
{
  /* SET CTC WITH TOP OCR1A*/
  CLR_BIT(TCCR1A, TCCR1A_WGM10);
  CLR_BIT(TCCR1A, TCCR1A_WGM11);
  SET_BIT(TCCR1B, TCCR1B_WGM12);
  CLR_BIT(TCCR1B, TCCR1B_WGM13);
  /*SET OCR1A Pin in Normal Mode */
  CLR_BIT(TCCR1A, TCCR1A_COM1A0);
  CLR_BIT(TCCR1A, TCCR1A_COM1A1);
  /*TOP Value in OCR1A*/
  OCR1A = 500; // get time period 500 micro sec for one step

  /*SET Pre-scaler value divided by 8 */
  TCCR1B &= 0b11111000; // clear pre-scaler
  TCCR1B |= 2;
}

void TIMER1_VidInitFastPWM_WithNonInverting(void)
{
  /* SET FAST PWM WITH TOP ICR1*/
  CLR_BIT(TCCR1A, TCCR1A_WGM10);
  SET_BIT(TCCR1A, TCCR1A_WGM11);
  SET_BIT(TCCR1B, TCCR1B_WGM12);
  SET_BIT(TCCR1B, TCCR1B_WGM13);

  /*SET Non-Inverting Mode */

  SET_BIT(TCCR1A, TCCR1A_COM1A1);
  CLR_BIT(TCCR1A, TCCR1A_COM1A0);
  /*TOP Value in ICR1*/
  ICR1 = 10000; // get time period 2.5m sec for one step
  OCR1A = 5000; // duty 50%
  /*SET Pre-scaler value divided by 8 */
  TCCR1B &= 0b11111000; // clear pre-scaler
  TCCR1B |= 2;
}
void StepperMotor_Direction(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction)
{
  DIO_VidSetPinDirection(Copy_u8Port, Copy_u8Pin, Output);
  switch (Copy_u8Direction)
  {
  case 0:
    DIO_VidSetPinValue(Copy_u8Port, Copy_u8Pin, Low);
    break;
  case 1:
    DIO_VidSetPinValue(Copy_u8Port, Copy_u8Pin, High);
    break;
  }
}

void TIMER1_VidSetNumberOfSteps(u16 Copy_u8StepValue, u8 Copy_u8Port, u8 Copy_u8Pin)
{
  DIO_VidSetPinDirection(Copy_u8Port, Copy_u8Pin, Output);
  TIMER1_VidInit_CTCMode();
  for (u16 i = 0; i < Copy_u8StepValue; i++)
  {
    DIO_VidSetPinValue(Copy_u8Port, Copy_u8Pin, High);
    while (((TIFR >> TIFR_ICF1) & (0x01)) == 0)
      ;
    TIFR |= (1 << TIFR_ICF1);
    DIO_VidSetPinValue(Copy_u8Port, Copy_u8Pin, Low);
  }
}

void Timer0_VidInit(void)
{
  /* Clear Prev Mode and Compare Match Output Mode */
  TCCR0 &= TIMER_0_CLEAR_MODE;

/* Select MODE From Config */
#if TIMER_0_MODE == TIMER_0_NORMAL_MODE
  TCCR0 |= TIMER_0_NORMAL_MODE_SET;                    /*Set Normal Mode*/
  TCCR0 |= (TIMER_0_NON_PWM_COMPARE_OUTPUT_MODE << 4); /*Set Compare Output Mode*/
  TCNT0 = TIMER_0_PRELOAD_VALUE;                       /* Set PreLoad Value */
#elif TIMER_0_MODE == TIMER_0_PWM_PHASE_CORRECT_MODE
  TCCR0 |= TIMER_0_PWM_PHASE_CORRECT_MODE_SET;               /* SELECT PHASE CORRECT MODE */
  TCCR0 |= (TIMER_0_PHASE_CORRECT_COMPARE_OUTPUT_MODE << 4); /* Set Compare Output Mode */
  TCNT0 = TIMER_0_PRELOAD_VALUE;                             /* Set PreLoad Value */
  OCR0 = TIMER_0_COMPARE_MATCH_VALUE;                        /* Ser Compare Match Value */
#elif TIMER_0_MODE == TIMER_0_CTC_MODE
  TCCR0 |= TIMER_0_CTC_MODE_SET;                       /*Set CTC Mode*/
  TCCR0 |= (TIMER_0_NON_PWM_COMPARE_OUTPUT_MODE << 4); /* Set Compare Output Mode */
  TCNT0 = TIMER_0_PRELOAD_VALUE;                       /* Set PreLoad Value */
  OCR0 = TIMER_0_COMPARE_MATCH_VALUE;                  /* Ser Compare Match Value */
#elif TIMER_0_MODE == TIMER_0_FAST_PWM_MODE
  TCCR0 |= TIMER_0_FAST_PWM_MODE_SET;              /* Set Fast_PWM Mode */
  TCCR0 |= (TIMER_0_PWM_COMPARE_OUTPUT_MODE << 4); /* Set Compare Output Mode */
  TCNT0 = TIMER_0_PRELOAD_VALUE;                   /* Set PreLoad Value */
  OCR0 = TIMER_0_COMPARE_MATCH_VALUE;              /* Ser Compare Match Value */
#endif

/* Enable Compare Match Interrupt */
#if TIMER_0_COMPAREMATCH_INTERRUPT_STATUS == ENABLE_TIMER_0_COMPAREMATCH_INTERRUPT
  SET_BIT(TIMSK, TIMSK_OCIE0);
#elif TIMER_0_COMPAREMATCH_INTERRUPT_STATUS == DISABLE_TIMER_0_COMPAREMATCH_INTERRUPT
  CLEAR_BIT(TIMSK, TIMSK_OCIE0);
#endif

/* Enable OverFlow Interrupt */
#if TIMER_0_OVERFLOW_INTERRUPT_STATUS == ENABLE_TIMER_0_OVERFLOW_INTERRUPT
  SET_BIT(TIMSK, TIMSK_TOIE0);
#elif TIMER_0_OVERFLOW_INTERRUPT_STATUS == DISABLE_TIMER_0_OVERFLOW_INTERRUPT
  CLEAR_BIT(TIMSK, TIMSK_TOIE0);
#endif

  /* SELECT Prescaller */
  TCCR0 |= TIMER_0_PRE_SCALAR_VALUE;
}

void TIMER0_voidSetPreLoadValue(u8 Copy_u8PreLoadValue)
{
  TCNT0 = Copy_u8PreLoadValue; /* Set PreLoad Value */
}

void TIMER0_voidSetCompareMatchValue(u8 Copy_u8CompareMatchValue)
{

  OCR0 = Copy_u8CompareMatchValue;
}

void TIMER0_voidGenFastPWM(u8 Copy_u8Duty)
{
  f32 Local_f32Duty = (f32)Copy_u8Duty / 100;
#if TIMER_0_PWM_COMPARE_OUTPUT_MODE == CLEAR_OC0_ON_COMPARE_SET_OC0_ON_TOP
  OCR0 = 256 * Local_f32Duty;
#elif TIMER_0_PWM_COMPARE_OUTPUT_MODE == SET_OC0_ON_COMPARE_CLEAR_OC0_ON_TOP
  OCR0 = 1 - (256 * Local_f32Duty);

#endif
}

u8 Timer0_u8SetCallBackForCompareMatch(void (*Copy_pvCallBackFunc)(void))
{
  u8 Local_u8ErrorStatus = OK;
  if (Copy_pvCallBackFunc != NULL)
  {
    TIMER0_pvCallBackFunc1 = Copy_pvCallBackFunc;
  }
  else
  {
    Local_u8ErrorStatus = NULL_POINTER;
  }
  return Local_u8ErrorStatus;
}

u8 Timer0_u8SetCallBackForOverFlow(void (*Copy_pvCallBackFunc)(void))
{
  u8 Local_u8ErrorStatus = OK;
  if (Copy_pvCallBackFunc != NULL)
  {
    TIMER0_pvCallBackFunc2 = Copy_pvCallBackFunc;
  }
  else
  {
    Local_u8ErrorStatus = NULL_POINTER;
  }
  return Local_u8ErrorStatus;
}
/* Timer_0 ISR For Compare Match */
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
  if (TIMER0_pvCallBackFunc1 != NULL)
  {
    TIMER0_pvCallBackFunc1();
  }
  else
  {
  }
}

/* Timer_0 ISR For OverFlow */
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
  if (TIMER0_pvCallBackFunc2 != NULL)
  {
    TIMER0_pvCallBackFunc2();
  }
  else
  {
  }
}

/***********************************************************************************************************************************/
/* Timer_1 */

void Timer1_VidInit(void)
{
  /* Clear Timer_1 Mode Bits and prescaller */
  TCCR1A &= TIMER_1_CLEAR_TCCR1A;
  TCCR1B &= TIMER_1_CLEAR_TCCR1B;
  /* Set Mode */

#if TIMER_1_MODE == TIMER_1_NORMAL_MODE
  TCCR1A |= (TIMER_1_NORMAL_MODE & TIMER_1_CLEAR_WAVEGEN_LEFT_TWO);
  TCCR1B |= ((TIMER_1_NORMAL_MODE << 1) & TIMER_1_CLEAR_WAVEGEN_FIRST_THREE);
  TCCR1A |= (TIMER_1_NON_PWM_COMPARE_OUTPUT_MODE_A << 6);
  TCCR1A |= (TIMER_1_NON_PWM_COMPARE_OUTPUT_MODE_B << 4);
  TCNT1 = TIMER_1_PRELOAD_VALUE; /* SET Preload Value For Timer 1 */
#elif TIMER_1_MODE == TIMER_1_PWM_PHASE_CORRECT_8_BIT_MODE
  TCCR1A |= (TIMER_1_PWM_PHASE_CORRECT_8_BIT_MODE & TIMER_1_CLEAR_WAVEGEN_LEFT_TWO);
  TCCR1B |= ((TIMER_1_PWM_PHASE_CORRECT_8_BIT_MODE << 1) & TIMER_1_CLEAR_WAVEGEN_FIRST_THREE);
  TCCR1A |= (TIMER_1_PHASE_CORRECT_COMPARE_OUTPUT_MODE_A << 6);
  TCCR1A |= (TIMER_1_PHASE_CORRECT_COMPARE_OUTPUT_MODE_B << 4);
  TCNT1 = TIMER_1_PRELOAD_VALUE;         /* SET Preload Value For Timer 1 */
  OCR1A = TIMER_1_COMPARE_MATCH_VALUE_A; /* SET Compare Match Value for Timer 1 Bin A */
  OCR1B = TIMER_1_COMPARE_MATCH_VALUE_B; /* SET Compare Match Value for Timer 1 Bin B */
#elif TIMER_1_MODE == TIMER_1_PWM_PHASE_CORRECT_9_BIT_MODE
  TCCR1A |= (TIMER_1_PWM_PHASE_CORRECT_9_BIT_MODE & TIMER_1_CLEAR_WAVEGEN_LEFT_TWO);
  TCCR1B |= ((TIMER_1_PWM_PHASE_CORRECT_9_BIT_MODE << 1) & TIMER_1_CLEAR_WAVEGEN_FIRST_THREE);
  TCCR1A |= (TIMER_1_PHASE_CORRECT_COMPARE_OUTPUT_MODE_A << 6);
  TCCR1A |= (TIMER_1_PHASE_CORRECT_COMPARE_OUTPUT_MODE_B << 4);
  TCNT1 = TIMER_1_PRELOAD_VALUE;                       /* SET Preload Value For Timer 1 */
  OCR1A = TIMER_1_COMPARE_MATCH_VALUE_A;               /* SET Compare Match Value for Timer 1 Bin A */
  OCR1B = TIMER_1_COMPARE_MATCH_VALUE_B;               /* SET Compare Match Value for Timer 1 Bin B */
#elif TIMER_1_MODE == TIMER_1_PWM_PHASE_CORRECT_10_BIT_MODE
  TCCR1A |= (TIMER_1_PWM_PHASE_CORRECT_10_BIT_MODE & TIMER_1_CLEAR_WAVEGEN_LEFT_TWO);
  TCCR1B |= ((TIMER_1_PWM_PHASE_CORRECT_10_BIT_MODE << 1) & TIMER_1_CLEAR_WAVEGEN_FIRST_THREE);
  TCCR1A |= (TIMER_1_PHASE_CORRECT_COMPARE_OUTPUT_MODE_A << 6);
  TCCR1A |= (TIMER_1_PHASE_CORRECT_COMPARE_OUTPUT_MODE_B << 4);
  TCNT1 = TIMER_1_PRELOAD_VALUE;                   /* SET Preload Value For Timer 1 */
  OCR1A = TIMER_1_COMPARE_MATCH_VALUE_A;           /* SET Compare Match Value for Timer 1 Bin A */
  OCR1B = TIMER_1_COMPARE_MATCH_VALUE_B;           /* SET Compare Match Value for Timer 1 Bin B */
#elif TIMER_1_MODE == TIMER_1_CTC_OCR1A_MODE
  TCCR1A |= (TIMER_1_CTC_OCR1A_MODE & TIMER_1_CLEAR_WAVEGEN_LEFT_TWO);
  TCCR1B |= ((TIMER_1_CTC_OCR1A_MODE << 1) & TIMER_1_CLEAR_WAVEGEN_FIRST_THREE);
  TCCR1A |= (TIMER_1_NON_PWM_COMPARE_OUTPUT_MODE_A << 6);
  TCCR1A |= (TIMER_1_NON_PWM_COMPARE_OUTPUT_MODE_B << 4);
  TCNT1 = TIMER_1_PRELOAD_VALUE;         /* SET Preload Value For Timer 1 */
  OCR1A = TIMER_1_COMPARE_MATCH_VALUE_A; /* SET Compare Match Value for Timer 1 Bin A */
  OCR1B = TIMER_1_COMPARE_MATCH_VALUE_B; /* SET Compare Match Value for Timer 1 Bin B */
#elif TIMER_1_MODE == TIMER_1_FAST_PWM_8_BIT_MODE
  TCCR1A |= (TIMER_1_FAST_PWM_9_BIT_MODE & TIMER_1_CLEAR_WAVEGEN_LEFT_TWO);
  TCCR1B |= ((TIMER_1_FAST_PWM_9_BIT_MODE << 1) & TIMER_1_CLEAR_WAVEGEN_FIRST_THREE);
  TCCR1A |= (TIMER_1_PWM_COMPARE_OUTPUT_MODE_A << 6);
  TCCR1A |= (TIMER_1_PWM_COMPARE_OUTPUT_MODE_B << 4);
  TCNT1 = TIMER_1_PRELOAD_VALUE;         /* SET Preload Value For Timer 1 */
  OCR1A = TIMER_1_COMPARE_MATCH_VALUE_A; /* SET Compare Match Value for Timer 1 Bin A */
  OCR1B = TIMER_1_COMPARE_MATCH_VALUE_B; /* SET Compare Match Value for Timer 1 Bin B */
#elif TIMER_1_MODE == TIMER_1_FAST_PWM_9_BIT_MODE
  TCCR1A |= (TIMER_1_FAST_PWM_9_BIT_MODE & TIMER_1_CLEAR_WAVEGEN_LEFT_TWO);
  TCCR1B |= ((TIMER_1_FAST_PWM_9_BIT_MODE << 1) & TIMER_1_CLEAR_WAVEGEN_FIRST_THREE);
  TCCR1A |= (TIMER_1_PWM_COMPARE_OUTPUT_MODE_A << 6);
  TCCR1A |= (TIMER_1_PWM_COMPARE_OUTPUT_MODE_B << 4);
  TCNT1 = TIMER_1_PRELOAD_VALUE;         /* SET Preload Value For Timer 1 */
  OCR1A = TIMER_1_COMPARE_MATCH_VALUE_A; /* SET Compare Match Value for Timer 1 Bin A */
  OCR1B = TIMER_1_COMPARE_MATCH_VALUE_B; /* SET Compare Match Value for Timer 1 Bin B */
#elif TIMER_1_MODE == TIMER_1_FAST_PWM_10_BIT_MODE
  TCCR1A |= (TIMER_1_FAST_PWM_10_BIT_MODE & TIMER_1_CLEAR_WAVEGEN_LEFT_TWO);
  TCCR1B |= ((TIMER_1_FAST_PWM_10_BIT_MODE << 1) & TIMER_1_CLEAR_WAVEGEN_FIRST_THREE);
  TCCR1A |= (TIMER_1_PWM_COMPARE_OUTPUT_MODE_A << 6);
  TCCR1A |= (TIMER_1_PWM_COMPARE_OUTPUT_MODE_B << 4);
  TCNT1 = TIMER_1_PRELOAD_VALUE;         /* SET Preload Value For Timer 1 */
  OCR1A = TIMER_1_COMPARE_MATCH_VALUE_A; /* SET Compare Match Value for Timer 1 Bin A */
  OCR1B = TIMER_1_COMPARE_MATCH_VALUE_B; /* SET Compare Match Value for Timer 1 Bin B */
#elif TIMER_1_MODE == TIMER_1_PWM_PHASE_AND_FREQUENCY_CORRECT_ICR1_MODE
  TCCR1A |= (TIMER_1_PWM_PHASE_AND_FREQUENCY_CORRECT_ICR1_MODE & TIMER_1_CLEAR_WAVEGEN_LEFT_TWO);
  TCCR1B |= ((TIMER_1_PWM_PHASE_AND_FREQUENCY_CORRECT_ICR1_MODE << 1) & TIMER_1_CLEAR_WAVEGEN_FIRST_THREE);
  TCCR1A |= (TIMER_1_PHASE_CORRECT_COMPARE_OUTPUT_MODE_A << 6);
  TCCR1A |= (TIMER_1_PHASE_CORRECT_COMPARE_OUTPUT_MODE_B << 4);
  TCNT1 = TIMER_1_PRELOAD_VALUE;         /* SET Preload Value For Timer 1 */
  ICR1 = TIMER_1_ICR1_VALUE;             /* Set ICR1 Value */
  OCR1A = TIMER_1_COMPARE_MATCH_VALUE_A; /* SET Compare Match Value for Timer 1 Bin A */
  OCR1B = TIMER_1_COMPARE_MATCH_VALUE_B; /* SET Compare Match Value for Timer 1 Bin B */
#elif TIMER_1_MODE == TIMER_1_PWM_PHASE_AND_FREQUENCY_CORRECT_OCR1A_MODE
  TCCR1A |= (TIMER_1_PWM_PHASE_AND_FREQUENCY_CORRECT_OCR1A_MODE & TIMER_1_CLEAR_WAVEGEN_LEFT_TWO);
  TCCR1B |= ((TIMER_1_PWM_PHASE_AND_FREQUENCY_CORRECT_OCR1A_MODE << 1) & TIMER_1_CLEAR_WAVEGEN_FIRST_THREE);
  TCCR1A |= (TIMER_1_PHASE_CORRECT_COMPARE_OUTPUT_MODE_A << 6);
  TCCR1A |= (TIMER_1_PHASE_CORRECT_COMPARE_OUTPUT_MODE_B << 4);
  TCNT1 = TIMER_1_PRELOAD_VALUE;         /* SET Preload Value For Timer 1 */
  OCR1A = TIMER_1_COMPARE_MATCH_VALUE_A; /* SET Compare Match Value for Timer 1 Bin A */
  OCR1B = TIMER_1_COMPARE_MATCH_VALUE_B; /* SET Compare Match Value for Timer 1 Bin B */
#elif TIMER_1_MODE == TIMER_1_PWM_PHASE_CORRECT_ICR1_MODE
  TCCR1A |= (TIMER_1_PWM_PHASE_CORRECT_ICR1_MODE & TIMER_1_CLEAR_WAVEGEN_LEFT_TWO);
  TCCR1B |= ((TIMER_1_PWM_PHASE_CORRECT_ICR1_MODE << 1) & TIMER_1_CLEAR_WAVEGEN_FIRST_THREE);
  TCCR1A |= (TIMER_1_PHASE_CORRECT_COMPARE_OUTPUT_MODE_A << 6);
  TCCR1A |= (TIMER_1_PHASE_CORRECT_COMPARE_OUTPUT_MODE_B << 4);
  TCNT1 = TIMER_1_PRELOAD_VALUE;         /* SET Preload Value For Timer 1 */
  ICR1 = TIMER_1_ICR1_VALUE;             /* Set ICR1 Value */
  OCR1A = TIMER_1_COMPARE_MATCH_VALUE_A; /* SET Compare Match Value for Timer 1 Bin A */
  OCR1B = TIMER_1_COMPARE_MATCH_VALUE_B; /* SET Compare Match Value for Timer 1 Bin B */
#elif TIMER_1_MODE == TIMER_1_PWM_PHASE_CORRECT_OCR1A_MODE
  TCCR1A |= (TIMER_1_PWM_PHASE_CORRECT_OCR1A_MODE & TIMER_1_CLEAR_WAVEGEN_LEFT_TWO);
  TCCR1B |= ((TIMER_1_PWM_PHASE_CORRECT_OCR1A_MODE << 1) & TIMER_1_CLEAR_WAVEGEN_FIRST_THREE);
  TCCR1A |= (TIMER_1_PHASE_CORRECT_COMPARE_OUTPUT_MODE_A << 6);
  TCCR1A |= (TIMER_1_PHASE_CORRECT_COMPARE_OUTPUT_MODE_B << 4);
  TCNT1 = TIMER_1_PRELOAD_VALUE;         /* SET Preload Value For Timer 1 */
  OCR1A = TIMER_1_COMPARE_MATCH_VALUE_A; /* SET Compare Match Value for Timer 1 Bin A */
  OCR1B = TIMER_1_COMPARE_MATCH_VALUE_B; /* SET Compare Match Value for Timer 1 Bin B */
#elif TIMER_1_MODE == TIMER_1_CTC_ICR1_MODE
  TCCR1A |= (TIMER_1_CTC_ICR1_MODE & TIMER_1_CLEAR_WAVEGEN_LEFT_TWO);
  TCCR1B |= ((TIMER_1_CTC_ICR1_MODE << 1) & TIMER_1_CLEAR_WAVEGEN_FIRST_THREE);
  TCCR1A |= (TIMER_1_NON_PWM_COMPARE_OUTPUT_MODE_A << 6);
  TCCR1A |= (TIMER_1_NON_PWM_COMPARE_OUTPUT_MODE_B << 4);
  TCNT1 = TIMER_1_PRELOAD_VALUE;         /* SET Preload Value For Timer 1 */
  ICR1 = TIMER_1_ICR1_VALUE;             /* Set ICR1 Value */
  OCR1A = TIMER_1_COMPARE_MATCH_VALUE_A; /* SET Compare Match Value for Timer 1 Bin A */
  OCR1B = TIMER_1_COMPARE_MATCH_VALUE_B; /* SET Compare Match Value for Timer 1 Bin B */
#elif TIMER_1_MODE == TIMER_1_FAST_PWM_ICR1_MODE
  TCCR1A |= (TIMER_1_FAST_PWM_ICR1_MODE & TIMER_1_CLEAR_WAVEGEN_LEFT_TWO);
  TCCR1B |= ((TIMER_1_FAST_PWM_ICR1_MODE << 1) & TIMER_1_CLEAR_WAVEGEN_FIRST_THREE);
  TCCR1A |= (TIMER_1_PWM_COMPARE_OUTPUT_MODE_A << 6);
  TCCR1A |= (TIMER_1_PWM_COMPARE_OUTPUT_MODE_B << 4);
  TCNT1 = TIMER_1_PRELOAD_VALUE;         /* SET Preload Value For Timer 1 */
  ICR1 = TIMER_1_ICR1_VALUE;             /* Set ICR1 Value */
  OCR1A = TIMER_1_COMPARE_MATCH_VALUE_A; /* SET Compare Match Value for Timer 1 Bin A */
  OCR1B = TIMER_1_COMPARE_MATCH_VALUE_B; /* SET Compare Match Value for Timer 1 Bin B */
#elif TIMER_1_MODE == TIMER_1_FAST_PWM_OCR1A_MODE
  TCCR1A |= (TIMER_1_FAST_PWM_OCR1A_MODE & TIMER_1_CLEAR_WAVEGEN_LEFT_TWO);
  TCCR1B |= ((TIMER_1_FAST_PWM_OCR1A_MODE << 1) & TIMER_1_CLEAR_WAVEGEN_FIRST_THREE);
  TCCR1A |= (TIMER_1_PWM_COMPARE_OUTPUT_MODE_A << 6);
  TCCR1A |= (TIMER_1_PWM_COMPARE_OUTPUT_MODE_B << 4);
  TCNT1 = TIMER_1_PRELOAD_VALUE;         /* SET Preload Value For Timer 1 */
  OCR1A = TIMER_1_COMPARE_MATCH_VALUE_A; /* SET Compare Match Value for Timer 1 Bin A */
  OCR1B = TIMER_1_COMPARE_MATCH_VALUE_B; /* SET Compare Match Value for Timer 1 Bin B */
#endif

/* Enable compare match Interrupt A */
#if TIMER_1_INTERRUPT_COMPAREMATCH_A_STATUS == ENABLE_TIMER_1_INTERRUPT_COMPAREMATCH_A
  SET_BIT(TIMSK, TIMSK_OCIE1A);
#elif TIMER_1_INTERRUPT_COMPAREMATCH_A_STATUS == DISABLE_TIMER_1_INTERRUPT_COMPAREMATCH_A
  CLEAR_BIT(TIMSK, TIMSK_OCIE1A);
#endif

/* Enable compare match Interrupt B */
#if TIMER_1_INTERRUPT_COMPAREMATCH_B_STATUS == ENABLE_TIMER_1_INTERUPT_COMPAREMATCH_B
  SET_BIT(TIMSK, TIMSK_OCIE1B);
#elif TIMER_1_INTERRUPT_COMPAREMATCH_B_STATUS == DISABLE_TIMER_1_INTERUPT_COMPAREMATCH_B
  CLEAR_BIT(TIMSK, TIMSK_OCIE1B);
#endif

/* Enable OverFlow Interrupt  */
#if TIMER_1_INTERRUPT_OVERFLOW_STATUS == ENABLE_TIMER_1_OVERFLOW_INTERRUPT
  SET_BIT(TIMSK, TIMSK_TOIE1);
#elif TIMER_1_INTERRUPT_OVERFLOW_STATUS == DISABLE_TIMER_1_OVERFLOW_INTERRUPT
  CLEAR_BIT(TIMSK, TIMSK_TOIE1);
#endif

/***********************  InputCapture  /***********************/

/* Enable Noise Canceller */
#if TIMER_1_INPUTCAPTURE_NOISECANCELLER_STATUS == ENABLE_TIMER_1_INPUTCAPTURE_NOISECANCELLER
  SET_BIT(TCCR1B, TCCR1B_ICNC1);
#elif TIMER_1_INPUTCAPTURE_NOISECANCELLER_STATUS == DISABLE_TIMER_1_INPUTCAPTURE_NOISECANCELLER
  CLEAR_BIT(TCCR1B, TCCR1B_ICNC1);
#endif

/*Edge Select*/
#if TIMER_1_INPUTCAPTURE_TRIGGER == TIMER_1_INPUTCAPTURE_RISINGEDGE
  SET_BIT(TCCR1B, TCCR1B_ICES1);
#elif TIMER_1_INPUTCAPTURE_TRIGGER == TIMER_1_INPUTCAPTURE_FALLINGEDGE
  CLEAR_BIT(TCCR1B, TCCR1B_ICES1);
#endif

/* Enable InputCapture Interrupt  */
#if TIMER_1_INTERRUPT_INPUTCAPTURE_STATUS == ENABLE_TIMER_1_INPUTCAPTURE_INTERRUPT
  SET_BIT(TIMSK, TIMSK_TICIE1);
#elif TIMER_1_INTERRUPT_INPUTCAPTURE_STATUS == DISABLE_TIMER_1_INPUTCAPTURE_INTERRUPT
  CLEAR_BIT(TIMSK, TIMSK_TICIE1);
#endif

  /* SELECT Prescaller */
  TCCR1B |= TIMER_1_PRE_SCALAR_VALUE;
}

void TIMER1_voidSetCompareMatchValueForA(u16 Copy_u16CompareMatchValue)
{
  OCR1A = Copy_u16CompareMatchValue; /* Set Compare Output Mode */
}

void TIMER1_voidSetCompareMatchValueForB(u16 Copy_u16CompareMatchValue)
{
  OCR1B = Copy_u16CompareMatchValue; /* Set Compare Output Mode */
}

void TIMER1_voidSetPreLoadValue(u16 Copy_u16PreLoadValue)
{
  TCNT1 = Copy_u16PreLoadValue; /* Set PreLoad Value */
}

void TIMER1_voidSetTop(u16 Copy_u16TopValue)
{
  ICR1 = Copy_u16TopValue; /* Set PreLoad Value */
}

u8 Timer1_VoidICUSetTriggerEdge(u8 Copy_u8Edge)
{
  u8 Local_u8ErrorStatus = OK;
  if (Copy_u8Edge == TIMER_1_INPUTCAPTURE_RISINGEDGE)
    SET_BIT(TCCR1B, TCCR1B_ICES1);
  else if (Copy_u8Edge == TIMER_1_INPUTCAPTURE_FALLINGEDGE)
    CLEAR_BIT(TCCR1B, TCCR1B_ICES1);
  else
    Local_u8ErrorStatus = NOK;
  return Local_u8ErrorStatus;
}

void Timer1_VoidICUInteruptEnable(void)
{
  SET_BIT(TIMSK, TIMSK_TICIE1);
}

void Timer1_VoidICUInteruptDisable(void)
{
  CLEAR_BIT(TIMSK, TIMSK_TICIE1);
}

void Timer1_VoidICUNoiseCancellerEnable(void)
{
  SET_BIT(TCCR1B, TCCR1B_ICNC1);
}

void Timer1_VoidICUNoiseCancellerDisable(void)
{
  CLEAR_BIT(TCCR1B, TCCR1B_ICNC1);
}

u16 Timer1_u16ReadInputCaptureUnit(void)
{
  return ICR1;
}

u8 Timer1_u8SetCallBackForCaptureEvent(void (*Copy_pvCallBackFunc)(void))
{
  u8 Local_u8ErrorStatus = OK;
  if (Copy_pvCallBackFunc != NULL)
  {
    TIMER1_pvCallBackFunc1 = Copy_pvCallBackFunc;
  }
  else
  {
    Local_u8ErrorStatus = NULL_POINTER;
  }
  return Local_u8ErrorStatus;
}

u8 Timer1_u8SetCallBackForCompareMatchA(void (*Copy_pvCallBackFunc)(void))
{
  u8 Local_u8ErrorStatus = OK;
  if (Copy_pvCallBackFunc != NULL)
  {
    TIMER1_pvCallBackFunc2 = Copy_pvCallBackFunc;
  }
  else
  {
    Local_u8ErrorStatus = NULL_POINTER;
  }
  return Local_u8ErrorStatus;
}

u8 Timer1_u8SetCallBackForCompareMatchB(void (*Copy_pvCallBackFunc)(void))
{
  u8 Local_u8ErrorStatus = OK;
  if (Copy_pvCallBackFunc != NULL)
  {
    TIMER1_pvCallBackFunc3 = Copy_pvCallBackFunc;
  }
  else
  {
    Local_u8ErrorStatus = NULL_POINTER;
  }
  return Local_u8ErrorStatus;
}

u8 Timer1_u8SetCallBackForOverFlow(void (*Copy_pvCallBackFunc)(void))
{
  u8 Local_u8ErrorStatus = OK;
  if (Copy_pvCallBackFunc != NULL)
  {
    TIMER1_pvCallBackFunc4 = Copy_pvCallBackFunc;
  }
  else
  {
    Local_u8ErrorStatus = NULL_POINTER;
  }
  return Local_u8ErrorStatus;
}

/* Timer/Counter1 Capture Event */
void __vector_6(void) __attribute__((signal));
void __vector_6(void)
{
  if (TIMER1_pvCallBackFunc1 != NULL)
  {
    TIMER1_pvCallBackFunc1();
  }
  else
  {
  }
}

/* Timer/Counter1 Compare Match A */
void __vector_7(void) __attribute__((signal));
void __vector_7(void)
{

  if (TIMER1_pvCallBackFunc2 != NULL)
  {
    TIMER1_pvCallBackFunc2();
  }
  else
  {
  }
}
/* Timer/Counter1 Compare Match B */

void __vector_8(void) __attribute__((signal));
void __vector_8(void)
{
  if (TIMER1_pvCallBackFunc3 != NULL)
  {
    TIMER1_pvCallBackFunc3();
  }
  else
  {
  }
}

/* Timer_1 ISR For OverFlow */
void __vector_9(void) __attribute__((signal));
void __vector_9(void)
{

  if (TIMER1_pvCallBackFunc4 != NULL)
  {
    TIMER1_pvCallBackFunc4();
  }
  else
  {
  }
}

/***********************************************************************************************************************************/

/* Timer_2 */

void Timer2_VidInit(void)
{
  /* Clear Prev Mode and Compare Match Output Mode */
  TCCR2 &= TIMER_2_CLEAR_MODE;

/* Select MODE From Config */
#if TIMER_2_MODE == TIMER_2_NORMAL_MODE
  TCCR2 |= TIMER_2_NORMAL_MODE_SET;                    /*Set Normal Mode*/
  TCCR2 |= (TIMER_2_NON_PWM_COMPARE_OUTPUT_MODE << 4); /*Set Compare Output Mode*/
  TCNT2 = TIMER_2_PRELOAD_VALUE;                       /* Set PreLoad Value */
#elif TIMER_2_MODE == TIMER_2_PWM_PHASE_CORRECT_MODE
  TCCR2 |= TIMER_2_PWM_PHASE_CORRECT_MODE_SET;               /* SELECT PHASE CORRECT MODE */
  TCCR2 |= (TIMER_2_PHASE_CORRECT_COMPARE_OUTPUT_MODE << 4); /* Set Compare Output Mode */
  TCNT2 = TIMER_2_PRELOAD_VALUE;                             /* Set PreLoad Value */
  OCR2 = TIMER_2_COMPARE_MATCH_VALUE;                        /* Ser Compare Match Value */
#elif TIMER_2_MODE == TIMER_2_CTC_MODE
  TCCR2 |= TIMER_2_CTC_MODE_SET;                       /*Set CTC Mode*/
  TCCR2 |= (TIMER_2_NON_PWM_COMPARE_OUTPUT_MODE << 4); /* Set Compare Output Mode */
  TCNT2 = TIMER_2_PRELOAD_VALUE;                       /* Set PreLoad Value */
  OCR2 = TIMER_2_COMPARE_MATCH_VALUE;                  /* Ser Compare Match Value */
#elif TIMER_2_MODE == TIMER_2_FAST_PWM_MODE
  TCCR2 |= TIMER_2_FAST_PWM_MODE_SET;              /* Set Fast_PWM Mode */
  TCCR2 |= (TIMER_2_PWM_COMPARE_OUTPUT_MODE << 4); /* Set Compare Output Mode */
  TCNT2 = TIMER_2_PRELOAD_VALUE;                   /* Set PreLoad Value */
  OCR2 = TIMER_2_COMPARE_MATCH_VALUE;              /* Ser Compare Match Value */
#endif

/* Enable Compare Match Interrupt */
#if TIMER_2_COMPAREMATCH_INTERRUPT_STATUS == ENABLE_TIMER_2_COMPAREMATCH_INTERRUPT
  SET_BIT(TIMSK, TIMSK_OCIE2);
#elif TIMER_2_COMPAREMATCH_INTERRUPT_STATUS == DISABLE_TIMER_2_COMPAREMATCH_INTERRUPT
  CLEAR_BIT(TIMSK, TIMSK_OCIE2);
#endif

/* Enable OverFlow Interrupt */
#if TIMER_2_OVERFLOW_INTERRUPT_STATUS == ENABLE_TIMER_2_OVERFLOW_INTERRUPT
  SET_BIT(TIMSK, TIMSK_TOIE2);
#elif TIMER_2_OVERFLOW_INTERRUPT_STATUS == DISABLE_TIMER_2_OVERFLOW_INTERRUPT
  CLEAR_BIT(TIMSK, TIMSK_TOIE2);
#endif

  /* SELECT Prescaller*/
  TCCR2 |= TIMER_2_PRE_SCALAR_VALUE;
}

void TIMER2_voidSetCompareMatchValue(u8 Copy_u8CompareMatchValue)
{
  OCR2 = Copy_u8CompareMatchValue; /* Set Compare Output Mode */
}

void TIMER2_voidSetPreLoadValue(u8 Copy_u8PreLoadValue)
{
  TCNT2 = Copy_u8PreLoadValue; /* Set PreLoad Value */
}

void TIMER2_voidGenFastPWM(u8 Copy_u8Duty)
{
  f32 Local_f32Duty = (f32)Copy_u8Duty / 100;
#if TIMER_2_PWM_COMPARE_OUTPUT_MODE == CLEAR_OC2_ON_COMPARE_SET_OC2_ON_TOP
  OCR2 = 256 * Local_f32Duty;
#elif TIMER_2_PWM_COMPARE_OUTPUT_MODE == SET_OC2_ON_COMPARE_CLEAR_OC2_ON_TOP
  OCR2 = 1 - (256 * Local_f32Duty);

#endif
}

u8 Timer2_u8SetCallBackForCompareMatch(void (*Copy_pvCallBackFunc)(void))
{
  u8 Local_u8ErrorStatus = OK;
  if (Copy_pvCallBackFunc != NULL)
  {
    TIMER2_pvCallBackFunc1 = Copy_pvCallBackFunc;
  }
  else
  {
    Local_u8ErrorStatus = NULL_POINTER;
  }
  return Local_u8ErrorStatus;
}

u8 Timer2_u8SetCallBackForOverFlow(void (*Copy_pvCallBackFunc)(void))
{
  u8 Local_u8ErrorStatus = OK;
  if (Copy_pvCallBackFunc != NULL)
  {
    TIMER2_pvCallBackFunc2 = Copy_pvCallBackFunc;
  }
  else
  {
    Local_u8ErrorStatus = NULL_POINTER;
  }
  return Local_u8ErrorStatus;
}

/* Timer_2 ISR For Compare Match */
void __vector_4(void) __attribute__((signal));
void __vector_4(void)
{
  if (TIMER2_pvCallBackFunc1 != NULL)
  {
    TIMER2_pvCallBackFunc1();
  }
  else
  {
  }
}

/* Timer_2 ISR For OverFlow */
void __vector_5(void) __attribute__((signal));
void __vector_5(void)
{
  if (TIMER2_pvCallBackFunc2 != NULL)
  {
    TIMER2_pvCallBackFunc2();
  }
  else
  {
  }
}

/***********************************************************************************************************************************/
/*  WatchDog Timer */

u8 WDT_VoidSleep(u8 Copy_u8SleepTime)
{
  u8 Local_u8ErrorStatus = OK;
  if (Copy_u8SleepTime < 8)
  {
    /* Clear Prescaller bits */
    WDTCR &= CLEAR_WDTCR_PRESCALLER;
    /* Set Prescaller */
    WDTCR |= Copy_u8SleepTime;
  }
  else
  {
    Local_u8ErrorStatus = NOK;
  }
  return Local_u8ErrorStatus;
}

void WDT_VoidEnable()
{
  SET_BIT(WDTCR, WDTCR_WDE);
}

void WDT_VoidDisable()
{
  /*Set WDE & WDTOE in one operation */
  WDTCR |= SET_WDTCR_WDE_WDTOE;
  /*Clear WDTCR */
  WDTCR = CLEAR_WDTCR;
}
