#include "stm32f10x.h" // Device header
#include "Delay.h"

void CountSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef CountSensor;
	CountSensor.GPIO_Mode = GPIO_Mode_IPU;
	CountSensor.GPIO_Pin = GPIO_Pin_2;
	CountSensor.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&CountSensor);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2);
	
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line1;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
}

void EXTI1_IRQHandler(void)
{
	int count=0;
	if(EXTI_GetITStatus(EXTI_Line1)==SET)
	{
		while(count!=6)
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4);
			Delay_ms(150);
			GPIO_ResetBits(GPIOA,GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4);
			Delay_ms(150);
			count++;
		}
		count=0;
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}
