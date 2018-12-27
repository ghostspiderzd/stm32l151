#ifndef __UART_H
#define __UART_H

/* Includes ------------------------------------------------------------------*/


/* Exported types ------------------------------------------------------------*/
#define DEBUG_LOG(String)						\
	if(DEFAULT_LOG_LEVEL >= LOG_LEVEL_DEBUG) 	\
		{										\
			UART_Debug(#String); 				\
		}

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void UART_SendData(unsigned char *String,unsigned char Len);
void UART_Debug(const char *String);



#endif /* __UART_H */

