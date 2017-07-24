#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "lcd.h"
#include "display.h"
#include "adc.h"
#include "dma.h"
#include "Key.h"
#include "timer.h"
#include "control.h"
#include "dac.h"
u16 buffer[4096]; //缓存区
u8 pause = 0;
extern uint32_t	TIM5CH1_CAPTURE_VAL;	//输入捕获值  
extern u8 count_Update;
extern u16 peakValue;
extern u16 valleyValue;
extern u16 points[250];
extern u8 graphIndex;
IsSuitable_Type isSuit;

int main(void)
 { 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168); 
	uart_init(9600);
	display_Init();
	DMA_ADCToMemory_Init((u32)buffer,4096);
	Adc_Init();
	Key_Init();
	Control_Init();

	TIM5_CH1_Cap_Init(0XFFFFFFFF,84-1); //以1Mhz的频率计数
	
	
	
  while(1) 
	{
		ADC_DMACmd(ADC1,DISABLE);
		DMA_Cmd(DMA2_Stream0, DISABLE);
		if(count_Update)        //成功捕获到了一次高电平
		{
			float temp = 80000 / (float)TIM5CH1_CAPTURE_VAL;
			display_Frequence(temp);
			count_Update = 0;		     //开启下一次捕获
		}
		if(!pause)
		{	
			while(!DMA_GetCurrDataCounter(DMA2_Stream0));
			display_DrawWave(buffer,4096);
			if(graphIndex == 250)
			{
				display_DrawWavePoint();
				graphIndex = 0;
			}
			DMA_ClearFlag(DMA2_Stream0,DMA_FLAG_TEIF0);
			DMA_ClearFlag(DMA2_Stream0,DMA_FLAG_TCIF0);
			DMA_Cmd(DMA2_Stream0,ENABLE);
			ADC_ClearFlag(ADC1,ADC_FLAG_OVR);
			ADC_DMACmd(ADC1,ENABLE);
			ADC_SoftwareStartConv(ADC1);			
			delay_ms(100);
		}
		IsSuitable_Type isSuit = Control_NeedToAdjust(peakValue,valleyValue);
		if(isSuit!= OK)//
		{
			if(isSuit == Large)
				Control_DecInput();
			else if(isSuit == Small)
				Control_IncInput();
		}
	}
}
