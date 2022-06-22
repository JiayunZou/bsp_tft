#include "bsp_led.h"

void LED_Init(void){
	RCC_APB2PeriphClockCmd(LED1_RCC|LED2_RCC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = LED1_Pin | LED2_Pin;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	
	GPIO_Init(LED1_PORT,&GPIO_InitStruct);
	GPIO_Init(LED2_PORT,&GPIO_InitStruct);
}
void LED1_On(void){
	GPIO_ResetBits(LED1_PORT,LED1_Pin);
}
void LED2_On(void){
	GPIO_ResetBits(LED2_PORT,LED2_Pin);
}
void LED1_Off(void){
	GPIO_SetBits(LED1_PORT,LED1_Pin);
}
void LED2_Off(void){
	GPIO_SetBits(LED2_PORT,LED2_Pin);
}










