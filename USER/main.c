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

//	u16 adcx;
  while(1) 
	{	
//	 	adcx=Get_Adc_Average(ADC_Channel_5,20);//获取通道5的转换值，20次取平均
//		float temp=(float)adcx*(3.3/4096);
//		measureDisplay(temp);
//		delay_ms(250);
	}
}
