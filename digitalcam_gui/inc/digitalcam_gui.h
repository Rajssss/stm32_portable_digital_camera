/*
 * digitalcam_gui.h
 *
 *  Created on: 11-Sep-2021
 *      Author: rajssss
 */

#ifndef LV_DIGITALCAM_GUI_INC_DIGITALCAM_GUI_H_
#define LV_DIGITALCAM_GUI_INC_DIGITALCAM_GUI_H_

#include "lvgl/lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

lv_obj_t *digitalcam_main_scr;
lv_obj_t *viewfinder_obj;
lv_obj_t *cam_feed;

void digitalcam_gui_init(void);
void digitalcam_cam_update_frame(void *frame);


#ifdef __cplusplus
}
#endif

#endif /* LV_DIGITALCAM_GUI_INC_DIGITALCAM_GUI_H_ */
