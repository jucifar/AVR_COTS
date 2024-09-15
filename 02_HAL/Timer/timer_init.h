#ifndef TIMER_INIT_h
#define TIMER_INIT_h

/* Timer_0  */
void Timer0_VidInit(void);
u8 Timer0_u8SetCallBackForCompareMatch(void (*Copy_pvCallBackFunc)(void));
u8 Timer0_u8SetCallBackForOverFlow(void (*Copy_pvCallBackFunc)(void));
void TIMER0_voidSetCompareMatchValue(u8 Copy_u8CompareMatchValue);
void TIMER0_voidSetPreLoadValue(u8 Copy_u8PreLoadValue);
void TIMER0_voidGenFastPWM(u8 Copy_u8Duty);

/* Timer_1 */

#define TIMER_1_INPUTCAPTURE_RISINGEDGE 1
#define TIMER_1_INPUTCAPTURE_FALLINGEDGE 0

void Timer1_VidInit(void);
u8 Timer1_u8SetCallBackForCaptureEvent(void (*Copy_pvCallBackFunc)(void));
u8 Timer1_u8SetCallBackForCompareMatchA(void (*Copy_pvCallBackFunc)(void));
u8 Timer1_u8SetCallBackForCompareMatchB(void (*Copy_pvCallBackFunc)(void));
u8 Timer1_u8SetCallBackForOverFlow(void (*Copy_pvCallBackFunc)(void));
void TIMER1_voidSetCompareMatchValueForA(u16 Copy_u16CompareMatchValue);
void TIMER1_voidSetCompareMatchValueForB(u16 Copy_u16CompareMatchValue);
void TIMER1_voidSetPreLoadValueForA(u16 Copy_u16PreLoadValue);
void TIMER1_voidSetPreLoadValueForB(u16 Copy_u16PreLoadValue);
void TIMER1_voidSetTop(u16 Copy_u16TopValue);
void TIMER1_voidGenFastPWM(u8 Copy_u8Duty);
u8 Timer1_VoidICUSetTriggerEdge(u8 Copy_u8Edge);
void Timer1_VoidICUInterruptEnable(void);
void Timer1_VoidICUInterruptDisable(void);
u16 Timer1_u16ReadInputCaptureUnit(void);
void Timer1_VoidICUNoiseCancellerEnable(void);
void Timer1_VoidICUNoiseCancellerDisable(void);

/*void timer1_VidChangeDuty(u8 factor);*/

/* Timer_2 */

void Timer2_VidInit(void);
u8 Timer2_u8SetCallBackForCompareMatch(void (*Copy_pvCallBackFunc)(void));
u8 Timer2_u8SetCallBackForOVERFLOW(void (*Copy_pvCallBackFunc)(void));
void TIMER2_voidSetCompareMatchValue(u8 Copy_u8CompareMatchValue);
void TIMER2_voidSetPreLoadValue(u8 Copy_u8PreLoadValue);
void TIMER2_voidGenFastPWM(u8 Copy_u8Duty);

/*  WatchDog Timer */
#define WDT_SLEEP_16MS 0
#define WDT_SLEEP_32MS 1
#define WDT_SLEEP_65MS 2
#define WDT_SLEEP_130MS 3
#define WDT_SLEEP_260MS 4
#define WDT_SLEEP_520MS 5
#define WDT_SLEEP_1000MS 6
#define WDT_SLEEP_2000MS 7

u8 WDT_VoidSleep(u8 Copy_u8SleepTime);
void WDT_VoidEnable();
void WDT_VoidDisable();


// Timer1 motor
void TIMER1_VidSetNumberOfSteps(u16 Copy_u8StepValue, u8 Copy_u8Port, u8 Copy_u8Pin);
void StepperMotor_Direction(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction);
void TIMER1_VidInitFastPWM_WithNonInverting(void);
void TIMER1_VidInit_CTCMode(void);

#endif
