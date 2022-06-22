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



void MenuS1(void){
	int16_t state1=10;
	uint8_t K,Last_State=0,State=0;
	
	while(1)
	{
		K=Torch_State();
		if(Last_State !=State)
		{
				OLED_Clear();
				State = Last_State ;
		}

		switch(State)
		{
			case 0:
			{
					if(K)
					{
						Last_State=K;
					}
						OLED_ShowString(1,1,"1 Voice Power");
						OLED_ShowString(2,1,"2 Sin Appear");
						OLED_ShowString(3,1,"3 FFT");
			}break;
			case 3:
			{
				
				
				OLED_ShowString(1,1,"Voice Power");
				switch(K)
				{
					case 3:OLED_ShowNum(2,1,CD4051Control(1),1);break;
					case 2:OLED_ShowNum(2,1,CD4051Control(0),1);break;
					case 1:Last_State = 0;break;
				}
			}	break;
			case 1: 
				while(1){
					OLED_ShowString(1,1,"Music!!!");
					FFT();
					if(Torch_State() == 1){
						OLED_SPI_Clear();
						break;
					}
					Last_State=0;
				}
				
			break;
			case 2:
			{
				OLED_ShowString(1,1,"Frequency Set");
				state1 += Encoder_Get();
				OLED_ShowNum(2,1,state1,4);
				AD9833_SetFrequencyQuick(state1*10,AD9833_OUT_SINUS);
				switch(K)
				{
					case 1:Last_State = 0;break;
				}
				
			}
	}
	}
}

