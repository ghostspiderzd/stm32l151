#include "protocol.h"
#include "uart.h"
#include "uartdriver.h"
#include "motor_driver.h"
#include "main.h"
#include "resistance_level_driver.h"

#include <stdlib.h>
#include <string.h>

ENUM_FUNCTION gEnum_Function = INIT_VALUE;
extern UART_STRUCT gUART_Struct;
unsigned char gPackageString[10];

unsigned char PROTOCOL_DataAnalysis(unsigned char *String)
{
	unsigned char i =0 ;
	unsigned char Len = 0;
	unsigned char Checkout = 0;
//	unsigned char ReturnOK[15]= RETURN_SUB_OK;
//	unsigned char ReturnERR[15]= RETURN_SUB_ERROR;
	unsigned char Hex_String[15];
	UART_STRUCT *pUART_Struct = &gUART_Struct;
	memset(Hex_String,'0',15);
	if(*String != NULL)
	{
		#ifdef Receive_Data_is_String
		HexStr2Integer((char *)String,(char *)Hex_String,strlen((const char *)String));
		#endif
		for(i = 0;i <= (UART_BUFF_MAX - UART_PROTOCOL_MIN);i++)
		{
			if((Hex_String[i] == 0xAA)&&(Hex_String[i+1] == 0x55))  //检查帧头
			{
				Len = Hex_String[2];
				Checkout = Hex_String[2];
				for(i = 1;i < Len-1;i++)       
				{
					Checkout ^= Hex_String[2+i];
				}
				if(Checkout == Hex_String[2 + Len-1])            //检查校验位
				{
					PROTOCOL_FunctionAnalysis(Hex_String+3);  //功能解析
					return 0;
				}
				else UART_SendData(ERROR_4,strlen(ERROR_4));
			}
		}
		UART_SendData(ERROR_1,strlen(ERROR_1)); //没有帧头，数据格式错误
		memset(pUART_Struct->ReceiveBuff,'0',UART_BUFF_MAX);	
	}
	return 0;
}


void PROTOCOL_FunctionAnalysis(unsigned char *String)
{
	UART_STRUCT *pUART_Struct = &gUART_Struct;
	unsigned char *pPackageString = gPackageString;
	if(*String != NULL)
	{
		switch(String[0])
		{
			case 0x01: //RESISTANCE_VALUE
				switch(String[1])
				{
					case 0x01: //puls
						gEnum_Function = RESISTANCE_VALUE_PULS;
						UART_SendData(RETURN_PULS_OK,strlen(RETURN_PULS_OK));
						Motor_ResistanceAdjustment(RESISTANCE_VALUE_PULS,String[2]);
					break;
					case 0x02: //minus
						gEnum_Function = RESISTANCE_VALUE_MINUS;
						UART_SendData(RETURN_SUB_OK,strlen(RETURN_SUB_OK));
						Motor_ResistanceAdjustment(RESISTANCE_VALUE_MINUS,String[2]);
					break;
					case 0x03:
						gEnum_Function =RESISTANCE_VALUE_RETURN;
						PROTOCOL_ReturnResistanceValue();
						IntToHexChar(pUART_Struct->TranmitBuff,pPackageString,strlen((const char*)pPackageString));
						UART_SendData(pUART_Struct->TranmitBuff,strlen((const char*)pUART_Struct->TranmitBuff));
						memset(pUART_Struct->TranmitBuff,'0',strlen((const char *)pUART_Struct->TranmitBuff));
					break;
					default :
					break;
				}
			break;
			case 0x02: //MILEAGE
				switch(String[1])
				{
					case 0x01: //set
						gEnum_Function = MILEAGE_SET;
					break;
					case 0x02: //get
						gEnum_Function = MILEAGE_GET;
					break;
					default :
					break;
				}
			break;
			case 0x03: //RUN
				switch(String[1])
				{
					case 0x01: //start
						gEnum_Function = RUN_START;
					break;
					case 0x02: //stop
						gEnum_Function = RUN_STOP;
					break;
					case 0x03: //get
						gEnum_Function = RUN_GET;
					default :
					break;
				}
			break;
			default :
				UART_SendData(ERROR_2,strlen(ERROR_2));
			break;
		}
	}
}

void PROTOCOL_ReturnResistanceValue()
{
	unsigned char Package[10];
	unsigned char i;
	unsigned char CheckBit = 0;
	unsigned char *pPackageString = gPackageString;
	memset(Package,'\0',10);
	Package[0] = 0x55;
	Package[1] = 0xAA;
	Package[2] = 0x05;
	Package[3] = 0x01;
	Package[4] = 0x03;
	Package[5]= Get_Resistance_Level_VValue();
	CheckBit = 0x05;
	for(i = 0;i < 4;i++)
	{
		CheckBit ^= Package[3 + i];
	}
	Package[6]= CheckBit;
	memcpy(pPackageString,Package,sizeof(Package));
}


void IntToHexChar(unsigned char *ReturnStr,unsigned char *HexStr,unsigned char len)
{
	unsigned char i = 0;
	unsigned char temp = 0;
	for(i = 0;i < len;i++)
	{
		temp = (HexStr[i] & 0xF0) >> 4;  //0xFE & 0XF0 -> 0XF0 >>4 -> 0X0F
		if (temp > 9) temp = temp + 55;	
		else temp = temp + 0x30;
		ReturnStr[2*i] = temp;
		temp = HexStr[i] & 0x0F;
		if (temp > 9) temp = temp + 55;	
		else temp = temp + 0x30;
		ReturnStr[2*i+1] = temp;
	}
}


char HexStr2Integer(char *in,char *out ,int len)
{
    char *str = (char *)malloc(len);
	int i;
    memset(str, 0, len);
    memcpy(str, in, len);
    for (i = 0; i < len; i+=2) {
        //小写转大写
        if(str[i] >= 'a' && str[i] <= 'f') str[i] = str[i] & ~0x20;
        if(str[i+1] >= 'a' && str[i] <= 'f') str[i+1] = str[i+1] & ~0x20;
        //处理第前4位
        if(str[i] >= 'A' && str[i] <= 'F')
            out[i/2] = (str[i]-'A'+10)<<4;
        else
            out[i/2] = (str[i] & ~0x30)<<4;
        //处理后4位, 并组合起来
        if(str[i+1] >= 'A' && str[i+1] <= 'F')
            out[i/2] |= (str[i+1]-'A'+10);
        else
            out[i/2] |= (str[i+1] & ~0x30);
    }
    free(str);
    return 0;
}






















