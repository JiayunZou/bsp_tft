#ifndef __FFT_ADC_H
#define __FFT_ADC_H
#include "stm32f10x.h"

void  DMA1_Channel1_IRQHandler(void);
void Adc1_Init(void);
void FFT_Start(void);
void FFT(void);
unsigned char CD4051Control(unsigned char i);
//extern volatile uint16_t ADC1_ConvertedValue;			//ADC采样的数据

#endif
