#include "key.h"
#include "stm32l1xx.h"
#include "stm32l1xx_rcc.h"
#include "stm32l1xx_gpio.h"


void Key_GPIO_Init()
{
  GPIO_InitTypeDef        GPIO_InitStructure;
	  /* GPIOD Periph clock enable */
  RCC_AHBPeriphClockCmd(KEY_GPIO_RCC, ENABLE);

  /* Configure PD0 and PD1 or PD3 and PD7 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = KEY1_PIN | KEY2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(KEY_GPIO_INPUT, &GPIO_InitStructure);
}





























