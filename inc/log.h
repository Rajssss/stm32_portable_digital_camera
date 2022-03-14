/*
 * retarget_stdio.h
 *
 *  Created on: 20-Feb-2022
 *      Author: rajssss
 */

#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>
#include "stm32f7xx_hal.h"

#define sys_log(fmt, ...) printf("%s: %s: " fmt"\n\r", __FILE__, __FUNCTION__, ##__VA_ARGS__)

void RetargetInit(void);

#endif /* LOG_H_ */
