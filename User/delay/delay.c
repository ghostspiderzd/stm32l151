#include "delay.h"
#include "stm32l1xx.h"


void Delay_ms(int ms)
{
	//ms
	unsigned char i;
	while(ms--)
	{
		for(i = 0;i < 10;i++)
		{
			Delay_us(100);
		}
	}
}


void Delay_us(unsigned char us)
{
	//1us
	unsigned char i;
	for(i=0;i<us;i++)
	{
		__NOP();__NOP();
	}
}































