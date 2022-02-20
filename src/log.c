/*
 * retarget_stdio.c
 *
 *  Created on: 20-Feb-2022
 *      Author: rajssss
 */
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include "inc/log.h"
#include "stm32746g_discovery.h"


UART_HandleTypeDef uart_printf_log;


void RetargetInit(void)
{
	uart_printf_log.Init.BaudRate = 115200;
	uart_printf_log.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart_printf_log.Init.Mode = UART_MODE_TX_RX;
	uart_printf_log.Init.Parity = UART_PARITY_NONE;
	uart_printf_log.Init.StopBits = UART_STOPBITS_1;
	uart_printf_log.Init.WordLength = UART_WORDLENGTH_8B;

    BSP_COM_Init(COM1, &uart_printf_log);

	/* Disable I/O buffering for STDOUT stream, so that
	 * chars are sent out as soon as they are printed. */
	setvbuf(stdout, NULL, _IONBF, 0);
}
