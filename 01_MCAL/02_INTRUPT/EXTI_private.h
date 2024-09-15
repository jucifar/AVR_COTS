#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

/*
    Configuration Setting
*/
#define NONE 8
#define DISABLE 50
#define ENABLE 60
#define OK 0
#define NOK 1
#define NULL_POINTER 2

/*
    Registers
*/

#define EXTI_MCUSCR *((volatile u8 *)0x54)
#define EXTI_MCUCR *((volatile u8 *)0x55)
#define EXTI_GICR *((volatile u8 *)0x5B)
#define MCUSCR_ISC2 6
#define MCUCR_ISC11 3
#define MCUCR_ISC10 2
#define MCUCR_ISC01 1
#define MCUCR_ISC00 0
#define MCUCR_INTERRUPT_0 6
#define MCUCR_INTERRUPT_1 7
#define MCUCR_INTERRUPT_2 5
#define GICR_INTERRUPT_0 6
#define GICR_INTERRUPT_1 7
#define GICR_INTERRUPT_2 5

#endif
