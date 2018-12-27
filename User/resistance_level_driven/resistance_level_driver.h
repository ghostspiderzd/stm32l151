#ifndef __RESISTANCE_LEVEL_DRIVER_H
#define __RESISTANCE_LEVEL_DRIVER_H

#define RESISTANCE_LEVEL_RCC RCC_AHBPeriph_GPIOA
#define RESISTANCE_LEVEL_GPIO GPIOA
#define RESISTANCE_LEVEL_PIN GPIO_Pin_4
#define RESISTANCE_LEVEL_ADC_CHANNEL ADC_Channel_4
#define INTERNAL_REF_ADC_CHANNEL ADC_Channel_17

















void Resistance_Level_ADC_Init(void);
int Get_Resistance_Level_VValue(void);


#endif

