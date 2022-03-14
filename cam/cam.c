/*
 * cam.c
 *
 *  Created on: 04-Oct-2021
 *      Author: rajssss
 */

#include <string.h>
#include "inc/cam.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "Utilities/Components/Common/camera.h"
#include "Utilities/Components/ov9655/ov9655.h"
#include "stm32746g_discovery_camera.h"
#include "stm32f7xx_hal_dma2d.h"
#include "multi_heap.h"
#include "lv_conf.h"
#include "digitalcam_gui/inc/digitalcam_gui.h"
#include "inc/gui.h"
#include "inc/log.h"


#if LV_COLOR_DEPTH == 16
typedef uint16_t uintpixel_t;
#elif LV_COLOR_DEPTH == 24 || LV_COLOR_DEPTH == 32
typedef uint32_t uintpixel_t;
#endif


extern DCMI_HandleTypeDef  hDcmiHandler;
extern DMA2D_HandleTypeDef Dma2dHandle;
extern uintpixel_t * lcd_fb;
extern SemaphoreHandle_t xGuiSemaphore;


uint8_t cam_init(void)
{
	BSP_CAMERA_Init(CAMERA_R320x240);
	ov9655_MirrorFlipConfig(CAMERA_I2C_ADDRESS, CAMERA_FLIP);

	return 0;
}


uint8_t cam_live_feed(void)
{
	my_img_dsc.header.always_zero = 0;
	my_img_dsc.header.w = 320;
	my_img_dsc.header.h = 240;
	my_img_dsc.data_size = 320*240*LV_COLOR_DEPTH/8;
	my_img_dsc.header.cf = LV_IMG_CF_TRUE_COLOR;

	cam_fb_size = 320*240*2;			// Resolution * color depth; RGB565=16bit=2byte

	cam_fb = (uint8_t *) malloc_ext(cam_fb_size);
	memset(cam_fb, 0, cam_fb_size);
//	cam_buff2 = (uint8_t *) malloc_ext(480*272*2);

	BSP_CAMERA_ContinuousStart((uint8_t *)cam_fb);
//	BSP_CAMERA_ContinuousStart_DBM((uint8_t *)cam_bf1, (uint8_t *)cam_bf2);

	return 0;
}


void BSP_CAMERA_FrameEventCallback(void)
{
	// Process cam data per Per Frame(X*Y)
/*    Dma2dHandle.Init.Mode         = DMA2D_M2M_PFC;
//    Dma2dHandle.Init.ColorMode    = DMA2D_OUTPUT_ARGB8888;
    Dma2dHandle.Init.ColorMode    = DMA2D_OUTPUT_RGB565;
    Dma2dHandle.Init.OutputOffset = 0x0;

    Dma2dHandle.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
    Dma2dHandle.LayerCfg[1].InputAlpha = 0xFF;
    Dma2dHandle.LayerCfg[1].InputColorMode = DMA2D_INPUT_RGB565;
    Dma2dHandle.LayerCfg[1].InputOffset = 0x0;

    Dma2dHandle.Instance  = DMA2D;

    if(HAL_DMA2D_Init(&Dma2dHandle) == HAL_OK)
    {
      if(HAL_DMA2D_ConfigLayer(&Dma2dHandle, 1) == HAL_OK)
      {
        if (HAL_DMA2D_Start(&Dma2dHandle, (uint32_t)cam_fb, (uint32_t)lcd_fb, 320, 240) == HAL_OK)
        {
          HAL_DMA2D_PollForTransfer(&Dma2dHandle, 10);
        }
      }
    }
    else
    {
      while(1);
    }*/

/*	sys_log("BSP_CAMERA_FrameEventCallback: Received");

	if(xQueueSemaphoreTake(xGuiSemaphore, pdMS_TO_TICKS(100)))
	{
		sys_log("BSP_CAMERA_FrameEventCallback: mutex lock");

		digitalcam_cam_update_frame(&my_img_dsc);

		xSemaphoreGive(xGuiSemaphore);
	}*/
	sys_log("BSP_CAMERA_FrameEventCallback: Received");

	xTaskNotifyFromISR(cam_frame_update_task_handle, 0, eNoAction, NULL);
//	digitalcam_cam_update_frame(cam_fb);

}

void BSP_CAMERA_LineEventCallback(void)
{
	sys_log("BSP_CAMERA_LineEventCallback: Received");
}


void BSP_CAMERA_IRQHandler(void)
{
  HAL_DCMI_IRQHandler(&hDcmiHandler);
}

void BSP_CAMERA_DMA_IRQHandler(void)
{
	HAL_DMA_IRQHandler(hDcmiHandler.DMA_Handle);
}
