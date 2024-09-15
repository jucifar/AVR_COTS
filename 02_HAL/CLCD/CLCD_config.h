#ifndef CLCD_CONFIG_H
#define CLCD_CONFIG_H

/*
CLCD_1_LINE_MODE
CLCD_2_LINE_MODE
*/
#define CLCD_LINE_MODE CLCD_2_LINE_MODE

/*
CLCD_FONT_5_8
CLCD_FONT_5_11
*/
#define CLCD_FONT_SIZE CLCD_FONT_5_11

/*
CLCD_ENABLE_DISPLAY
CLCD_DISABLE_DISPLAY
*/
#define CLCD_DISPLAY_STATUS CLCD_ENABLE_DISPLAY

/*
CLCD_ENABLE_CURSOR
CLCD_DISABLE_CURSOR
*/
#define CLCD_CURSOR_STATUS CLCD_ENABLE_CURSOR

/*
CLCD_ENABLE_CURSOR_PLINK
CLCD_DISABLE_CURSOR_PLINK
*/
#define CLCD_CURSOR_PLINK_STATUS CLCD_ENABLE_CURSOR_PLINK

/*
CLCD_CURSOR_INCREMENT
CLCD_CURSOR_DECREMENT
*/
#define CLCD_CURSOR_ACTION CLCD_CURSOR_INCREMENT

/*
CLCD_DISPLAY_SHIFT_RIGHT
CLCD_DISPLAY_SHIFT_LEFT
*/
#define CLCD_DISPLAY_ACTION CLCD_DISPLAY_SHIFT_RIGHT

#endif
