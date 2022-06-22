#include "stm32f10x.h"
#include "SPI.h"
#include "Delay.h"
#include "stdio.h"
#include <stdarg.h>
#include "SPIOled.h"
#include "OLEDWord.h"
//sbit OLED_SPI_DC = P4^7;
//sbit OLED_SPI_CS = P1^1;
//sbit OLED_SPI_RES = P1^2;
#define OLED_SPI_DC_W(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_13, (BitAction)(x))
#define OLED_SPI_CS_W(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_14, (BitAction)(x))
#define OLED_SPI_RES_W(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_12, (BitAction)(x))
//0 为命令 1为数据




unsigned char OLED_SPI_GRAM[128][8];




void OLED_SPI_WriteByte(unsigned char Data,unsigned char Cmd)
{
	OLED_SPI_DC_W(Cmd);
	SPI_SendByte(Data);
	OLED_SPI_DC_W(1);
}
void OLED_SPI_WriteCMD(unsigned char CMD)
{
	OLED_SPI_WriteByte(CMD,0);
}
void OLED_SPI_WriteData(unsigned char Data)
{
	OLED_SPI_WriteByte(Data,1);
}

void OLED_SPI_Clear(void)
{
	unsigned char i,n;
	for(i = 0;i < 8;i++)
	{
		OLED_SPI_WriteCMD(0xb0+i);
		OLED_SPI_WriteCMD(0x02);
		OLED_SPI_WriteCMD(0x10);
		for(n=0;n<128;n++)
		OLED_SPI_WriteData(0);
	}
}
void OLED_SPI_SetClear(void)
{
	
}
//开启显示		
void OLED_SPI_Display_ON()
{
	OLED_SPI_WriteCMD(0x8D);
	OLED_SPI_WriteCMD(0x14);
	OLED_SPI_WriteCMD(0xAF);
}	
//关闭显示
void OLED_SPI_Display_OFF(void)
{
	OLED_SPI_WriteCMD(0x8D);
	OLED_SPI_WriteCMD(0x10);
	OLED_SPI_WriteCMD(0xAE);
}
//设置光标
void OLED_SPI_Set_Position(unsigned char x,unsigned char y)
{
	OLED_SPI_WriteCMD(0xb0+y);
	OLED_SPI_WriteCMD((((x+2)&0xf0)>>4)|0x10);
	OLED_SPI_WriteCMD((x+2)&0x0f);
}
//OLED 初始化
void OLED_SPI_Init(void)
{
	
	Spi_Init();
	OLED_SPI_CS_W(0);
	OLED_SPI_RES_W(1);
	Delay_ms(100);
	OLED_SPI_RES_W(0);
	Delay_ms(100);
	OLED_SPI_RES_W(1);
	
	OLED_SPI_WriteCMD(0xAE);
	OLED_SPI_WriteCMD(0x02);
	OLED_SPI_WriteCMD(0x10);
	OLED_SPI_WriteCMD(0x40);
	OLED_SPI_WriteCMD(0x81);
	OLED_SPI_WriteCMD(0xCF);
	OLED_SPI_WriteCMD(0xA1);
	OLED_SPI_WriteCMD(0xC8);
	OLED_SPI_WriteCMD(0xA6);
	OLED_SPI_WriteCMD(0xA8);
	OLED_SPI_WriteCMD(0x3F);
	OLED_SPI_WriteCMD(0xD3);
	OLED_SPI_WriteCMD(0x00);
	OLED_SPI_WriteCMD(0xD5);
	OLED_SPI_WriteCMD(0x80);
	OLED_SPI_WriteCMD(0xD9);
	OLED_SPI_WriteCMD(0xF1);
	OLED_SPI_WriteCMD(0xDA);
	OLED_SPI_WriteCMD(0x12);
	OLED_SPI_WriteCMD(0xDB);
	OLED_SPI_WriteCMD(0x40);
	OLED_SPI_WriteCMD(0x20);
	OLED_SPI_WriteCMD(0x02);
	OLED_SPI_WriteCMD(0x8D);
	OLED_SPI_WriteCMD(0x14);
	OLED_SPI_WriteCMD(0xA4);
	OLED_SPI_WriteCMD(0xA6);
	OLED_SPI_WriteCMD(0xAF);
	
	OLED_SPI_WriteCMD(0xAF);
	
	OLED_SPI_Clear();
	
	OLED_SPI_Set_Position(0,0);
}

