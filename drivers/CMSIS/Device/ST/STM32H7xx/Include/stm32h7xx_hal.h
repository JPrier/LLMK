/**
 * @file stm32h7xx_hal.h
 * @brief STM32H7xx HAL header file
 */

#ifndef __STM32H7XX_HAL_H
#define __STM32H7XX_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CI_BUILD
/* CI build uses simplified HAL definitions */
#include "stm32h7xx_hal_ci.h"
#else
/* For local builds, include the actual STM32 HAL headers */
#include "stm32h7xx.h"
#endif /* CI_BUILD */

#ifdef __cplusplus
}
#endif

#endif /* __STM32H7XX_HAL_H */
