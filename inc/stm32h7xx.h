#ifndef STM32H7XX_H
#define STM32H7XX_H

#define STM32H723xx

/* Include CMSIS headers */
#include "stm32h723xx.h"

/* Define USE_HAL_DRIVER to include HAL driver */
#define USE_HAL_DRIVER

#ifdef USE_HAL_DRIVER
  #include "stm32h7xx_hal.h"
#endif /* USE_HAL_DRIVER */

#endif /* STM32H7XX_H */
