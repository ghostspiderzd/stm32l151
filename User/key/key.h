#ifndef __KEY_H
#define __KEY_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_gpio.h"

/* Exported types ------------------------------------------------------------*/
#define KEY_GPIO_RCC RCC_AHBPeriph_GPIOB
#define KEY_GPIO_INPUT GPIOB 
#define KEY1_PIN GPIO_Pin_8
#define KEY2_PIN GPIO_Pin_9

#define KEY1_STATUS GPIO_ReadInputDataBit(KEY_GPIO_INPUT,KEY1_PIN)
#define KEY2_STATUS GPIO_ReadInputDataBit(KEY_GPIO_INPUT,KEY2_PIN)


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void Key_GPIO_Init(void);


#endif 

