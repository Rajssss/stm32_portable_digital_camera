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
#include "multi_heap.h"
#include "lv_conf.h"

#if LV_COLOR_DEPTH == 16
typedef uint16_t uintpixel_t;
#elif LV_COLOR_DEPTH == 24 || LV_COLOR_DEPTH == 32
typedef uint32_t uintpixel_t;
#endif

static void LCD_LL_ConvertLineToARGB8888(void *pSrc, void *pDst);


extern DCMI_HandleTypeDef  hDcmiHandler;
extern DMA2D_HandleTypeDef Dma2dHandle;
extern uintpixel_t * lcd_fb;

uint8_t cam_init(void)
{
	BSP_CAMERA_Init(CAMERA_R320x240);
	ov9655_MirrorFlipConfig(CAMERA_I2C_ADDRESS, CAMERA_FLIP);

	return 0;
}


uint8_t cam_live_feed(void)
{
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

//	digitalcam_cam_update_frame(cam_fb);

}


void BSP_CAMERA_IRQHandler(void)
{
//  HAL_DCMI_IRQHandler(&hDcmiHandler);
}
