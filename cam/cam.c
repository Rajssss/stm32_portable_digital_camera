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


static void MX_DMA2D_Init(void);


static DMA2D_HandleTypeDef hdma2d;


uint8_t cam_init(void)
{
	  BSP_CAMERA_Init(CAMERA_R480x272);


	  return 0;
}


uint8_t cam_live_feed(void)
{
	  BSP_CAMERA_ContinuousStart_DBM((uint8_t *)CAM_FRAME_BUFFER, (uint8_t *)CAM_SECOND_FRAME_BUFFER);

	  return 0;
}


static void MX_DMA2D_Init(void)
{

  hdma2d.Instance = DMA2D;
  hdma2d.Init.Mode = DMA2D_M2M;
  hdma2d.Init.ColorMode = DMA2D_OUTPUT_ARGB8888;
  hdma2d.Init.OutputOffset = 0;
  hdma2d.LayerCfg[1].InputOffset = 0;
  hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[1].InputAlpha = 0;
  if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
  {
//    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
  {
//    _Error_Handler(__FILE__, __LINE__);
  }

}
