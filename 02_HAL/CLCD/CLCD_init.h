/****************************************************************************
 ****************************************************************************
 *******************   SWC    :        CLCD_INIT          ********************
 *******************    By    : Youssef Mostafa Mohamed  ********************
 *******************   Date   :       9/9/2022          ********************
 *******************  Version :          V1.0            ********************
 ****************************************************************************
 ***************************************************************************/
#ifndef CLCD_INIT_H
#define CLCD_INIT_H

#define CLCD_TWO_16 32
#define CLCD_FOUR_20 80

#define CLCD_4_BIT_MODE 4
#define CLCD_8_BIT_MODE 8

#define DISCONNECTED_PIN 9
#define DISCONNECTED_PORT 10

typedef struct CLCD
{
    u8 CLCD_TYPE;               // CLCD_TWO_16  ||  CLCD_FOUR_20
    u8 CLCD_MODE;               // CLCD_4_BIT_MODE  ||  CLCD_8_BIT_MODE
    PIN_t CLCD_DATA_PINS[8];    // LCD DATA PINS
    PIN_t CLCD_CONTROL_PINS[3]; // LCD CONTROL PINS
} CLCD_t;

/*

Choose The Pins and pass it to the struct in the same order:

// CLCD_DATA_PINS
{{D0_PORT,D0_PIN},
{D1_PORT,D1_PIN},
{D2_PORT,D2_PIN},
{D3_PORT,D3_PIN},
{D4_PORT,D4_PIN},
{D5_PORT,D5_PIN},
{D6_PORT,D6_PIN},
{D7_PORT,D7_PIN}}

// CLCD_CONTROL_PINS
{{RS_PORT,RS_PIN},
{RW_PORT,RW_PIN},
{ENABLE_PORT,ENABLE_PIN}}

*/

void CLCD_VidSendData(u8 copy_u8Data, CLCD_t *CLCD_INFO);
void CLCD_VidSendCommand(u8 copy_u8Command, CLCD_t *CLCD_INFO);
void CLCD_VidInit(CLCD_t *CLCD_INFO);
void CLCD_VidDisplayName(const u8 *copy_u8name, CLCD_t *CLCD_INFO);
void CLCD_VidGoTo(u8 copy_u8X, u8 copy_u8Y, CLCD_t *CLCD_INFO);
void CLCD_VidClearDisplay(CLCD_t *CLCD_INFO);
void CLCD_VidCreateSpecialChar(u8 *copy_u8pattern, u8 copy_u8pattern_num, CLCD_t *CLCD_INFO);
void CLCD_VidSendSpecialChar(u8 copy_u8pattern, u8 copy_u8X, u8 copy_u8Y, CLCD_t *CLCD_INFO);
void CLCD_VidSendInteger(u64 copy_u64integer, CLCD_t *CLCD_INFO);
void CLCD_VidSendNumber(f64 copy_f64Number, CLCD_t *CLCD_INFO);
void CLCD_VidSendDecimal(f64 copy_f64decimal, CLCD_t *CLCD_INFO);
u8 CLCD_VidReadDisplay(u8 copy_u8X, u8 copy_u8Y, CLCD_t *CLCD_INFO);

#endif
