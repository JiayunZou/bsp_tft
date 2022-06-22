#ifndef __BSP_LED_H_
#define __BSP_LED_H_

#include "stm32f10x.h"                  // Device header

#define	LED1_Pin		GPIO_Pin_10
#define	LED2_Pin		GPIO_Pin_5
#define	LED1_RCC		RCC_APB2Periph_GPIOA
#define LED2_RCC		RCC_APB2Periph_GPIOE
#define	LED1_PORT		GPIOA
#define LED2_PORT		GPIOE

void LED_Init(void);
void LED1_On(void);
void LED2_On(void);
void LED1_Off(void);
void LED2_Off(void);

#endif
