#ifndef ADC_INIT_H
#define ADC_INIT_H

typedef struct
{
    u8 CHAIN_ID;
    u8 SIZE;
    u8 *Channel_Ids;
    u16 *RESULTS;
    void (*NOTIFICATION_FUNCTION)(void);
} ADC_CHAIN;

/* ADC INIT FUNC */
void ADC_VidInit(void);

/* Synchronous Functions */
u8 ADC_u8StartConversionSynchronous(u8 copy_u8channel, u16 *copy_pu16Reading);

/* Asynchronous Functions */
u8 ADC_u8StartConversionAsynchronous(u8 copy_u8channel, u16 *copy_pu16Reading, void (*copy_pvNotificationFunction)(u16));

/* Asynchronous ChainConversion Functions */
u8 ADC_StartChainConversion(ADC_CHAIN *Copy_ADC_CHAIN);

#endif
