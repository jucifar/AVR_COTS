/****************************************************************************
 ****************************************************************************
 *******************   SWC    :        GLCD_INIT          ********************
 *******************    By    : Youssef Mostafa Mohamed  ********************
 *******************   Date   :       9/9/2022          ********************
 *******************  Version :          V1.0            ********************
 ****************************************************************************
 ***************************************************************************/
#ifndef GLCD_INIT_H
#define GLCD_INIT_H

#define GLCD_4_BIT_MODE 4
#define GLCD_8_BIT_MODE 8

#define DISCONNECTED_PIN 9
#define DISCONNECTED_PORT 10

typedef struct GLCD
{
    u8 GLCD_MODE;               // GLCD_4_BIT_MODE  ||  GLCD_8_BIT_MODE
    PIN_t GLCD_DATA_PINS[8];    // LCD DATA PINS
    PIN_t GLCD_CONTROL_PINS[6]; // LCD CONTROL PINS
} GLCD_t;

/*

Choose The Pins and pass it to the struct in the same order:

// GLCD_DATA_PINS
{{D0_PORT,D0_PIN},
{D1_PORT,D1_PIN},
{D2_PORT,D2_PIN},
{D3_PORT,D3_PIN},
{D4_PORT,D4_PIN},
{D5_PORT,D5_PIN},
{D6_PORT,D6_PIN},
{D7_PORT,D7_PIN}}

// GLCD_CONTROL_PINS
{{RS_PORT,RS_PIN},
{RW_PORT,RW_PIN},
{ENABLE_PORT,ENABLE_PIN},
{CS0_PORT,CS0_PIN},
{CS1_PORT,CS0_PIN},
{RST_PORT,RST_PIN}}

*/
void GLCD_VidInit(GLCD_t *GLCD_INFO);
void GLCD_VidSendData(u8 copy_u8Data, GLCD_t *GLCD_INFO);
void GLCD_VidSendCommand(u8 copy_u8Command, GLCD_t *GLCD_INFO);
void GLCD_VidSendByte(u8 copy_u8Data, u8 copy_u8y, GLCD_t *GLCD_INFO);
void GLCD_VidSendChar(u8 Copy_u8Char, u8 Copy_u8UnderlineStatus, u8 copy_u8y, GLCD_t *GLCD_INFO);
void GLCD_VidDisplayText_Pixel(u8 Copy_u8Pixel, u8 copy_u8y, const u8 *copy_u8name, u8 Copy_u8UnderlineStatus, GLCD_t *GLCD_INFO);
void GLCD_VidDisplayText_Page(u8 Copy_u8Page, u8 copy_u8y, const u8 *copy_u8name, u8 Copy_u8UnderlineStatus, GLCD_t *GLCD_INFO);
void GLCD_VidGoToZ(u8 Copy_u8Z, GLCD_t *GLCD_INFO);
void GLCD_VidGoToY(u8 Copy_u8Y, GLCD_t *GLCD_INFO);
void GLCD_VidGoToPage(u8 Copy_u8Page, GLCD_t *GLCD_INFO);
void GLCD_VidDisplayStraitLine(u8 Copy_u8x, GLCD_t *GLCD_INFO);
void GLCD_VidDisplaySinWave(u8 Copy_u8x, u8 copy_u8y, GLCD_t *GLCD_INFO);
void GLCD_VidDisplayHorizontalLine(u8 Copy_u8y, GLCD_t *GLCD_INFO);
void GLCD_VidGoToPixel(u8 Copy_u8Pixel, u8 copy_u8y, GLCD_t *GLCD_INFO);
void GLCD_VidGoToPY(u8 Copy_u8Page, u8 copy_u8y, GLCD_t *GLCD_INFO);
void GLCD_VidClearDisplay(GLCD_t *GLCD_INFO);
void GLCD_VidSendInteger(u64 copy_u64integer, u8 Copy_u8UnderlineStatus, u8 copy_u8y, GLCD_t *GLCD_INFO);
void GLCD_VidSendNumber(f64 copy_f64Number, GLCD_t *GLCD_INFO);
void GLCD_VidSendDecimal(f64 copy_f64decimal, GLCD_t *GLCD_INFO);
u8 GLCD_u8GetPage(u8 Copy_u8Pixel, u8 copy_u8y, GLCD_t *GLCD_INFO);

