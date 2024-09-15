#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

/*

  LEFT
  RIGHT

*/
#define ADJUST LEFT

/*

  PRE_SCALAR_VALUE_2
  PRE_SCALAR_VALUE_4
  PRE_SCALAR_VALUE_8
  PRE_SCALAR_VALUE_16
  PRE_SCALAR_VALUE_32
  PRE_SCALAR_VALUE_64
  PRE_SCALAR_VALUE_128

*/
#define PRE_SCALAR_VALUE PRE_SCALAR_VALUE_128

/*

  AREF
  AVCC
  INTERNAL

*/
#define ADC_REFERENCE_SELECTION AVCC

/*

  ENABLE_AUTO_TRIGGER
  DISABLE_AUTO_TRIGGER

*/
#define AUTO_TRIGGER DISABLE_AUTO_TRIGGER
/*

  ADC0
  ADC1
  ADC2
  ADC3
  ADC4
  ADC5
  ADC6
  ADC7

*/
#define AUTO_TRIGGER_CHANNEL ADC0

/*

  FREE_RUNNING_MODE
  ANALOG_COMPARATOR
  EXTERNAL_INTERRUPT_REQUEST_0
  TIMER_COUNTER_0_COMPARE_MATCH
  TIMER_COUNTER_0_OVERFLOW
  TIMER_COUNTER_COMPARE_MATCH_B
  TIMER_COUNTER_1_OVERFLOW
  TIMER_COUNTER_1_CAPTURE_EVENT

*/
#define AUTO_TRIGGER_SOU FREE_RUNNING_MODE

/*

  BIT_8
  BIT_10

*/
#define RESOLUTION BIT_8

#define ADC_U32TIMEOUT 20000

#endif