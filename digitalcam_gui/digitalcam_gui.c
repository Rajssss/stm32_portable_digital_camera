/*
 * digitalcam_gui.c
 *
 *  Created on: 11-Sep-2021
 *      Author: rajssss
 */
#include <stdio.h>
#include <stdint.h>
#include "inc/digitalcam_gui.h"
#ifdef ESP_IDF_VERSION
	#include "lvgl.h"
#else
	#include "lvgl/lvgl.h"
#endif
#include "font/font.h"


static void digicam_viewfinder_init(void);
static void digitalcam_cam_feed(void);



lv_obj_t *digitalcam_main_scr;
lv_obj_t *viewfinder_obj;
lv_obj_t *cam_feed;


void digitalcam_gui_init(void)
{
	digitalcam_main_scr = lv_obj_create(NULL, NULL);
	lv_obj_set_size(digitalcam_main_scr, 480, 272);
	lv_obj_set_style_local_border_width(digitalcam_main_scr, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_radius(digitalcam_main_scr, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
//	lv_obj_set_style_local_bg_opa(digitalcam_main_scr, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);
//	lv_disp_set_bg_opa(NULL, LV_OPA_TRANSP);
	lv_obj_set_style_local_bg_color(digitalcam_main_scr, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);

//	digitalcam_cam_feed();
	digicam_viewfinder_init();

	lv_scr_load_anim(digitalcam_main_scr, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, 0);

}


void digitalcam_cam_feed(void)
{
	cam_feed = lv_img_create(digitalcam_main_scr, NULL);

}


void digicam_viewfinder_init(void)
{
	viewfinder_obj = lv_obj_create(digitalcam_main_scr, NULL);
	lv_obj_set_size(viewfinder_obj, 320, 240);
	lv_obj_set_style_local_border_width(viewfinder_obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_radius(viewfinder_obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
//	lv_obj_set_style_local_bg_opa(viewfinder_obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);
	lv_obj_align(viewfinder_obj, digitalcam_main_scr, LV_ALIGN_CENTER, 0, 0);


	static lv_style_t btn_style;
	lv_style_init(&btn_style);
	lv_style_set_radius(&btn_style, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE);
	lv_style_set_bg_color(&btn_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_style_set_bg_color(&btn_style, LV_STATE_PRESSED, LV_COLOR_GRAY);
	lv_style_set_border_width(&btn_style, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_width(&btn_style, LV_STATE_DEFAULT, 0);

	lv_obj_t *action_btn = lv_btn_create(digitalcam_main_scr, NULL);
	lv_obj_add_style(action_btn, LV_BTN_PART_MAIN, &btn_style);
	lv_obj_set_size(action_btn, 55, 55);
	lv_obj_align(action_btn, digitalcam_main_scr, LV_ALIGN_IN_RIGHT_MID, -10, 0);

	lv_obj_t *action_icon = lv_label_create(action_btn, NULL);
	lv_obj_set_style_local_text_font(action_icon, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &viewfinder_icons_20);
	lv_obj_set_style_local_text_color(action_icon, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
	lv_label_set_text(action_icon, VIEWFINDER_ICON_STILL_CAM);
	lv_obj_align(action_icon, action_btn, LV_ALIGN_CENTER, 0, 0);


	lv_obj_t *switch_mode_btn = lv_obj_create(digitalcam_main_scr, action_btn);
	lv_obj_set_size(switch_mode_btn, 37, 37);
	lv_obj_set_style_local_bg_opa(switch_mode_btn, LV_BTN_PART_MAIN, LV_STATE_PRESSED, 50);
	lv_obj_set_style_local_bg_opa(switch_mode_btn, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 50);
	lv_obj_align(switch_mode_btn, digitalcam_main_scr, LV_ALIGN_IN_TOP_RIGHT, -10, 10);

	lv_obj_t *switch_mode_icon = lv_label_create(switch_mode_btn, action_icon);
	lv_label_set_text(switch_mode_icon, VIEWFINDER_ICON_VIDEO_CAM);
	lv_obj_align(switch_mode_icon, switch_mode_btn, LV_ALIGN_CENTER, 0, 0);


	lv_obj_t *gallery_btn = lv_obj_create(digitalcam_main_scr, switch_mode_btn);
	lv_obj_align(gallery_btn, digitalcam_main_scr, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -10);

	lv_obj_t *gallery_icon = lv_label_create(gallery_btn, switch_mode_icon);
	lv_label_set_text(gallery_icon, VIEWFINDER_ICON_GALLERY);
	lv_obj_align(gallery_icon, gallery_btn, LV_ALIGN_CENTER, 0, 0);


	lv_obj_t *setting_btn = lv_obj_create(digitalcam_main_scr, switch_mode_btn);
	lv_obj_set_style_local_bg_opa(setting_btn, LV_BTN_PART_MAIN, LV_STATE_PRESSED, 50);
	lv_obj_set_style_local_bg_opa(setting_btn, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 50);
	lv_obj_align(setting_btn, digitalcam_main_scr, LV_ALIGN_IN_TOP_LEFT, 10, 10);

	lv_obj_t *setting_icon = lv_label_create(setting_btn, gallery_icon);
	lv_label_set_text(setting_icon, VIEWFINDER_ICON_SETTINGS);
	lv_obj_align(setting_icon, setting_btn, LV_ALIGN_CENTER, 0, 0);

}
