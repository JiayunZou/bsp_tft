#include "stm32f10x.h"                  // Device header
#include "BSP_LED.H"
#include "Delay.h"
#include "torch.h"
#include "bsp_ntimer.h"
#include "oled.h"
#include "FFTADC.h"
#include "SPIOled.h"
#include "AD9833.h"		// AD9833 definitions.
#include "Encoder.h"
#include "Menu.h"


//void Game(void){
//	
//	
//}


int main(void){
	
	OLED_SPI_Init();
	Encoder_Init();
	AD9833_Init();
	LED_Init();
	Advance_TIM_Init();
	OLED_Init();
	Torch_GPIO_Init();
	LED1_Off();
	MenuS1();
	while(1){
		
	}
}


