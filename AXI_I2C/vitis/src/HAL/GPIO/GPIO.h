/*
 * GPIO.h
 *
 *  Created on: 2026. 4. 28.
 *      Author: kccistc
 */

#ifndef SRC_HAL_GPIO_GPIO_H_
#define SRC_HAL_GPIO_GPIO_H_

#include <stdint.h>


typedef struct {
   uint32_t CR;
   uint32_t IDR;
   uint32_t ODR;
}GPIO_Typedef_t;

typedef enum {
    INPUT  = 0,
    OUTPUT = 1
} GPIO_Direction_t;

typedef enum {
    RESET = 0,
    SET   = 1
} GPIO_PinState_t;

void GPIO_SetMode(GPIO_Typedef_t * GPIOx, uint8_t pin, GPIO_Direction_t dir);
void GPIO_WritePin(GPIO_Typedef_t * GPIOx, uint8_t pin, GPIO_PinState_t state);
uint8_t GPIO_ReadPin(GPIO_Typedef_t * GPIOx, uint8_t pin);


#define GPIOA_BASE_ADDR 0x44A00000
#define GPIOB_BASE_ADDR 0x44A10000
#define GPIOC_BASE_ADDR 0x44A20000

#define GPIOA ((GPIO_Typedef_t *) (GPIOA_BASE_ADDR + 0x00))
#define GPIOB ((GPIO_Typedef_t *) (GPIOB_BASE_ADDR + 0x00))
#define GPIOC ((GPIO_Typedef_t *) (GPIOC_BASE_ADDR + 0x00))

//#define GPIO_PIN_0   (1 << 0)
//#define GPIO_PIN_1   (1 << 1)
//#define GPIO_PIN_2   (1 << 2)
//#define GPIO_PIN_3   (1 << 3)
//#define GPIO_PIN_4   (1 << 4)
//#define GPIO_PIN_5   (1 << 5)
//#define GPIO_PIN_6   (1 << 6)
//#define GPIO_PIN_7   (1 << 7)

#define GPIO_PIN_0   0x01 // 0b00000001
#define GPIO_PIN_1   0x02 // 0b00000010
#define GPIO_PIN_2   0x04 // 0b00000100
#define GPIO_PIN_3   0x08 // 0b00001000
#define GPIO_PIN_4   0x10 // 0b00010000
#define GPIO_PIN_5   0x20 // 0b00100000
#define GPIO_PIN_6   0x40 // 0b01000000
#define GPIO_PIN_7   0x80 // 0b10000000

#define INPUT 0x00
#define OUTPUT 0x01

#define RESET 0x00
#define SET 0x01





void GPIO_SetMode(GPIO_Typedef_t * GPIOx, uint8_t pin, GPIO_Direction_t dir);
void GPIO_WritePin(GPIO_Typedef_t * GPIOx, uint8_t pin, GPIO_PinState_t state);
uint8_t GPIO_ReadPin(GPIO_Typedef_t * GPIOx, uint8_t pin);
void GPIO_WritePort(GPIO_Typedef_t * GPIOx,  GPIO_PinState_t state);
uint8_t GPIO_ReadPort(GPIO_Typedef_t * GPIOx);

#endif /* SRC_HAL_GPIO_GPIO_H_ */
