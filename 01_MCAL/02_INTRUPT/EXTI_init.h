#ifndef EXTI_INIT_H
#define EXTI_INIT_H

/*
    Configuration Setting
*/

#define FALLING_EDGE 10
#define RISING_EDGE 20
#define LOW_LEVEL 30
#define ON_CHANGE 40

#define INTERRUPT_0 6
#define INTERRUPT_1 7
#define INTERRUPT_2 5

u8 EXTI_VidEnableInterrupt(u8 Copy_u8INTERRUPT, u8 copy_u8Sense);
u8 EXTI_VidDisableInterrupt(u8 Copy_u8INTERRUPT);

void EXTI_VidEnable(void);
void EXTI_VidDisable(void);

u8 EXTI_u8Int0SetCallBack(void (*Copy_pvInt0Func)(void));
u8 EXTI_u8Int1SetCallBack(void (*Copy_pvInt1Func)(void));
u8 EXTI_u8Int2SetCallBack(void (*Copy_pvInt2Func)(void));

#endif
