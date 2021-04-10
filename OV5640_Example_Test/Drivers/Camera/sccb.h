#ifndef __SCCB_H
#define __SCCB_H

#include "stm32f7xx.h"
#include "main.h"




#define    OV5640_SIOC_H()       HAL_GPIO_WritePin(DCMI_SIOC_GPIO_Port, DCMI_SIOC_Pin, GPIO_PIN_SET)
#define    OV5640_SIOC_L()       HAL_GPIO_WritePin(DCMI_SIOC_GPIO_Port, DCMI_SIOC_Pin, GPIO_PIN_RESET)
#define    OV5640_SIOD_H()       HAL_GPIO_WritePin(DCMI_SIOD_GPIO_Port, DCMI_SIOD_Pin, GPIO_PIN_SET)
#define    OV5640_SIOD_L()       HAL_GPIO_WritePin(DCMI_SIOD_GPIO_Port, DCMI_SIOD_Pin, GPIO_PIN_RESET)

#define    OV5640_SIOD_READ()     HAL_GPIO_ReadPin(DCMI_SIOD_GPIO_Port, DCMI_SIOD_Pin)


void SCCB_Init(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void SCCB_No_Ack(void);
uint8_t SCCB_WR_Byte(uint8_t dat);
uint8_t SCCB_RD_Byte(void);
#endif

