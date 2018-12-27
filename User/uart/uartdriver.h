#ifndef __UART_DRIVER_H
#define __UART_DRIVER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_usart.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_rcc.h"


/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
#define UART_BUFF_MAX 20

#define UART_PROTOCOL_MIN 7

#define Receive_Data_is_String
/* Exported macro ------------------------------------------------------------*/

#define UART_GPIO_RCC RCC_AHBPeriph_GPIOB

#define UART_GPIO GPIOB

#define UART_TX_PIN GPIO_Pin_6
#define UART_TX_PINSOURCE GPIO_PinSource6

#define UART_RX_PIN GPIO_Pin_7
#define UART_RX_PINSOURCE GPIO_PinSource7

#define UART USART1
#define UART_BAUDRATE 9600
#define UART_IRQ USART1_IRQn
#define UART_RCC RCC_APB2Periph_USART1

typedef struct
{
	unsigned char ReceiveBuff[UART_BUFF_MAX];
	unsigned char ReceiveLen;
	unsigned char ReceiveFinishFlag;

	unsigned char TranmitBuff[UART_BUFF_MAX];
	unsigned char TranmitLen;
	unsigned char TranmitFinishFlag;
}UART_STRUCT;


/* Exported functions ------------------------------------------------------- */

void UART_Init(void);

void UART_GPIO_Init(void);

void UART_ATT_Config(void);

void UART_NVIC_Init(void);

void USART1_IRQHandler(void);

void UART_ReceiveData(unsigned char String);

#endif /* __UART_DRIVER_H */

