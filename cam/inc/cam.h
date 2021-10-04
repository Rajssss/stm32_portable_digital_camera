/*
 * cam.h
 *
 *  Created on: 04-Oct-2021
 *      Author: rajssss
 */

#ifndef CAM_INC_CAM_H_
#define CAM_INC_CAM_H_

#include <stdint.h>

#define CAM_FRAME_BUFFER			0xC0000000
#define CAM_SECOND_FRAME_BUFFER		0xC0200000

uint8_t cam_init(void);
uint8_t cam_live_feed(void);

#endif /* CAM_INC_CAM_H_ */
