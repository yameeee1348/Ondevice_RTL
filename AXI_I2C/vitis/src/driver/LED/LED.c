/*
 * LED.c
 *
 *  Created on: 2026. 4. 30.
 *      Author: kccistc
 */

#include "LED.h"
#include "../../common/common.h"


hLed_t hLed;

void LED_Init()
{
	GPIO_SetMode(GPIOC, GPIO_PIN_0, OUTPUT);
	GPIO_SetMode(GPIOC, GPIO_PIN_1, OUTPUT);
	GPIO_SetMode(GPIOC, GPIO_PIN_2, OUTPUT);
	GPIO_SetMode(GPIOC, GPIO_PIN_3, OUTPUT);
	GPIO_SetMode(GPIOC, GPIO_PIN_4, OUTPUT);
	GPIO_SetMode(GPIOC, GPIO_PIN_5, OUTPUT);
	GPIO_SetMode(GPIOC, GPIO_PIN_6, OUTPUT);
	GPIO_SetMode(GPIOC, GPIO_PIN_7, OUTPUT);

	 hLed.pattern = 0x01;
	 hLed.mode    = UP_CNT_MODE;

	 GPIO_WritePort(GPIOC, (1 << 4) | hLed.pattern);

}

void LED_Execute()
{
    switch (hLed.mode) {
        case UP_CNT_MODE:
            LED_UpCntMode();
            break;
        case WATCH_MODE:
            LED_WatchMode();
            break;
        default:LED_UpCntMode();
            break;
    }
}

void LED_SetMode(LedMode_t mode)
{
    hLed.mode = mode;
}

void LED_UpCntMode()
{
    static uint32_t lastTick = 0;
    uint8_t status_led = (1 << 4);
    if (millis() - lastTick >= 1000) {   // 1sec
            lastTick = millis();             // 여기도 millis()로 수정
            hLed.pattern = ((hLed.pattern << 1) | (hLed.pattern >> 3)) & 0x0F;
        }

        GPIO_WritePort(GPIOC, status_led | hLed.pattern);
    }

void LED_WatchMode() {
    static uint32_t lastTick = 0;
    uint8_t status_led = (1 << 5);
    if (millis() - lastTick >= 500) {    // 0.5sec
            lastTick = millis();             // 여기도 millis()로 수정
            hLed.pattern = ((hLed.pattern >> 1) | (hLed.pattern << 3)) & 0x0F;
        }

        GPIO_WritePort(GPIOC, status_led | hLed.pattern);
    }
