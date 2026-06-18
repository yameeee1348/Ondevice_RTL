#include "xparameters.h"
#include "xintc.h"
#include "xil_exception.h"
#include "xil_printf.h"
#include "ap_main.h"
#include "../driver/FND/FND.h"
#include "../driver/Button/Button.h"
#include "../common/common.h"
#include "../HAL/TMR/TMR.h"
#include "../driver/LED/LED.h"
#include "../driver/SW/sw.h"
#include "I2C/I2C.h"


hSw_t hSw0;



void ap_init() {
    I2C_Init();
    SW_Init(&hSw0, 0x44A40000);

    xil_printf("I2C Master FND Control System Ready\r\n");
}

void ap_execute() {
    	uint32_t val;
    uint8_t sw_value = 0;
    uint8_t slave_addr_w = 0xA0;
    uint8_t slave_addr_r = 0xA1;  // Read
      uint8_t readback = 0;
    while(1) {

        val = Xil_In32(0x44A40000 + 0x04) & 0xFF;
        xil_printf("SW: 0x%02X\r\n", val);
        if (SW_GetState(&hSw0, &sw_value) == SW_CHANGED) {
                    xil_printf("[I2C] SW: 0x%02X\r\n", sw_value);

                    // Write
                    I2C_Start();
                    I2C_WriteByte(slave_addr_w);
                    I2C_WriteByte(sw_value);
                    I2C_Stop();

                    delay_ms(10);

                    // Read back - Slave가 받은 값 확인
                    I2C_Start();
                    I2C_WriteByte(slave_addr_r);
                    readback = I2C_ReadByte(1);
                    I2C_Stop();

                    xil_printf("[I2C] Readback: 0x%02X\r\n", readback);
                }
            }
        }

//        if (SW_GetState(&hSw0, &sw_value) == SW_CHANGED) {
//
//            xil_printf("\r\n[EVENT] SW Changed: 0x%02X\r\n", sw_value);
//
//
//            xil_printf("[I2C] Sending Data to FND Slave...\r\n");
//
//            I2C_Start();
//            I2C_WriteByte(slave_addr);
//            I2C_WriteByte(sw_value);
//            I2C_Stop();
//
//    }
//            xil_printf("[I2C] Write Finished. FND should update to 0x%02X\r\n", sw_value);
//        delay_ms(200);
//}
//}
//void ap_execute() {
//    while(1) {
//
//        }
//    }
//}
