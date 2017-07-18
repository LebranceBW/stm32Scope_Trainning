#include "Key.h"
#include "display.h"
#include "delay.h"
void Key_GPIOF_Init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct = 
	{
			.GPIO_Mode = GPIO_Mode_IN,
			.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5,
			.GPIO_PuPd = GPIO_PuPd_UP,
			.GPIO_Speed = GPIO_Speed_2MHz 
	};
	GPIO_Init(GPIOF,&GPIO_InitStruct);
}

void Key_EXTI_Init()
{
	EXTI_InitTypeDef EXTI_InitStruct = 
	{
		.EXTI_Line = EXTI_Line0|EXTI_Line1|EXTI_Line2|EXTI_Line3|EXTI_Line4|EXTI_Line5,
		.EXTI_LineCmd = ENABLE,
		.EXTI_Mode = EXTI_Mode_Interrupt,
		.EXTI_Trigger = EXTI_Trigger_Falling
	};
	EXTI_Init(&EXTI_InitStruct);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF,GPIO_PinSource0); 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF,GPIO_PinSource1); 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF,GPIO_PinSource2); 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF,GPIO_PinSource3); 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF,GPIO_PinSource4); 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF,GPIO_PinSource5); 
	
}

void Key_NVIC_Init()
{
	NVIC_InitTypeDef	NVIC_Struct =
	{
			.NVIC_IRQChannel = EXTI1_IRQn,
			.NVIC_IRQChannelCmd = ENABLE,
			.NVIC_IRQChannelPreemptionPriority = 1,
			.NVIC_IRQChannelSubPriority = 0
	};
	NVIC_Init(&NVIC_Struct);
	NVIC_Struct.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_Init(&NVIC_Struct);
}
void Key_Init()
{
	Key_GPIOF_Init();
	Key_EXTI_Init();
	Key_NVIC_Init();
}
void EXTI0_IRQHandler(void) //上键
{}
void EXTI1_IRQHandler(void) // 左键
{
	delay_ms(20);
	if(!GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_1))
	{
		display_XScale_Cmd(Falling);
		while(!GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_1));
	}
	EXTI_ClearITPendingBit(EXTI_Line1);
}
void EXTI2_IRQHandler(void) //右键
{
	delay_ms(20);
	if(!GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_2))
	{
		display_XScale_Cmd(Raising);
		while(!GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_2));
	}
	EXTI_ClearITPendingBit(EXTI_Line2);
}
void EXTI3_IRQHandler(void) //下键
{}
void EXTI4_IRQHandler(void) //复位
{}
void EXTI9_5IRQHandler(void) //确认
{}

	