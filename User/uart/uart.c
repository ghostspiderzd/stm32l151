#include "uart.h"
#include "uartdriver.h"
#include "main.h"
#include "string.h"

void UART_Debug(const char *String)
{
	unsigned char Len = strlen(String);
	if(*String != NULL)
	{
		while(Len--)
		{
			while(USART_GetFlagStatus(UART,USART_FLAG_TC ) != SET);
			USART_SendData(UART,*String++);
		}
	}
}


void UART_SendData(unsigned char *String,unsigned char Len)
{
	if(*String != NULL)
	{
		while(Len--)
		{
			while(USART_GetFlagStatus(UART,USART_FLAG_TC ) != SET);
			USART_SendData(UART,*String++);
		}
	}
}





































