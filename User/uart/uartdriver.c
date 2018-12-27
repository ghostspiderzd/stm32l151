#include "uartdriver.h"
#include "stm32l1xx_usart.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_rcc.h"
#include "main.h"

UART_STRUCT gUART_Struct;

void UART_Init()
{

	RCC_APB2PeriphClockCmd(UART_RCC,ENABLE);
	RCC_AHBPeriphClockCmd(UART_GPIO_RCC,ENABLE);

	UART_GPIO_Init();
	UART_NVIC_Init();
	UART_ATT_Config();
	gUART_Struct.ReceiveLen = 0;
	gUART_Struct.ReceiveFinishFlag = RESET;
}


void UART_GPIO_Init()
{
	GPIO_InitTypeDef   GPIO_InitStructure;
			 			
	GPIO_InitStructure.GPIO_Pin=UART_TX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;	
	GPIO_Init(UART_GPIO,&GPIO_InitStructure);
			
	GPIO_InitStructure.GPIO_Pin=UART_RX_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(UART_GPIO,&GPIO_InitStructure);

}

void UART_ATT_Config()
{
	USART_InitTypeDef USART_InitStructure;

	USART_InitStructure.USART_BaudRate=UART_BAUDRATE;
    USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_StopBits=USART_StopBits_1;
    USART_InitStructure.USART_Parity=USART_Parity_No;
    USART_InitStructure.USART_WordLength=USART_WordLength_8b;
    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;

	GPIO_PinAFConfig(UART_GPIO, UART_TX_PINSOURCE, GPIO_AF_USART1);
	GPIO_PinAFConfig(UART_GPIO, UART_RX_PINSOURCE, GPIO_AF_USART1);
	
    USART_Init(UART,&USART_InitStructure);
    USART_ITConfig(UART,USART_IT_RXNE,ENABLE);    
	USART_ITConfig(UART,USART_IT_IDLE,ENABLE);    
	
    USART_Cmd(UART,ENABLE);
}


void UART_NVIC_Init()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


void USART1_IRQHandler()
{
	UART_STRUCT *pUART_Struct = &gUART_Struct;
	 if(USART_GetITStatus(UART,USART_IT_RXNE)== SET)
     {
     	USART_ClearITPendingBit(UART,USART_IT_RXNE);
		UART_ReceiveData(USART_ReceiveData(USART1));
	 }
	 if(USART_GetITStatus(UART,USART_IT_IDLE)== SET)
	 {
		USART1->SR;
		USART1->DR;
		pUART_Struct->ReceiveFinishFlag = SET;
		pUART_Struct->ReceiveLen = 0;
	 }
}

void UART_ReceiveData(unsigned char String)
{
	UART_STRUCT *pUART_Struct = &gUART_Struct;
	if(String != NULL)
	{
		if(pUART_Struct->ReceiveLen < UART_BUFF_MAX)
		{
			pUART_Struct->ReceiveBuff[pUART_Struct->ReceiveLen++] = String;
		}
		else
		{
			pUART_Struct->ReceiveLen = 0;
		}
	}
}

























