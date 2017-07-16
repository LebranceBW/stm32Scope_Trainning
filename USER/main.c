#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "lcd.h"
#include "display.h"
#include "adc.h"
#include "dma.h"

u16 buffer[1024]; //缓存区
int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168); 
	uart_init(9600);
	display_Init();
	DMA_ADCToMemory_Init((u32)buffer,1024);
	Adc_Init();
  while(1) 
	{
		display_DrawWave(buffer,1024);
		delay_ms(10);
	}
}
