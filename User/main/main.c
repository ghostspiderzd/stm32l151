
#include <stdio.h>
#include "main.h"
#include "stm32l1xx.h"
#include "delay.h"
#include "resistance_level_driver.h"
#include "motor_driver.h"
#include "key.h"
#include "uartdriver.h"
#include "protocol.h"
#include "uart.h"


extern UART_STRUCT gUART_Struct;
int main()
{
//	RCC_ClocksTypeDef get_rcc_clock;
	SystemInit();
//	RCC_GetClocksFreq(&get_rcc_clock); 
	Resistance_Level_ADC_Init();  //检测阻力等级ADC初始化
	Motor_GPIO_Init();
	Motor_Stop();
	//Key_GPIO_Init();
	UART_Init();
	DEBUG_LOG("Init finish");
	while(1)
	{
		Logic();
	}
}


void Logic()
{
	UART_STRUCT *pUART_Struct = &gUART_Struct;
	if(pUART_Struct->ReceiveFinishFlag != RESET)
		{
			pUART_Struct->ReceiveFinishFlag = RESET;
			PROTOCOL_DataAnalysis(pUART_Struct->ReceiveBuff);
		}
}
