#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "lcd.h"
#include "display.h"
#include "adc.h"
#include "dma.h"
#include "Key.h"
u16 buffer[2048]; //缓存区
u8 pause = 0;

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168); 
	uart_init(9600);
	display_Init();
	DMA_ADCToMemory_Init((u32)buffer,2048);
	Adc_Init();
	Key_Init();
	display_XScale();
	display_YScale();
  while(1) 
	{
		if(!pause)
		{
			ADC_DMACmd(ADC1,DISABLE);
			DMA_Cmd(DMA2_Stream0, DISABLE);
			
			display_DrawWave(buffer,2048);

			
			
			DMA_ClearFlag(DMA2_Stream0,DMA_FLAG_TEIF0);
			DMA_ClearFlag(DMA2_Stream0,DMA_FLAG_TCIF0);
			DMA_Cmd(DMA2_Stream0,ENABLE);
			ADC_ClearFlag(ADC1,ADC_FLAG_OVR);
			ADC_DMACmd(ADC1,ENABLE);
			ADC_SoftwareStartConv(ADC1);
			
			
			delay_ms(10);
		}
	}
}