// standard ascii 5x7 font
// defines ascii characters 0x20-0x7F (32-127)
#if GLCD_FONT_SIZE == GLCD_FONT5x7
static const char Font5x7[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, // (space) 0
    0x00, 0x00, 0x5F, 0x00, 0x00, // ! 1              0 0 1 0 0
    0x00, 0x07, 0x00, 0x07, 0x00, // " 2              0 0 0 0 0
    0x14, 0x7F, 0x14, 0x7F, 0x14, // # 3              0 0 1 0 0
    0x24, 0x2A, 0x7F, 0x2A, 0x12, // $ 4              0 0 1 0 0
    0x23, 0x13, 0x08, 0x64, 0x62, // % 5              0 0 1 0 0
    0x36, 0x49, 0x55, 0x22, 0x50, // & 6              0 0 1 0 0
    0x00, 0x05, 0x03, 0x00, 0x00, // ' 7              0 0 1 0 0
    0x00, 0x1C, 0x22, 0x41, 0x00, // ( 8              0 0 1 0 0
    0x00, 0x41, 0x22, 0x1C, 0x00, // ) 9
    0x08, 0x2A, 0x1C, 0x2A, 0x08, // * 10
    0x08, 0x08, 0x3E, 0x08, 0x08, // + 11
    0x00, 0x50, 0x30, 0x00, 0x00, // , 12
    0x08, 0x08, 0x08, 0x08, 0x08, // - 13
    0x00, 0x60, 0x60, 0x00, 0x00, // . 14
    0x20, 0x10, 0x08, 0x04, 0x02, // / 15
    0x3E, 0x51, 0x49, 0x45, 0x3E, // 0 16
    0x00, 0x42, 0x7F, 0x40, 0x00, // 1 17
    0x42, 0x61, 0x51, 0x49, 0x46, // 2 18
    0x21, 0x41, 0x45, 0x4B, 0x31, // 3 19
    0x18, 0x14, 0x12, 0x7F, 0x10, // 4 20
    0x27, 0x45, 0x45, 0x45, 0x39, // 5 20
    0x3C, 0x4A, 0x49, 0x49, 0x30, // 6 21
    0x01, 0x71, 0x09, 0x05, 0x03, // 7 22
    0x36, 0x49, 0x49, 0x49, 0x36, // 8 23
    0x06, 0x49, 0x49, 0x29, 0x1E, // 9 24
    0x00, 0x36, 0x36, 0x00, 0x00, // : 25
    0x00, 0x56, 0x36, 0x00, 0x00, // ; 26
    0x00, 0x08, 0x14, 0x22, 0x41, // < 27
    0x14, 0x14, 0x14, 0x14, 0x14, // = 28
    0x41, 0x22, 0x14, 0x08, 0x00, // > 29
    0x02, 0x01, 0x51, 0x09, 0x06, // ? 30
    0x32, 0x49, 0x79, 0x41, 0x3E, // @ 31
    0x7E, 0x11, 0x11, 0x11, 0x7E, // A 32
    0x7F, 0x49, 0x49, 0x49, 0x36, // B 33
    0x3E, 0x41, 0x41, 0x41, 0x22, // C 34
    0x7F, 0x41, 0x41, 0x22, 0x1C, // D 35
    0x7F, 0x49, 0x49, 0x49, 0x41, // E 36
    0x7F, 0x09, 0x09, 0x01, 0x01, // F 37
    0x3E, 0x41, 0x41, 0x51, 0x32, // G 38
    0x7F, 0x08, 0x08, 0x08, 0x7F, // H 39
    0x00, 0x41, 0x7F, 0x41, 0x00, // I 40
    0x20, 0x40, 0x41, 0x3F, 0x01, // J 41
    0x7F, 0x08, 0x14, 0x22, 0x41, // K 42
    0x7F, 0x40, 0x40, 0x40, 0x40, // L 43
    0x7F, 0x02, 0x04, 0x02, 0x7F, // M 44
    0x7F, 0x04, 0x08, 0x10, 0x7F, // N 45
    0x3E, 0x41, 0x41, 0x41, 0x3E, // O 46
    0x7F, 0x09, 0x09, 0x09, 0x06, // P 47
    0x3E, 0x41, 0x51, 0x21, 0x5E, // Q 48
    0x7F, 0x09, 0x19, 0x29, 0x46, // R 49
    0x46, 0x49, 0x49, 0x49, 0x31, // S 50
    0x01, 0x01, 0x7F, 0x01, 0x01, // T 51
    0x3F, 0x40, 0x40, 0x40, 0x3F, // U 52
    0x1F, 0x20, 0x40, 0x20, 0x1F, // V 53
    0x7F, 0x20, 0x18, 0x20, 0x7F, // W 54
    0x63, 0x14, 0x08, 0x14, 0x63, // X 55
    0x03, 0x04, 0x78, 0x04, 0x03, // Y 56
    0x61, 0x51, 0x49, 0x45, 0x43, // Z 57
    0x00, 0x00, 0x7F, 0x41, 0x41, // [ 58
    0x02, 0x04, 0x08, 0x10, 0x20, // "\" 59
    0x41, 0x41, 0x7F, 0x00, 0x00, // ] 60
    0x04, 0x02, 0x01, 0x02, 0x04, // ^ 61
    0x40, 0x40, 0x40, 0x40, 0x40, // _ 62
    0x00, 0x01, 0x02, 0x04, 0x00, // ` 63
    0x20, 0x54, 0x54, 0x54, 0x78, // a 64
    0x7F, 0x48, 0x44, 0x44, 0x38, // b 65
    0x38, 0x44, 0x44, 0x44, 0x20, // c 66
    0x38, 0x44, 0x44, 0x48, 0x7F, // d 67
    0x38, 0x54, 0x54, 0x54, 0x18, // e 68
    0x08, 0x7E, 0x09, 0x01, 0x02, // f 69
    0x08, 0x14, 0x54, 0x54, 0x3C, // g 70
    0x7F, 0x08, 0x04, 0x04, 0x78, // h 71
    0x00, 0x44, 0x7D, 0x40, 0x00, // i 72
    0x20, 0x40, 0x44, 0x3D, 0x00, // j 73
    0x00, 0x7F, 0x10, 0x28, 0x44, // k 74
    0x00, 0x41, 0x7F, 0x40, 0x00, // l 75
    0x7C, 0x04, 0x18, 0x04, 0x78, // m 76
    0x7C, 0x08, 0x04, 0x04, 0x78, // n 77
    0x38, 0x44, 0x44, 0x44, 0x38, // o 78
    0x7C, 0x14, 0x14, 0x14, 0x08, // p 79
    0x08, 0x14, 0x14, 0x18, 0x7C, // q 80
    0x7C, 0x08, 0x04, 0x04, 0x08, // r 81
    0x48, 0x54, 0x54, 0x54, 0x20, // s 82
    0x04, 0x3F, 0x44, 0x40, 0x20, // t 83
    0x3C, 0x40, 0x40, 0x20, 0x7C, // u 84
    0x1C, 0x20, 0x40, 0x20, 0x1C, // v 85
    0x3C, 0x40, 0x30, 0x40, 0x3C, // w 86
    0x44, 0x28, 0x10, 0x28, 0x44, // x 87
    0x0C, 0x50, 0x50, 0x50, 0x3C, // y 88
    0x44, 0x64, 0x54, 0x4C, 0x44, // z 89
    0x00, 0x08, 0x36, 0x41, 0x00, // { 90
    0x00, 0x00, 0x7F, 0x00, 0x00, // | 91
    0x00, 0x41, 0x36, 0x08, 0x00, // } 92
    0x08, 0x08, 0x2A, 0x1C, 0x08, // -> 93
    0x08, 0x1C, 0x2A, 0x08, 0x08  // <- 94
};
#elif GLCD_FONT_SIZE == GLCD_FONT7x7
const u8 Font7x7[] =
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x5F, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00,
        0x14, 0x14, 0x7F, 0x14, 0x7F, 0x14, 0x14,
        0x04, 0x2A, 0x2A, 0x7F, 0x2A, 0x2A, 0x10,
        0x43, 0x23, 0x10, 0x08, 0x04, 0x62, 0x61,
        0x30, 0x4A, 0x45, 0x2A, 0x10, 0x28, 0x40,
        0x00, 0x00, 0x04, 0x03, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x3E, 0x41, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x41, 0x3E, 0x00, 0x00,
        0x00, 0x00, 0x0A, 0x07, 0x0A, 0x00, 0x00,
        0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00,
        0x00, 0x00, 0x40, 0x30, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x08, 0x08, 0x08, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
        0x00, 0x40, 0x30, 0x08, 0x06, 0x01, 0x00,
        0x3E, 0x61, 0x51, 0x49, 0x45, 0x43, 0x3E,
        0x00, 0x44, 0x42, 0x7F, 0x40, 0x40, 0x00,
        0x42, 0x61, 0x51, 0x49, 0x49, 0x45, 0x42,
        0x22, 0x41, 0x49, 0x49, 0x49, 0x49, 0x36,
        0x18, 0x14, 0x12, 0x7F, 0x10, 0x10, 0x00,
        0x4F, 0x49, 0x49, 0x49, 0x49, 0x49, 0x31,
        0x3E, 0x49, 0x49, 0x49, 0x49, 0x49, 0x32,
        0x41, 0x21, 0x11, 0x09, 0x05, 0x03, 0x00,
        0x36, 0x49, 0x49, 0x49, 0x49, 0x49, 0x36,
        0x26, 0x49, 0x49, 0x49, 0x49, 0x49, 0x3E,
        0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x40, 0x34, 0x00, 0x00, 0x00,
        0x08, 0x14, 0x14, 0x22, 0x22, 0x41, 0x41,
        0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
        0x41, 0x41, 0x22, 0x22, 0x14, 0x14, 0x08,
        0x02, 0x01, 0x01, 0x51, 0x09, 0x09, 0x06,
        0x3E, 0x41, 0x49, 0x55, 0x5D, 0x51, 0x0E,
        0x7E, 0x09, 0x09, 0x09, 0x09, 0x09, 0x7E,
        0x7F, 0x49, 0x49, 0x49, 0x49, 0x49, 0x36,
        0x3E, 0x41, 0x41, 0x41, 0x41, 0x41, 0x22,
        0x7F, 0x41, 0x41, 0x41, 0x41, 0x22, 0x1C,
        0x7F, 0x49, 0x49, 0x49, 0x49, 0x49, 0x49,
        0x7F, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09,
        0x3E, 0x41, 0x41, 0x49, 0x49, 0x49, 0x32,
        0x7F, 0x08, 0x08, 0x08, 0x08, 0x08, 0x7F,
        0x00, 0x41, 0x41, 0x7F, 0x41, 0x41, 0x00,
        0x00, 0x00, 0x20, 0x40, 0x3F, 0x00, 0x00,
        0x7F, 0x08, 0x14, 0x14, 0x22, 0x22, 0x41,
        0x7F, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
        0x7F, 0x02, 0x04, 0x08, 0x04, 0x02, 0x7F,
        0x7F, 0x02, 0x04, 0x08, 0x10, 0x20, 0x7F,
        0x3E, 0x41, 0x41, 0x41, 0x41, 0x41, 0x3E,
        0x7F, 0x09, 0x09, 0x09, 0x09, 0x09, 0x06,
        0x1E, 0x21, 0x21, 0x29, 0x31, 0x3E, 0x40,
        0x7F, 0x09, 0x19, 0x29, 0x46, 0x00, 0x00,
        0x26, 0x49, 0x49, 0x49, 0x49, 0x49, 0x32,
        0x01, 0x01, 0x01, 0x7F, 0x01, 0x01, 0x01,
        0x3F, 0x40, 0x40, 0x40, 0x40, 0x40, 0x3F,
        0x03, 0x0C, 0x30, 0x40, 0x30, 0x0C, 0x03,
        0x3F, 0x40, 0x40, 0x3F, 0x40, 0x40, 0x3F,
        0x41, 0x22, 0x14, 0x08, 0x14, 0x22, 0x41,
        0x01, 0x02, 0x04, 0x78, 0x04, 0x02, 0x01,
        0x41, 0x61, 0x51, 0x49, 0x45, 0x43, 0x41,
        0x00, 0x00, 0x7F, 0x41, 0x00, 0x00, 0x00,
        0x00, 0x01, 0x06, 0x08, 0x30, 0x40, 0x00,
        0x00, 0x00, 0x00, 0x41, 0x7F, 0x00, 0x00,
        0x00, 0x00, 0x02, 0x01, 0x02, 0x00, 0x00,
        0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
        0x00, 0x00, 0x00, 0x03, 0x04, 0x00, 0x00,
        0x00, 0x20, 0x54, 0x54, 0x54, 0x78, 0x00,
        0x00, 0x7F, 0x48, 0x48, 0x30, 0x00, 0x00,
        0x00, 0x30, 0x48, 0x48, 0x48, 0x00, 0x00,
        0x00, 0x30, 0x48, 0x48, 0x7F, 0x00, 0x00,
        0x00, 0x38, 0x54, 0x54, 0x54, 0x08, 0x00,
        0x00, 0x08, 0x7C, 0x0A, 0x02, 0x00, 0x00,
        0x00, 0x24, 0x4A, 0x4A, 0x3E, 0x00, 0x00,
        0x00, 0x7F, 0x08, 0x08, 0x70, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x20, 0x40, 0x3A, 0x00, 0x00,
        0x00, 0x7F, 0x10, 0x28, 0x44, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x3F, 0x40, 0x00, 0x00,
        0x70, 0x08, 0x08, 0x70, 0x08, 0x08, 0x70,
        0x00, 0x78, 0x08, 0x08, 0x70, 0x00, 0x00,
        0x00, 0x38, 0x44, 0x44, 0x44, 0x38, 0x00,
        0x00, 0x7C, 0x12, 0x12, 0x0C, 0x00, 0x00,
        0x00, 0x0C, 0x12, 0x12, 0x7C, 0x00, 0x00,
        0x00, 0x00, 0x70, 0x08, 0x08, 0x00, 0x00,
        0x00, 0x48, 0x54, 0x54, 0x24, 0x00, 0x00,
        0x00, 0x00, 0x08, 0x3E, 0x48, 0x00, 0x00,
        0x00, 0x38, 0x40, 0x40, 0x78, 0x00, 0x00,
        0x00, 0x18, 0x20, 0x40, 0x20, 0x18, 0x00,
        0x38, 0x40, 0x40, 0x38, 0x40, 0x40, 0x38,
        0x00, 0x44, 0x28, 0x10, 0x28, 0x44, 0x00,
        0x00, 0x06, 0x48, 0x48, 0x48, 0x3E, 0x00,
        0x00, 0x48, 0x68, 0x58, 0x48, 0x00, 0x00,
        0x00, 0x00, 0x08, 0x36, 0x41, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x41, 0x36, 0x08, 0x00, 0x00,
        0x08, 0x04, 0x04, 0x08, 0x08, 0x04, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x0E, 0x11, 0x11, 0x51, 0x11, 0x11, 0x0A,
        0x00, 0x3A, 0x40, 0x40, 0x7A, 0x00, 0x00,
        0x00, 0x38, 0x54, 0x56, 0x55, 0x08, 0x00,
        0x00, 0x20, 0x56, 0x55, 0x56, 0x78, 0x00,
        0x00, 0x20, 0x55, 0x54, 0x55, 0x78, 0x00,
        0x00, 0x20, 0x55, 0x56, 0x54, 0x78, 0x00,
        0x00, 0x20, 0x54, 0x55, 0x54, 0x78, 0x00,
        0x00, 0x0C, 0x12, 0x52, 0x12, 0x00, 0x00,
        0x00, 0x38, 0x56, 0x55, 0x56, 0x08, 0x00,
        0x00, 0x38, 0x55, 0x54, 0x55, 0x08, 0x00,
        0x00, 0x38, 0x55, 0x56, 0x54, 0x08, 0x00,
        0x00, 0x00, 0x02, 0x78, 0x02, 0x00, 0x00,
        0x00, 0x00, 0x04, 0x72, 0x04, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00,
        0x78, 0x14, 0x15, 0x14, 0x15, 0x14, 0x78,
        0x78, 0x14, 0x14, 0x15, 0x14, 0x14, 0x78,
        0x7C, 0x54, 0x54, 0x56, 0x55, 0x54, 0x54,
        0x20, 0x54, 0x54, 0x78, 0x38, 0x54, 0x4C,
        0x7E, 0x09, 0x09, 0x7F, 0x49, 0x49, 0x49,
        0x00, 0x38, 0x46, 0x45, 0x46, 0x38, 0x00,
        0x00, 0x38, 0x45, 0x44, 0x45, 0x38, 0x00,
        0x00, 0x38, 0x45, 0x46, 0x44, 0x38, 0x00,
        0x00, 0x3A, 0x41, 0x41, 0x7A, 0x00, 0x00,
        0x00, 0x38, 0x41, 0x42, 0x78, 0x00, 0x00,
        0x00, 0x44, 0x44, 0x7D, 0x44, 0x44, 0x00,
        0x38, 0x44, 0x45, 0x44, 0x45, 0x44, 0x38,
        0x3D, 0x40, 0x40, 0x40, 0x40, 0x40, 0x3D,
        0x40, 0x3C, 0x32, 0x2A, 0x26, 0x1E, 0x01,
        0x44, 0x7E, 0x45, 0x41, 0x41, 0x22, 0x00,
        0x3E, 0x51, 0x51, 0x49, 0x45, 0x45, 0x3E,
        0x12, 0x15, 0x15, 0x55, 0x15, 0x15, 0x08,
        0x00, 0x02, 0x15, 0x55, 0x15, 0x08, 0x00,
        0x00, 0x20, 0x54, 0x56, 0x55, 0x78, 0x00,
        0x00, 0x00, 0x00, 0x7A, 0x01, 0x00, 0x00,
        0x00, 0x38, 0x44, 0x46, 0x45, 0x38, 0x00,
        0x00, 0x38, 0x42, 0x41, 0x78, 0x00, 0x00,
        0x00, 0x7A, 0x09, 0x0A, 0x71, 0x00, 0x00,
        0x7E, 0x05, 0x09, 0x12, 0x22, 0x7D, 0x00,
        0x39, 0x46, 0x56, 0x56, 0x56, 0x65, 0x00,
        0x00, 0x08, 0x55, 0x56, 0x3D, 0x00, 0x00,
        0x30, 0x48, 0x48, 0x45, 0x40, 0x40, 0x20,
        0x3E, 0x41, 0x7D, 0x55, 0x6D, 0x41, 0x3E,
        0x00, 0x04, 0x04, 0x04, 0x04, 0x1C, 0x00,
        0x4A, 0x2F, 0x18, 0x08, 0x4C, 0x6A, 0x51,
        0x4A, 0x2F, 0x18, 0x28, 0x34, 0x7A, 0x21,
        0x00, 0x00, 0x00, 0x7D, 0x00, 0x00, 0x00,
        0x00, 0x08, 0x14, 0x00, 0x08, 0x14, 0x00,
        0x00, 0x14, 0x08, 0x00, 0x14, 0x08, 0x00,
        0x55, 0x00, 0x55, 0x00, 0x55, 0x00, 0x55,
        0x2A, 0x55, 0x2A, 0x55, 0x2A, 0x55, 0x2A,
        0x2A, 0x7F, 0x2A, 0x7F, 0x2A, 0x7F, 0x2A,
        0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00,
        0x08, 0x08, 0x08, 0x7F, 0x00, 0x00, 0x00,
        0x78, 0x16, 0x15, 0x14, 0x14, 0x14, 0x78,
        0x78, 0x16, 0x15, 0x15, 0x15, 0x16, 0x78,
        0x78, 0x14, 0x14, 0x14, 0x15, 0x16, 0x78,
        0x3E, 0x41, 0x49, 0x55, 0x55, 0x41, 0x3E,
        0x14, 0x14, 0x77, 0x00, 0x7F, 0x00, 0x00,
        0x00, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x00,
        0x14, 0x14, 0x74, 0x04, 0x7C, 0x00, 0x00,
        0x14, 0x14, 0x17, 0x10, 0x1F, 0x00, 0x00,
        0x00, 0x0C, 0x12, 0x33, 0x12, 0x00, 0x00,
        0x00, 0x01, 0x2A, 0x7C, 0x2A, 0x01, 0x00,
        0x08, 0x08, 0x08, 0x78, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x0F, 0x08, 0x08, 0x08,
        0x08, 0x08, 0x08, 0x0F, 0x08, 0x08, 0x08,
        0x08, 0x08, 0x08, 0x78, 0x08, 0x08, 0x08,
        0x00, 0x00, 0x00, 0x7F, 0x08, 0x08, 0x08,
        0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
        0x08, 0x08, 0x08, 0x7F, 0x08, 0x08, 0x08,
        0x00, 0x20, 0x56, 0x55, 0x56, 0x79, 0x00,
        0x7A, 0x15, 0x15, 0x16, 0x16, 0x15, 0x78,
        0x00, 0x00, 0x1F, 0x10, 0x17, 0x14, 0x14,
        0x00, 0x00, 0x7E, 0x02, 0x7A, 0x0A, 0x0A,
        0x14, 0x14, 0x17, 0x10, 0x17, 0x14, 0x14,
        0x14, 0x14, 0x74, 0x04, 0x74, 0x14, 0x14,
        0x00, 0x00, 0x7F, 0x00, 0x77, 0x14, 0x14,
        0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
        0x14, 0x14, 0x77, 0x00, 0x77, 0x14, 0x14,
        0x41, 0x3E, 0x22, 0x22, 0x22, 0x3E, 0x41,
        0x00, 0x12, 0x15, 0x12, 0x00, 0x00, 0x00,
        0x00, 0x12, 0x15, 0x17, 0x00, 0x00, 0x00,
        0x7C, 0x56, 0x55, 0x55, 0x55, 0x56, 0x54,
        0x7C, 0x54, 0x55, 0x54, 0x55, 0x54, 0x54,
        0x7C, 0x54, 0x55, 0x56, 0x54, 0x54, 0x54,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x48, 0x7A, 0x49, 0x00, 0x00,
        0x00, 0x00, 0x4A, 0x79, 0x4A, 0x00, 0x00,
        0x00, 0x00, 0x4A, 0x78, 0x4A, 0x00, 0x00,
        0x08, 0x08, 0x08, 0x0F, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x78, 0x08, 0x08, 0x08,
        0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
        0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78,
        0x00, 0x00, 0x00, 0x77, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x49, 0x7A, 0x48, 0x00, 0x00,
        0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
        0x38, 0x44, 0x44, 0x46, 0x45, 0x44, 0x38,
        0x7E, 0x01, 0x09, 0x49, 0x49, 0x49, 0x36,
        0x38, 0x44, 0x46, 0x45, 0x46, 0x44, 0x38,
        0x38, 0x44, 0x45, 0x46, 0x44, 0x44, 0x38,
        0x00, 0x3A, 0x45, 0x46, 0x45, 0x38, 0x00,
        0x3A, 0x45, 0x45, 0x46, 0x46, 0x45, 0x38,
        0x00, 0x7C, 0x20, 0x20, 0x1C, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x22, 0x14, 0x08, 0x14, 0x22, 0x00,
        0x3C, 0x40, 0x40, 0x42, 0x41, 0x40, 0x3C,
        0x3C, 0x40, 0x42, 0x41, 0x42, 0x40, 0x3C,
        0x3C, 0x40, 0x41, 0x42, 0x40, 0x40, 0x3C,
        0x00, 0x00, 0x01, 0x7A, 0x00, 0x00, 0x00,
        0x00, 0x0D, 0x50, 0x50, 0x50, 0x3D, 0x00,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00,
        0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00,
        0x00, 0x00, 0x24, 0x2E, 0x24, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x55, 0x35, 0x1A, 0x28, 0x34, 0x7A, 0x21,
        0x02, 0x05, 0x7F, 0x01, 0x7F, 0x00, 0x00,
        0x0A, 0x55, 0x55, 0x55, 0x55, 0x55, 0x28,
        0x00, 0x08, 0x08, 0x2A, 0x08, 0x08, 0x00,
        0x00, 0x00, 0x40, 0x50, 0x20, 0x00, 0x00,
        0x00, 0x00, 0x02, 0x05, 0x02, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x12, 0x1F, 0x10, 0x00, 0x00,
        0x00, 0x00, 0x15, 0x15, 0x0E, 0x00, 0x00,
        0x00, 0x00, 0x12, 0x19, 0x16, 0x00, 0x00,
        0x00, 0x00, 0x1C, 0x1C, 0x1C, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
#endif

#endif
