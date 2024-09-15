
/****************************************************************************
*****************************************************************************
*******************   SWC    :       SSD Driver         *********************
*******************    By    : Youssef Mostafa Mohamed  *********************
*******************   Date   :       3/9/2022          *********************
*******************  Version :          V1.0            *********************
*****************************************************************************
****************************************************************************/

#ifndef _SSD_CONFIG_H_
#define _SSD_CONFIG_H_

/* Please Select one of the following
 * 01 - COM - CATHODE
 * 02 - COM - ANODE */

/* For seven segment '0' */

#define SSD0_TYPE COMCATH
#define SSD0_PORT Port_A

#define SSD0_SEG_A_PIN Pin_0
#define SSD0_SEG_B_PIN Pin_1
#define SSD0_SEG_C_PIN Pin_2
#define SSD0_SEG_D_PIN Pin_3
#define SSD0_SEG_E_PIN Pin_4
#define SSD0_SEG_F_PIN Pin_5
#define SSD0_SEG_G_PIN Pin_6
#define SSD0_SEG_H_PIN Pin_7

/* For seven segment '1' */

#define SSD1_TYPE COMCATH
#define SSD1_PORT Port_C

#define SSD1_SEG_A_PIN Pin_0
#define SSD1_SEG_B_PIN Pin_1
#define SSD1_SEG_C_PIN Pin_2
#define SSD1_SEG_D_PIN Pin_3
#define SSD1_SEG_E_PIN Pin_4
#define SSD1_SEG_F_PIN Pin_5
#define SSD1_SEG_G_PIN Pin_6
#define SSD1_SEG_H_PIN Pin_7

#endif
