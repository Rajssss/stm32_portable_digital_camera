/*
 * cam.c
 *
 *  Created on: 04-Oct-2021
 *      Author: rajssss
 */

#include "inc/cam.h"
#include "Utilities/Components/Common/camera.h"
#include "Utilities/Components/ov9655/ov9655.h"
#include "stm32746g_discovery_camera.h"
#include "stm32f7xx_hal_dma2d.h"


uint8_t cam_init(void)
{
	BSP_CAMERA_Init(CAMERA_R480x272);

	return 0;
}


uint8_t cam_live_feed(void *cam_bf1, void *cam_bf2)
{
	BSP_CAMERA_ContinuousStart_DBM((uint8_t *)cam_bf1, (uint8_t *)cam_bf2);

	return 0;
}

