#include "stm32l1xx.h"
#include "stm32l1xx_rcc.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_adc.h"
#include "resistance_level_driver.h"
#include "delay.h"

void Resistance_Level_ADC_Init()
{

 ADC_InitTypeDef           ADC_InitStructure;
 GPIO_InitTypeDef          GPIO_InitStructure;
	  /* Enable The HSI (16Mhz) */
  RCC_HSICmd(ENABLE);
  
  /* Check that HSI oscillator is ready */
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
   
  /* Configure RV3 input voltage */

  /* Enable the GPIOF Clock */
  RCC_AHBPeriphClockCmd(RESISTANCE_LEVEL_RCC, ENABLE);

  GPIO_InitStructure.GPIO_Pin = RESISTANCE_LEVEL_PIN;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(RESISTANCE_LEVEL_GPIO, &GPIO_InitStructure);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  /* ADC1 DeInit */  
  ADC_DeInit(ADC1);
//  ADC_TempSensorVrefintCmd(ENABLE);
  /* ADC1 Configuration of channel18/31 and channel5/1b : continuous mode, external trigger (TIM2) */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
 // ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T2_TRGO;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 Regular Channel Config */
  ADC_RegularChannelConfig(ADC1, RESISTANCE_LEVEL_ADC_CHANNEL, 1, ADC_SampleTime_192Cycles);

  /* Enables the ADC1 Power Down during Delay */ 
//  ADC_PowerDownCmd(ADC1, ADC_PowerDown_Idle_Delay, ENABLE);
  
  /* Delay until the converted data has been read */
//  ADC_DelaySelectionConfig(ADC1, ADC_DelayLength_Freeze);

  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);     
  
  /* Wait until the ADC1 is ready */
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
  {
  }

}




int Get_Resistance_Level_VValue()
{
	int temp = 0;
	unsigned char i = 0;
	for(i = 0; i < 8;i++)
	{
		ADC_SoftwareStartConv(ADC1);
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
		temp += ADC_GetConversionValue(ADC1);
		Delay_ms(10);
	}
	temp = temp / 8;
	temp = temp*3.27/4096*100;
	temp /= 16;
	return temp;
}
























