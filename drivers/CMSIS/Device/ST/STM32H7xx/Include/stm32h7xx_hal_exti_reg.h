/**
  ******************************************************************************
  * @file    stm32h7xx_hal_exti_reg.h
  * @brief   Header file of EXTI HAL register module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7xx_HAL_EXTI_REG_H
#define STM32H7xx_HAL_EXTI_REG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal_def.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @defgroup EXTI_REG EXTI_REG
  * @brief EXTI Register module
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  EXTI Registers structure definition
  */
typedef struct
{
  __IO uint32_t IMR1;        /*!< EXTI Interrupt mask register 1,             Address offset: 0x00 */
  __IO uint32_t EMR1;        /*!< EXTI Event mask register 1,                 Address offset: 0x04 */
  __IO uint32_t RTSR1;       /*!< EXTI Rising trigger selection register 1,   Address offset: 0x08 */
  __IO uint32_t FTSR1;       /*!< EXTI Falling trigger selection register 1,  Address offset: 0x0C */
  __IO uint32_t SWIER1;      /*!< EXTI Software interrupt event register 1,   Address offset: 0x10 */
  __IO uint32_t PR1;         /*!< EXTI Pending register 1,                    Address offset: 0x14 */
  uint32_t      RESERVED1;   /*!< Reserved, 0x18                                                   */
  uint32_t      RESERVED2;   /*!< Reserved, 0x1C                                                   */
  __IO uint32_t IMR2;        /*!< EXTI Interrupt mask register 2,             Address offset: 0x20 */
  __IO uint32_t EMR2;        /*!< EXTI Event mask register 2,                 Address offset: 0x24 */
  __IO uint32_t RTSR2;       /*!< EXTI Rising trigger selection register 2,   Address offset: 0x28 */
  __IO uint32_t FTSR2;       /*!< EXTI Falling trigger selection register 2,  Address offset: 0x2C */
  __IO uint32_t SWIER2;      /*!< EXTI Software interrupt event register 2,   Address offset: 0x30 */
  __IO uint32_t PR2;         /*!< EXTI Pending register 2,                    Address offset: 0x34 */
  uint32_t      RESERVED3[2];/*!< Reserved, 0x38-0x3C                                              */
  __IO uint32_t IMR3;        /*!< EXTI Interrupt mask register 3,             Address offset: 0x40 */
  __IO uint32_t EMR3;        /*!< EXTI Event mask register 3,                 Address offset: 0x44 */
  __IO uint32_t RTSR3;       /*!< EXTI Rising trigger selection register 3,   Address offset: 0x48 */
  __IO uint32_t FTSR3;       /*!< EXTI Falling trigger selection register 3,  Address offset: 0x4C */
  __IO uint32_t SWIER3;      /*!< EXTI Software interrupt event register 3,   Address offset: 0x50 */
  __IO uint32_t PR3;         /*!< EXTI Pending register 3,                    Address offset: 0x54 */
  uint32_t      RESERVED4[2];/*!< Reserved, 0x58-0x5C                                              */
  __IO uint32_t D3PMR1;      /*!< EXTI D3 Pending mask register 1,            Address offset: 0x60 */
  __IO uint32_t D3PCR1L;     /*!< EXTI D3 Pending clear selection register 1 low, Address offset: 0x64 */
  __IO uint32_t D3PCR1H;     /*!< EXTI D3 Pending clear selection register 1 high, Address offset: 0x68 */
  uint32_t      RESERVED5;   /*!< Reserved, 0x6C                                                   */
  __IO uint32_t D3PMR2;      /*!< EXTI D3 Pending mask register 2,            Address offset: 0x70 */
  __IO uint32_t D3PCR2L;     /*!< EXTI D3 Pending clear selection register 2 low, Address offset: 0x74 */
  __IO uint32_t D3PCR2H;     /*!< EXTI D3 Pending clear selection register 2 high, Address offset: 0x78 */
} EXTI_TypeDef;

/* Exported constants --------------------------------------------------------*/
/** @defgroup EXTI_REG_Exported_Constants EXTI_REG Exported Constants
  * @{
  */

/** @defgroup EXTI_REG_Exported_Constants_Group1 EXTI register base address
  * @{
  */
#define EXTI_BASE              (0x58000000UL)
/** @defgroup EXTI_REG_Exported_Constants_Group2 EXTI register instance
  * @{
  */
#define EXTI                  ((EXTI_TypeDef *) EXTI_BASE)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7xx_HAL_EXTI_REG_H */
