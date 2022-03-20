/*
 * gui.h
 *
 *  Created on: 20-Feb-2022
 *      Author: rajssss
 */

#ifndef GUI_H_
#define GUI_H_
#include "FreeRTOS.h"
#include "task.h"

extern TaskHandle_t cam_frame_update_task_handle;

void gui_init(void);

#endif /* GUI_H_ */
