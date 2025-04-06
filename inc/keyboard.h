/**
 * @file keyboard.h
 * @brief Keyboard handling functionality
 */

#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Exported types ------------------------------------------------------------*/
typedef struct {
  uint8_t keycode;
  GPIO_TypeDef* port;
  uint16_t pin;
} Key_TypeDef;

/* Exported functions prototypes ---------------------------------------------*/
void Keyboard_Init(void);
void Keyboard_Process(void);
void Keyboard_SendReport(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#ifdef __cplusplus
}
#endif

#endif /* __KEYBOARD_H */
