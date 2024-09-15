#ifndef TIMER_CONFIG_H
#define TIMER_CONFIG_H


/* Set Timer_1 Compare Match Value A & B */

#define TIMER_1_COMPARE_MATCH_VALUE_A 1550
#define TIMER_1_COMPARE_MATCH_VALUE_B 0

/* Set Timer_1 PreLoad Value */
#define TIMER_1_PRELOAD_VALUE 0
/* Set ICR1 Value */
#define TIMER_1_ICR1_VALUE 8155

#define TIMER_1_INTERUPT_COMPAREMATCH_A_STATUS DISABLE_TIMER_1_INTERUPT_COMPAREMATCH_A
#define TIMER_1_INTERUPT_COMPAREMATCH_B_STATUS DISABLE_TIMER_1_INTERUPT_COMPAREMATCH_B
#define TIMER_1_INTERUPT_OVERFLOW_STATUS ENABLE_TIMER_1_OVERFLOW_INTERUPT

/*
Timer_1_Modes:

    TIMER_1_NORMAL_MODE
    TIMER_1_PWM_PHASE_CORRECT_8_BIT_MODE
    TIMER_1_PWM_PHASE_CORRECT_9_BIT_MODE
    TIMER_1_PWM_PHASE_CORRECT_10_BIT_MODE
    TIMER_1_CTC_OCR1A_MODE
    TIMER_1_FAST_PWM_8_BIT_MODE
    TIMER_1_FAST_PWM_9_BIT_MODE
    TIMER_1_FAST_PWM_10_BIT_MODE
    TIMER_1_PWM_PHASE_AND_FREQUANCY_CORRECT_ICR1_MODE
    TIMER_1_PWM_PHASE_AND_FREQUANCY_CORRECT_OCR1A_MODE
    TIMER_1_PWM_PHASE_CORRECT_ICR1_MODE
    TIMER_1_PWM_PHASE_CORRECT_OCR1A_MODE
    TIMER_1_CTC_ICR1_MODE
    TIMER_1_FAST_PWM_ICR1_MODE
    TIMER_1_FAST_PWM_OCR1A_MODE

 */
#define TIMER_1_MODE TIMER_1_PWM_PHASE_CORRECT_ICR1_MODE

/*
TIMER_1_PRE_SCALAR_VALUE:

    PRE_SCALAR_VALUE_NO_CLOCK,
    PRE_SCALAR_VALUE_NONE,
    PRE_SCALAR_VALUE_8,
    PRE_SCALAR_VALUE_64,
    PRE_SCALAR_VALUE_256,
    PRE_SCALAR_VALUE_1024,
    EXTERNAL_CLOCK_ON_T_BIN_FALLINGEDGE,
    EXTERNAL_CLOCK_ON_T_BIN_RISINGEDGE

*/

#define TIMER_1_PRE_SCALAR_VALUE PRE_SCALAR_VALUE_8

/*
COMPARE_OUTPUT_MODE_TIMER_1_NON_PWM:

    OC1A_OC1B_DISCONNECTED_NONPWM
    TOGGLE_OC1A_OC1B_ON_COMPARE_NONPWM
    CLEAR_OC1_ON_COMPARE
    SET_OC1_ON_COMPARE

*/
#define TIMER_1_NON_PWM_COMPARE_OUTPUT_MODE_A OC1A_OC1B_DISCONNECTED_NONPWM
#define TIMER_1_NON_PWM_COMPARE_OUTPUT_MODE_B OC1A_OC1B_DISCONNECTED_NONPWM

/*
COMPARE_OUTPUT_MODE_TIMER_1_FAST_PWM:

   OC1A_OC1B_DISCONNECTED_FPWM
    TOGGLE_OC1A_OC1B_ON_COMPARE_FPWM
    CLEAR_OC1_ON_COMPARE_SET_OC1_ON_TOP
    SET_OC1_ON_COMPARE_CLEAR_OC1_ON_TOP


*/
#define TIMER_1_PWM_COMPARE_OUTPUT_MODE_A OC1A_OC1B_DISCONNECTED_FPWM
#define TIMER_1_PWM_COMPARE_OUTPUT_MODE_B OC1A_OC1B_DISCONNECTED_FPWM

/*
COMPARE_OUTPUT_MODE_TIMER_1_PHASE_CORRECT:

    OC1A_OC1B_DISCONNECTED_PCORRECT
    TOGGLE_OCA1_OCB1_ON_COMPARE_PCORRECT
    CLEAR_OC1_ON_COMPARE_UPCOUNTING_SET_OC1_ON_TOP_DOWNCOUNTING
    SET_OC1_ON_COMPARE_UPCOUNTING_CLEAR_OC1_ON_TOP_DOWNCOUNTING

*/

#define TIMER_1_PHASE_CORRECT_COMPARE_OUTPUT_MODE_A CLEAR_OC1_ON_COMPARE_UPCOUNTING_SET_OC1_ON_TOP_DOWNCOUNTING
#define TIMER_1_PHASE_CORRECT_COMPARE_OUTPUT_MODE_B OC1A_OC1B_DISCONNECTED_PCORRECT



#endif