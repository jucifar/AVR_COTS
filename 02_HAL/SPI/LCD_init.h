/****************************************************************************
 ****************************************************************************
 *******************   SWC    :        LCD_INIT          ********************
 *******************    By    : Youssef Mostafa Mohamed  ********************
 *******************   Date   :       9/9/2022          ********************
 *******************  Version :          V1.0            ********************
 ****************************************************************************
 ***************************************************************************/
#ifndef LCD_INIT_H
#define LCD_INIT_H

void LCD_VidSendData(u8 copy_u8Data);
void LCD_VidSendCommand(u8 copy_u8Command);
void LCD_VidInit();
void LCD_VidDisplayName(u8 *copy_u8name);
void LCD_VidGoTo(u8 copy_u8X, u8 copy_u8Y);
void LCD_VidClearDisplay(void);
void LCD_VidCreateSpecialChar(u8 *pattern, u8 pattern_num);
void LCD_VidSendSpecialChar(u8 copy_u8pattern, u8 copy_u8X, u8 copy_u8Y);
void LCD_VidSendInteger(u64 copy_u64intger);
void LCD_VidSendNumber(f64 copy_f64Number);
void LCD_VidSendDecimal(f64 copy_f64decemal);

#endif
