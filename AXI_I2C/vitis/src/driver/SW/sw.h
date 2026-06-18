#ifndef SRC_DRIVER_SW_SW_H_
#define SRC_DRIVER_SW_SW_H_

#include <stdint.h>
#include "xil_io.h"
#include "xparameters.h"


typedef enum {
    SW_NO_CHANGE = 0,
    SW_CHANGED
} sw_act_t;


typedef struct {
    uint32_t baseAddr;
    uint8_t  prevState;
} hSw_t;

void SW_Init(hSw_t *hsw, uint32_t baseAddr);
sw_act_t SW_GetState(hSw_t *hsw, uint8_t *currentVal);

#endif
