/**
 * @file stm32h723xx.h
 * @brief STM32H723xx device header file placeholder for CI build
 */

#ifndef __STM32H723XX_H
#define __STM32H723XX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Include HAL definitions */
#include "stm32h7xx_hal.h"

/* Define GPIO ports for CI build */
extern GPIO_TypeDef* GPIOA;
extern GPIO_TypeDef* GPIOB;
extern GPIO_TypeDef* GPIOC;
extern GPIO_TypeDef* GPIOD;
extern GPIO_TypeDef* GPIOE;
extern GPIO_TypeDef* GPIOF;
extern GPIO_TypeDef* GPIOG;
extern GPIO_TypeDef* GPIOH;

#ifdef __cplusplus
}
#endif

#endif /* __STM32H723XX_H */
