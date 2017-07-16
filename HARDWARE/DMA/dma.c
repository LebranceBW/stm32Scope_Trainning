#include "dma.h"

void DMA_ADCToMemory_Init(u32 memoryAddr,int length)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA2时钟使能 
	/*ADC1 隶属于DMA2 通道0 数据流0*/
	DMA_DeInit(DMA2_Stream0);
	DMA_Cmd(DMA2_Stream0, DISABLE);
	 DMA_InitTypeDef DMA_InitStruct = 
		{
			.DMA_BufferSize = length,//缓冲区250单位
			.DMA_Channel = DMA_Channel_0,
			.DMA_DIR = DMA_DIR_PeripheralToMemory,//DMA传输方向：外设到内存
			.DMA_Mode = DMA_Mode_Circular,//循环？
			.DMA_Priority = DMA_Priority_High,
			/*存储器设置*/
			.DMA_Memory0BaseAddr = memoryAddr,//首地址在buffer处
			.DMA_MemoryBurst = DMA_MemoryBurst_INC4,
			.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord,
			.DMA_MemoryInc = DMA_MemoryInc_Enable,
			
			/*外设设置*/
			.DMA_PeripheralBaseAddr = ADC1_DR_Address,//ADC1 的数据寄存器
			.DMA_PeripheralBurst = DMA_PeripheralBurst_INC4,
			.DMA_PeripheralInc = DMA_PeripheralInc_Disable,//外设非增量模式
			.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord,//外设数据长度:16位
			/*FIFO设置*/
			.DMA_FIFOMode = DMA_FIFOMode_Enable,
		  .DMA_FIFOThreshold = DMA_FIFOThreshold_Full		
		};
		
		DMA_Init(DMA2_Stream0, &DMA_InitStruct);//初始化DMA数据流
//		DMA_FlowControllerConfig(DMA2_Stream0,DMA_FlowCtrl_Peripheral);

		DMA_Cmd(DMA2_Stream0, ENABLE);
}
