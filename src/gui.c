/*
 * gui.c
 *
 *  Created on: 20-Feb-2022
 *      Author: rajssss
 */
#include <stdio.h>
#include "inc/gui.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "digitalcam_gui/inc/digitalcam_gui.h"
#include "cam/inc/cam.h"
#include "multi_heap.h"
#include "inc/log.h"
#include "lvgl/lvgl.h"
#include "hal_stm_lvgl/tft/tft.h"
#include "hal_stm_lvgl/touchpad/touchpad.h"


static void gui_task(void *args);
static void cam_frame_update_task(void *args);


TaskHandle_t cam_frame_update_task_handle;


//GUI Semaphore
SemaphoreHandle_t xGuiSemaphore;

void gui_init(void)
{
	xTaskCreate(gui_task, "gui_task", 1024*10, NULL, 4, NULL);
//    xTaskCreate(cam_frame_update_task, "cam_frame_update_task", 1024*2, NULL, 4, &cam_frame_update_task_handle);

}


static void gui_task(void *args)
{
	xGuiSemaphore = xSemaphoreCreateMutex();

    sys_log("Initializing LVGL\n");

    lv_init();

    tft_init();
    touchpad_init();

//    digitalcam_gui_init();

    cam_init();
//
    cam_live_feed();

    while(1)
    {
//		sys_log("gui_task: running");
        /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
        vTaskDelay(pdMS_TO_TICKS(10));

        /* Try to take the semaphore, call lvgl related function on success */
        if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY)) {
//            lv_task_handler();
            xSemaphoreGive(xGuiSemaphore);
       }
    }

}


static void cam_frame_update_task(void *args)
{
	vTaskDelay(pdMS_TO_TICKS(5*1000));

    cam_init();

    cam_live_feed();

	while(1)
	{
		if(xTaskNotifyWait(0, 0, NULL, portMAX_DELAY)== pdTRUE)
		{
			sys_log("cam_frame_update_task: running");

			if(xQueueSemaphoreTake(xGuiSemaphore, pdMS_TO_TICKS(100)))
			{
				sys_log("cam_frame_update_task: got mutex");

				digitalcam_cam_update_frame(&my_img_dsc);

				sys_log("cam_frame_update_task: wrote frame");

				xSemaphoreGive(xGuiSemaphore);
			}
		}
	}

/*	cam_live_feed();

	while(1)
	{
		vTaskDelay(pdMS_TO_TICKS(1000));
		sys_log("cam_frame_update_task: running");
	}*/
}
