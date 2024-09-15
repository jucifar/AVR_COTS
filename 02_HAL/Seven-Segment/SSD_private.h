
/****************************************************************************
*****************************************************************************
*******************   SWC    :       SSD Driver         *********************
*******************    By    : Youssef Mostafa Mohamed  *********************
*******************   Date   :       3/9/2022          *********************
*******************  Version :          V1.0            *********************
*****************************************************************************
****************************************************************************/

#ifndef _SSD_PRIVATE_H_
#define _SSD_PRIVATE_H_

#define Null (0b00000000)
#define ZERO (0b00111111)
#define ONE (0b00000110)
#define TWO (0b01011011)
#define THREE (0b01001111)
#define FOUR (0b01100110)
#define FIVE (0b01101101)
#define SIX (0b01111101)
#define SEVEN (0b00000111)
#define EIGHT (0b01111111)
#define NINE (0b01101111)

static u8 seven_segment_cathode[10] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
static u8 seven_segment_anode[10] = {~ZERO, ~ONE, ~TWO, ~THREE, ~FOUR, ~FIVE, ~SIX, ~SEVEN, ~EIGHT, ~NINE};

#define COMCATH 1
#define COMANODE 2

#endif
