/*
 * LED.h
 *
 *  Created on: 2026. 4. 30.
 *      Author: kccistc
 */

#ifndef SRC_DRIVER_LED_LED_H_
#define SRC_DRIVER_LED_LED_H_

#include <stdint.h>
#include "../../HAL/GPIO/GPIO.h"

typedef enum{
	UP_CNT_MODE,
	WATCH_MODE,
	HM_MODE,
	SMS_MODE,
	BLINK_MODE
}LedMode_t;

typedef struct {
    uint8_t pattern;
    LedMode_t mode;
} hLed_t;

void LED_Init();
void LED_Execute();
void LED_SetMode(LedMode_t mode);
void LED_UpCntMode();
void LED_WatchMode();


#endif /* SRC_DRIVER_LED_LED_H_ */
