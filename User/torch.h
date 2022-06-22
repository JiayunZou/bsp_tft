#ifndef __TORCH_H
#define __TORCH_H

#include "stm32f10x.h"
#include "bsp_ntimer.h"
#include "Delay.h"

#define	Torch1_Pin		GPIO_Pin_1
#define	Torch2_Pin		GPIO_Pin_7
#define	Torch3_Pin		GPIO_Pin_4

#define	Torch1_RCC		RCC_APB2Periph_GPIOA
#define Torch2_RCC		RCC_APB2Periph_GPIOB
#define Torch3_RCC		RCC_APB2Periph_GPIOB

#define	Torch1_PORT		GPIOA
#define Torch2_PORT		GPIOB
#define Torch3_PORT		GPIOB
#define MaxValue		50


void Torch_GPIO_Init(void);
void Torchx_GPIO_Out_PP(uint8_t Torchx);
void Torchx_GPIO_FLOAT_IN(uint8_t Torchx);
uint8_t Torch_State(void);

#endif
