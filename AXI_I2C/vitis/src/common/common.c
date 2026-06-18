/*
 * common.c
 *
 *  Created on: 2026. 4. 28.
 *      Author: kccistc
 */
#include "common.h"

void delay_ms(uint32_t msec) {
    usleep(msec * 1000);
}

void delay_us(uint32_t usec) {
    usleep(usec);
}
