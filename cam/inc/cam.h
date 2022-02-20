/*
 * cam.h
 *
 *  Created on: 04-Oct-2021
 *      Author: rajssss
 */

#ifndef CAM_INC_CAM_H_
#define CAM_INC_CAM_H_

#include <stdint.h>

/*
#define CAM_FRAME_BUFFER			0x60200000
#define CAM_SECOND_FRAME_BUFFER		0x60400000
*/

#define CAM_FRAME_BUFFER			0x60000000
#define CAM_SECOND_FRAME_BUFFER		0x60200000

/*
#define FRAME_BUFFER			0xC0000000
#define SECOND_FRAME_BUFFER		0xC0200000
*/

uint8_t *cam_fb;
uint32_t cam_fb_size;

uint8_t cam_init(void);
uint8_t cam_live_feed(void);

#endif /* CAM_INC_CAM_H_ */
