
/****************************************************************************
*****************************************************************************
*******************   SWC    :       SSD Driver         *********************
*******************    By    : Youssef Mostafa Mohamed  *********************
*******************   Date   :       3/9/2022          *********************
*******************  Version :          V1.0            *********************
*****************************************************************************
****************************************************************************/

#ifndef _SSD_INTERFACE_H_
#define _SSD_INTERFACE_H_

#define SSD_ID0 0
#define SSD_ID1 1
#define SSD_ID2 2
#define SSD_ID3 3
#define SSD_ID4 4

void SSD_VidInit(u8 SSD_Copy_u8Id);
void SSD_VidDisplayNumber(u8 SSD_Copy_u8Id, u8 Copy_u8Number);
void SSD_VidTurnOff(u8 SSD_Copy_u8Id);

#endif
