/*
 * i2c.h
 *
 *  Created on: 2026. 5. 2.
 *      Author: kccistc
 */

#ifndef SRC_AP_I2C_I2C_H_
#define SRC_AP_I2C_I2C_H_

#include <stdint.h>
#include "xil_io.h"
#include "xparameters.h"

#define I2C_BASEADDR    XPAR_I2C_0_S00_AXI_BASEADDR

#define I2C_CMD_REG     (I2C_BASEADDR + 0x00)
#define I2C_TX_REG      (I2C_BASEADDR + 0x04)
#define I2C_STATUS_REG  (I2C_BASEADDR + 0x08)

#define I2C_CMD_START   0x01
#define I2C_CMD_WRITE   0x02
#define I2C_CMD_READ    0x04
#define I2C_CMD_STOP    0x08
#define I2C_CMD_NACK    0x10
#define I2C_STATUS_DONE 0x200


void I2C_Init();
void I2C_Start();
void I2C_Stop();
void I2C_WriteByte(uint8_t data);
uint8_t I2C_ReadByte(uint8_t nack_en);

#endif /* SRC_AP_I2C_I2C_H_ */
