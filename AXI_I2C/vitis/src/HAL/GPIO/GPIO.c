#include "GPIO.h"



void GPIO_SetMode(GPIO_Typedef_t * GPIOx, uint8_t pin, GPIO_Direction_t dir) {
   if (dir == OUTPUT) {
      GPIOx->CR |= pin;   // set 1
   } else {
      GPIOx->CR &= ~pin;   // set 0
   }
}

void GPIO_WritePin(GPIO_Typedef_t * GPIOx, uint8_t pin, GPIO_PinState_t state) {
   if (state == SET) {
      GPIOx->ODR |= pin;   // set 1
   } else {
      GPIOx->ODR &= ~pin;   // set 0
   }
}

uint8_t GPIO_ReadPin(GPIO_Typedef_t * GPIOx, uint8_t pin) {
   //return (GPIOx->IDR & pin);
  return (GPIOx->IDR & pin) ? 1 : 0;
   // only 0 -> false
}


void GPIO_WritePort(GPIO_Typedef_t * GPIOx, GPIO_PinState_t state)
{
   GPIOx -> ODR = state;
}

uint8_t GPIO_ReadPort(GPIO_Typedef_t * GPIOx)
{
   return GPIOx -> IDR;
}
