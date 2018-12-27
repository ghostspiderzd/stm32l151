#ifndef __MOTOR_DRIVER_H
#define __MOTOR_DRIVER_H

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define MOTOR_GPIO_RCC RCC_AHBPeriph_GPIOA
#define MOTOR_GPIO_INPUT GPIOA 
#define MOTOR_PIN_INPUTA GPIO_Pin_9
#define MOTOR_PIN_INPUTB GPIO_Pin_10

#define INTERVAL2_23 		500
#define INTERVAL2_1_B 		200
#define INTERVAL23_24_B 	450
#define INTERVAL1_B_P	 	1750
#define INTERVAL1_B_S		1500
#define INTERVAL1_A	 		1650

#define DEFAULT_RESISTANCE_VALUE		9


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


void Motor_GPIO_Init(void);
void Motor_Stop(void);
void Motor_Forward(void);
void Motor_Reverse(void);
void Motor_Brake(void);

void Motor_ResistanceAdjustment(unsigned char Set,unsigned char ResistanceValue);



#endif 

