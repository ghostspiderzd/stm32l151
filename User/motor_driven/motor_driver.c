#include "stm32l1xx.h"
#include "stm32l1xx_rcc.h"
#include "stm32l1xx_gpio.h"
#include "motor_driver.h"
#include "delay.h"
#include "protocol.h"
#include "main.h"

void Motor_GPIO_Init()
{
  GPIO_InitTypeDef        GPIO_InitStructure;
	  /* GPIOD Periph clock enable */
  RCC_AHBPeriphClockCmd(MOTOR_GPIO_RCC, ENABLE);

  /* Configure PD0 and PD1 or PD3 and PD7 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = MOTOR_PIN_INPUTA | MOTOR_PIN_INPUTB;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(MOTOR_GPIO_INPUT, &GPIO_InitStructure);

}

void Motor_Stop()
{
	GPIO_ResetBits(MOTOR_GPIO_INPUT,MOTOR_PIN_INPUTA);	 //INPUTA L
	GPIO_ResetBits(MOTOR_GPIO_INPUT,MOTOR_PIN_INPUTB);   //INPUTB L
}

void Motor_Forward()
{
	GPIO_SetBits(MOTOR_GPIO_INPUT,MOTOR_PIN_INPUTA);	 //INPUTA H
	GPIO_ResetBits(MOTOR_GPIO_INPUT,MOTOR_PIN_INPUTB);	 //INPUTB L
}

void Motor_Reverse()
{
	GPIO_ResetBits(MOTOR_GPIO_INPUT,MOTOR_PIN_INPUTA);	 //INPUTA L
	GPIO_SetBits(MOTOR_GPIO_INPUT,MOTOR_PIN_INPUTB);	 //INPUTB H
}

void Motor_Brake()
{
	GPIO_SetBits(MOTOR_GPIO_INPUT,MOTOR_PIN_INPUTA);	 //INPUTA H
	GPIO_SetBits(MOTOR_GPIO_INPUT,MOTOR_PIN_INPUTB);	 //INPUTB H
}

void Motor_ResistanceAdjustment(unsigned char Set,unsigned char ResistanceValue)
{
	if(ResistanceValue != NULL)
	{
		switch(Set)
		{
			case RESISTANCE_VALUE_PULS:
				if(ResistanceValue > 0x01)
				{
					Motor_Reverse();
					Delay_ms(ResistanceValue * INTERVAL2_23);
					Motor_Stop();
				}
				else
				{
					Motor_Reverse();         //单次加
					Delay_ms(INTERVAL1_B_P);
					//Motor_Forward();
					//Delay_ms(INTERVAL1_A);
					Motor_Stop();
				}
			break;
			case RESISTANCE_VALUE_MINUS:
				if(ResistanceValue > 0x01)
				{
					Motor_Forward();
					Delay_ms(ResistanceValue * INTERVAL2_23);
					Motor_Stop();
				}
				else
				{
					Motor_Forward();         //单次减
					Delay_ms(INTERVAL1_A);
					//Motor_Reverse();
					//Delay_ms(INTERVAL1_B_S);
					Motor_Stop();
				}	
			break;
			default :
			break;
		}
	}
}