void OLED_SPI_ShowChineseWord(unsigned char x,unsigned char y,unsigned char* Str,unsigned char Flag)
{
	unsigned char i = 0;
	unsigned int Index;
	for(Index = 0;Index < sizeof(Hzk)/35;Index ++)
	{
		if(Hzk[Index].Name[0] == Str[0]&&Hzk[Index].Name[1] == Str[1])
		{
			OLED_SPI_Set_Position(x,y);//设置OLED光标位置
			for(i= 0;i < 16;i ++)
			{
				if(Flag ==0) OLED_SPI_WriteData(Hzk[Index].Dat[i]);
				else OLED_SPI_WriteData(~Hzk[Index].Dat[i]);
			}
			OLED_SPI_Set_Position(x,y+1);
			for(i = 0;i< 16;i++)
			{
				if(Flag ==0) OLED_SPI_WriteData(Hzk[Index].Dat[i+16]);
				else OLED_SPI_WriteData(~Hzk[Index].Dat[i+16]);
			}
		}
	}
	
}

void OLED_SPI_ShowChar(unsigned char x,unsigned char y,unsigned char Chr,unsigned char Flag)
{
	unsigned char c = 0,i=0;
	c = Chr-' ';//得到偏移后的值
	if(x > 127){x = 0;y=y+2;}
	OLED_SPI_Set_Position(x,y);
	for(i = 0;i< 8;i++)
	{
		if(Flag ==0) OLED_SPI_WriteData(F8X16[c*16+i]);
		else OLED_SPI_WriteData(~F8X16[c*16+i]);
	}
	OLED_SPI_Set_Position(x,y+1);
	for(i = 0;i< 8;i++)
	{
		if(Flag ==0) OLED_SPI_WriteData(F8X16[c*16+i+8]);
		else OLED_SPI_WriteData(~F8X16[c*16+i+8]);
	}
}

void OLED_SPI_ShowText(unsigned char x,unsigned char y,unsigned char * Str,unsigned char Flag)
{
	unsigned char TempStr[3] = {'\0'};
	while(*Str !='\0')
	{
		if(*Str&0x80)
		{
			TempStr[0]= *Str++;
			TempStr[1]= *Str++;
			OLED_SPI_ShowChineseWord(x,y,TempStr,Flag);
			x+=16;
			if(*Str &0x80)
			{
				if(x >= 112){y++;y++;x=0;}
			}
			else
			{
				if(x>=120){y++;y++;x=0;}
			}
		}
		else
		{
			OLED_SPI_ShowChar(x,y,*Str++,Flag);
			x+=8;
			if(*Str&0x80)
			{
				if(x >= 112){y++;y++;x=0;}
			}
			else
			{
				if(x>=120){y++;y++;x=0;}
			}
		}
	}
}

void OLED_SPI_Refresh_Gram(void)
{
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_SPI_WriteCMD(0xb0+i);    //设置页地址（0~7）
		OLED_SPI_WriteCMD(0x00);      //设置显示位置—列低地址
		OLED_SPI_WriteCMD(0x10);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_SPI_WriteData(OLED_SPI_GRAM[n][i]); 
	}   
}

void OLED_SPI_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;//超出范围了.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_SPI_GRAM[x][pos]|=temp;
	else OLED_SPI_GRAM[x][pos]&=~temp;	    
}
//x1,y1,x2,y2 填充区域的对角坐标
//确保x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63	 	 
//dot:0,清空;1,填充	  
void OLED_SPI_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)  
{  
	u8 x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)OLED_SPI_DrawPoint(x,y,dot);
	}													    
//	OLED_SPI_Refresh_Gram();//更新显示
}
signed int OLED_SPI_Printf(unsigned char x,unsigned char y,const char *pFormat,...)
	
{
	char pStr[25] = {'\0'};
	va_list ap;
	signed int result;
	
	//Forward call tp vprintf
	va_start(ap,pFormat);
	result = vsprintf((char *)pStr,pFormat,ap);
	va_end(ap);
	
	OLED_SPI_ShowText(x,y,( unsigned char*)pStr,0);
	
	return result;
}
