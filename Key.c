#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Key(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef KEY;
	KEY.GPIO_Mode = GPIO_Mode_IPD;
	KEY.GPIO_Pin = GPIO_Pin_8;
	KEY.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&KEY);
	
	GPIO_InitTypeDef LED;
	LED.GPIO_Mode = GPIO_Mode_Out_PP;
	LED.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4;
	LED.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&LED);
	
	int count=1;
	
	while(1)
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==1)
		{
			Delay_ms(10);
			if(count==1)
			{
			GPIO_SetBits(GPIOA,GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4);
			count=2;
			}
			else
			{
				GPIO_ResetBits(GPIOA,GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4);
				count=1;
			}
		}
	}
}

