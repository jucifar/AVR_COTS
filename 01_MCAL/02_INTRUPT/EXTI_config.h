#ifndef EXTI_CONFIG_H
#define EXTI_CONFIG_H

#define INT_0_1_PORT Port_D
#define INT_2_PORT Port_B
#define INT_0_PIN Pin_2
#define INT_1_PIN Pin_3
#define INT_2_PIN Pin_2

/*
    FALLING_EDGE
    RISING_EDGE
    LOW_LEVEL
    ON_CHANGE

*/
#define INTERRUPT_SOURCE_0_SENSE_CONTROL FALLING_EDGE
#define INTERRUPT_SOURCE_1_SENSE_CONTROL NONE
#define INTERRUPT_SOURCE_2_SENSE_CONTROL NONE

/*
    INTERRUPT_0
    INTERRUPT_1
    INTERRUPT_2

*/
#define INTERRUPT_SOURCE_0 INTERRUPT0
#define INTERRUPT_SOURCE_1 NONE
#define INTERRUPT_SOURCE_2 NONE

/*
    DISABLE
    NONE
*/
#define INTERRUPT_DISABLE_0 DISABLE
#define INTERRUPT_DISABLE_1 ENABLE
#define INTERRUPT_DISABLE_2 ENABLE

#endif
