#include "torch.h"


 void LibDriveKeyInit(void)
 {
         GPIO_InitTypeDef  GPIO_InitStruct;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    
         GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);     
        GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;
         GPIO_InitStruct.GPIO_Pin     = GPIO_Pin_3 | GPIO_Pin_4;    
         GPIO_Init(GPIOB, &GPIO_InitStruct);
 }
void Torch_GPIO_Init(void){
	LibDriveKeyInit();
	RCC_APB2PeriphClockCmd(Torch1_RCC|Torch2_RCC|Torch3_RCC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = Torch1_Pin | Torch2_Pin|Torch3_Pin;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(Torch1_PORT,&GPIO_InitStruct);
	GPIO_Init(Torch2_PORT,&GPIO_InitStruct);
	GPIO_Init(Torch3_PORT,&GPIO_InitStruct);	
	GPIO_ResetBits(Torch1_PORT,Torch1_Pin);
	GPIO_ResetBits(Torch2_PORT,Torch2_Pin);
	GPIO_ResetBits(Torch3_PORT,Torch3_Pin);
	
}

void Torchx_GPIO_Out_PP(uint8_t Torchx){
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	if(Torchx == 1){
		GPIO_InitStruct.GPIO_Pin = Torch1_Pin;
		GPIO_Init(Torch1_PORT,&GPIO_InitStruct);
		GPIO_ResetBits(Torch1_PORT,Torch1_Pin);
	}else if(Torchx == 2){
		GPIO_InitStruct.GPIO_Pin = Torch2_Pin;
		GPIO_Init(Torch2_PORT,&GPIO_InitStruct);
		GPIO_ResetBits(Torch2_PORT,Torch2_Pin);
	}else if(Torchx == 3){
		GPIO_InitStruct.GPIO_Pin = Torch3_Pin;
		GPIO_Init(Torch3_PORT,&GPIO_InitStruct);
		GPIO_ResetBits(Torch3_PORT,Torch3_Pin);
	}
}
void Torchx_GPIO_FLOAT_IN(uint8_t Torchx){
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	if(Torchx == 1){
		GPIO_InitStruct.GPIO_Pin = Torch1_Pin;
		GPIO_Init(Torch1_PORT,&GPIO_InitStruct);
	}else if(Torchx == 2){
		GPIO_InitStruct.GPIO_Pin = Torch2_Pin;
		GPIO_Init(Torch2_PORT,&GPIO_InitStruct);
	}else if(Torchx == 3){
		GPIO_InitStruct.GPIO_Pin = Torch3_Pin;
		GPIO_Init(Torch3_PORT,&GPIO_InitStruct);
	}
}



uint8_t Torchx_Check(uint8_t Torchx){	
	if(Torchx == 1){
		Torchx_GPIO_Out_PP(1);
		Delay_ms(5);
		TIM2->CNT = 0;
		Torchx_GPIO_FLOAT_IN(1);
		while(GPIO_ReadInputDataBit(Torch1_PORT,Torch1_Pin) == 0);
		if(TIM2->CNT>=MaxValue){
			return 1;
		}else{
			return 0;
		}
		
	}else if(Torchx == 2){
		Torchx_GPIO_Out_PP(2);
		Delay_ms(5);
		TIM2->CNT = 0;
		Torchx_GPIO_FLOAT_IN(2);
		while(GPIO_ReadInputDataBit(Torch2_PORT,Torch2_Pin) == 0);
		if(TIM2->CNT>=MaxValue){
			return 2;
		}else{
			return 0;
		}
	}else if(Torchx == 3){
		Torchx_GPIO_Out_PP(3);
		Delay_ms(5);
		TIM2->CNT = 0;
		Torchx_GPIO_FLOAT_IN(3);
		while(GPIO_ReadInputDataBit(Torch3_PORT,Torch3_Pin) == 0);
		if(TIM2->CNT>=MaxValue){
			return 3;
		}else{
			return 0;
		}
	}
}
uint8_t Torch_State(void){
	if(Torchx_Check(1) == 1){
		while(Torchx_Check(1) == 1);
		return 1;
	}
	if(Torchx_Check(2) == 2){
		while(Torchx_Check(2) == 2);
		return 2;
	}
	if(Torchx_Check(3) == 3){
		while(Torchx_Check(3) == 3);
		return 3;
	}
}




