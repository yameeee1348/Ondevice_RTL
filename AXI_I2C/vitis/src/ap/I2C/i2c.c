/*
 * i2c.c
 *
 *  Created on: 2026. 5. 2.
 *      Author: kccistc
 */

#include "I2C.h"
#include "xil_printf.h"



static void I2C_WaitDone() {
    uint32_t timeout = 100000;
    while((Xil_In32(I2C_STATUS_REG) & I2C_STATUS_DONE) == 0) {
        if(--timeout == 0) {
            xil_printf("[I2C] Timeout Error!\n");
            return;
        }
    }
}

void I2C_Init() {
    Xil_Out32(I2C_CMD_REG, 0x00);
}

void I2C_Start() {
    Xil_Out32(I2C_CMD_REG, I2C_CMD_START);
    I2C_WaitDone();
    Xil_Out32(I2C_CMD_REG, 0x00);
}

void I2C_Stop() {
    Xil_Out32(I2C_CMD_REG, I2C_CMD_STOP);
    I2C_WaitDone();
    Xil_Out32(I2C_CMD_REG, 0x00);
}

void I2C_WriteByte(uint8_t data) {
    Xil_Out32(I2C_TX_REG, data);
    Xil_Out32(I2C_CMD_REG, I2C_CMD_WRITE);
    I2C_WaitDone();
    Xil_Out32(I2C_CMD_REG, 0x00);
}

uint8_t I2C_ReadByte(uint8_t nack_en) {
    uint32_t cmd = I2C_CMD_READ;
    if (nack_en) cmd |= I2C_CMD_NACK;
    Xil_Out32(I2C_CMD_REG, cmd);
    Xil_Out32(I2C_CMD_REG, 0x00);
    I2C_WaitDone();
    return (uint8_t)(Xil_In32(I2C_STATUS_REG) & 0xFF);
}
