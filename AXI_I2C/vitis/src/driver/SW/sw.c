#include "SW.h"
#include "../../common/common.h"

void SW_Init(hSw_t *hsw, uint32_t baseAddr) {
    hsw->baseAddr = baseAddr;
    // CR(+0x00)에 방향 설정 필요 시 여기서 설정
    hsw->prevState = (uint8_t)(Xil_In32(baseAddr + 0x04) & 0xFF);
}

sw_act_t SW_GetState(hSw_t *hsw, uint8_t *currentVal) {
    uint8_t curState = (uint8_t)(Xil_In32(hsw->baseAddr + 0x04) & 0xFF);
    if (curState != hsw->prevState) {
        delay_ms(20);
        curState = (uint8_t)(Xil_In32(hsw->baseAddr + 0x04) & 0xFF);
        if (curState != hsw->prevState) {
            *currentVal = curState;
            hsw->prevState = curState;
            return SW_CHANGED;
        }
    }
    return SW_NO_CHANGE;
}
