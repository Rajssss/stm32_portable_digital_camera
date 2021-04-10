#include "sccb.h"



// Use for STM32F746IGT , HCLK = 200MHz
void delay_6us(void)
{
        uint16_t  i;
        
        for(i=0;i < 250;i++);
}


void SCCB_Delay(void)
{
	delay_6us();
}

void SCCB_Start(void)
{
    OV5640_SIOD_H();    
    OV5640_SIOC_H();	  
    SCCB_Delay();  
    OV5640_SIOD_L();
    SCCB_Delay();	 
    OV5640_SIOC_L();	  
}

void SCCB_Stop(void)
{
    OV5640_SIOD_L();
    SCCB_Delay();	 
    OV5640_SIOC_H();	
    SCCB_Delay(); 
    OV5640_SIOD_H();	
    SCCB_Delay();
}  

void SCCB_No_Ack(void)
{
	SCCB_Delay();
	OV5640_SIOD_H();	
	OV5640_SIOC_H();	
	SCCB_Delay();
	OV5640_SIOC_L();	
	SCCB_Delay();
	OV5640_SIOD_L();	
	SCCB_Delay();
}

uint8_t SCCB_WR_Byte(uint8_t dat)
{
	uint8_t j,res;	 
	for(j=0;j<8;j++) 
	{
		if(dat&0x80)OV5640_SIOD_H();	
		else OV5640_SIOD_L();
		dat<<=1;
		SCCB_Delay();
		OV5640_SIOC_H();	
		SCCB_Delay();
		OV5640_SIOC_L();		   
	}			 
	SCCB_Delay();
	OV5640_SIOC_H();		
	SCCB_Delay();
	if(OV5640_SIOD_READ())res=1;  
	else res=0;       
	OV5640_SIOC_L();		  
	return res;  
}	 

uint8_t SCCB_RD_Byte(void)
{
	uint8_t temp=0,j;    
	for(j=8;j>0;j--) 
	{		     	  
		SCCB_Delay();
		OV5640_SIOC_H();
		temp=temp<<1;
		if(OV5640_SIOD_READ())temp++;   
		SCCB_Delay();
		OV5640_SIOC_L();
	}	 
	return temp;
} 							    
