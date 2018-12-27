#ifndef __PROTOCOL_H
#define __PROTOCOL_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
	INIT_VALUE = 0,
	RESISTANCE_VALUE_MINUS,          //阻力减
	RESISTANCE_VALUE_PULS,         //阻力加
	RESISTANCE_VALUE_RETURN,		//返回阻力值
	MILEAGE_SET,                    //设置里程数
	MILEAGE_GET,                    //获取里程数
 	RUN_START,                      //启动运行
 	RUN_STOP,					    //停止运行
 	RUN_GET,						//获取运行状态
}ENUM_FUNCTION;
extern ENUM_FUNCTION gEnum_Function;

/* Exported constants --------------------------------------------------------*/

#define RETURN_PULS_OK "55AA050101FEFB"
#define RETURN_PULS_ERROR "55AA050101FFFA"

#define RETURN_SUB_OK "55AA050201FEF8"
#define RETURN_SUB_ERROR "55AA050201FFF9"

#define ERROR_1 "ERROR_1\r\n"	//数据格式错误
#define ERROR_2 "ERROR_2\r\n"	//功能码错误
#define ERROR_3 "ERROR_3\r\n"	//参数错误
#define ERROR_4 "ERROR_4\r\n"	//校验位错误


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

unsigned char PROTOCOL_DataAnalysis(unsigned char *String);
void PROTOCOL_FunctionAnalysis(unsigned char *String);
char HexStr2Integer(char *in,char *out ,int len);
void IntToHexChar(unsigned char *ReturnStr,unsigned char *HexStr,unsigned char len);
void PROTOCOL_ReturnResistanceValue(void);


#endif /* __MAIN_H */

