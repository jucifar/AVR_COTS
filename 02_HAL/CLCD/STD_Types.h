
/****************************************************************************
 ****************************************************************************
 *******************   SWC    :       STD_TYPES          ********************
 *******************    By    : Youssef Mostafa Mohamed  ********************
 *******************   Date   :       21/8/2022          ********************
 *******************  Version :          V1.0            ********************
 ****************************************************************************
 ***************************************************************************/

#ifndef STD_TYPES_H
#define STD_TYPES_H

typedef char s8;
typedef unsigned char u8;
typedef short int s16;
typedef unsigned short int u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;
typedef long double f128;

#define FALSE 0
#define TRUE 1
#define NULL 0

typedef enum FUNCTION_STATUS
{
    NOK,
    OK,
    NULL_POINTER,
    BUSY_FUNC
} FUNCTION_STATUS;

typedef enum PERIPHERAL_STATUS
{
    IDLE,
    BUSY
} PERIPHERAL_STATUS;

typedef struct
{
    u8 PORT;
    u8 PIN;
} PIN_t;

#endif
