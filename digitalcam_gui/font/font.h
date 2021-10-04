/*
 * font.h
 *
 *  Created on: 13-Sep-2021
 *      Author: rajssss
 */

#ifndef LV_DIGITALCAM_GUI_FONT_FONT_H_
#define LV_DIGITALCAM_GUI_FONT_FONT_H_

#ifdef ESP_IDF_VERSION
	#include "../../lvgl/lvgl.h"
#else
	#include "lvgl/lvgl.h"
#endif


/*
 * Font Declarations
 *
 * */
LV_FONT_DECLARE(viewfinder_icons_20)


/*
 * Symbol defines
 *
 * */
#define VIEWFINDER_ICON_STILL_CAM	"\uf030"
#define VIEWFINDER_ICON_VIDEO_CAM	"\uf03d"
#define VIEWFINDER_ICON_GALLERY		"\uf87c"
#define VIEWFINDER_ICON_SETTINGS	"\uf013"



#endif /* LV_DIGITALCAM_GUI_FONT_FONT_H_ */
