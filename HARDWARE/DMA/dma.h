#ifndef DMA_H__
#define DMA_H__
#include "sys.h"

#define ADC1_DR_Address    (u32)&(ADC1->DR)

void DMA_ADCToMemory_Init(u32 memoryAddr,int length);

#endif
