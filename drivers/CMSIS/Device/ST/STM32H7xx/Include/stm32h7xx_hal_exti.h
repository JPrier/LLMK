/**
  ******************************************************************************
  * @file    stm32h7xx_hal_exti.h
  * @brief   Header file of EXTI HAL module.
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
#ifndef STM32H7xx_HAL_EXTI_H
#define STM32H7xx_HAL_EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal_def.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @defgroup EXTI EXTI
  * @brief EXTI HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup EXTI_Exported_Types EXTI Exported Types
  * @{
  */
typedef enum
{
  HAL_EXTI_COMMON_CB_ID          = 0x00U,
  HAL_EXTI_RISING_CB_ID          = 0x01U,
  HAL_EXTI_FALLING_CB_ID         = 0x02U,
} EXTI_CallbackIDTypeDef;

/**
  * @brief  EXTI Handle structure definition
  */
typedef struct
{
  uint32_t Line;                    /*!<  Exti line number */
  void (* RisingCallback)(void);    /*!<  Exti rising callback */
  void (* FallingCallback)(void);   /*!<  Exti falling callback */
} EXTI_HandleTypeDef;

/**
  * @brief  EXTI Configuration structure definition
  */
typedef struct
{
  uint32_t Line;      /*!< The Exti line to be configured. This parameter
                           can be a value of @ref EXTI_Line */
  uint32_t Mode;      /*!< The Exit Mode to be configured for a core.
                           This parameter can be a combination of @ref EXTI_Mode */
  uint32_t Trigger;   /*!< The Exti Trigger to be configured. This parameter
                           can be a value of @ref EXTI_Trigger */
  uint32_t GPIOSel;   /*!< The Exti GPIO multiplexer selection to be configured.
                           This parameter is only possible for line 0 to 15. It
                           can be a value of @ref EXTI_GPIOSel */
  uint32_t PendClearSource;  /*!< Specifies the clear source of pending register.
                                  This parameter can be a value of @ref EXTI_PendClear_Source */
} EXTI_ConfigTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup EXTI_Exported_Constants EXTI Exported Constants
  * @{
  */

/** @defgroup EXTI_Line  EXTI Line
  * @{
  */
#define EXTI_LINE_0                         (0x00000001U)  /*!< External interrupt line 0 */
#define EXTI_LINE_1                         (0x00000002U)  /*!< External interrupt line 1 */
#define EXTI_LINE_2                         (0x00000004U)  /*!< External interrupt line 2 */
#define EXTI_LINE_3                         (0x00000008U)  /*!< External interrupt line 3 */
#define EXTI_LINE_4                         (0x00000010U)  /*!< External interrupt line 4 */
#define EXTI_LINE_5                         (0x00000020U)  /*!< External interrupt line 5 */
#define EXTI_LINE_6                         (0x00000040U)  /*!< External interrupt line 6 */
#define EXTI_LINE_7                         (0x00000080U)  /*!< External interrupt line 7 */
#define EXTI_LINE_8                         (0x00000100U)  /*!< External interrupt line 8 */
#define EXTI_LINE_9                         (0x00000200U)  /*!< External interrupt line 9 */
#define EXTI_LINE_10                        (0x00000400U)  /*!< External interrupt line 10 */
#define EXTI_LINE_11                        (0x00000800U)  /*!< External interrupt line 11 */
#define EXTI_LINE_12                        (0x00001000U)  /*!< External interrupt line 12 */
#define EXTI_LINE_13                        (0x00002000U)  /*!< External interrupt line 13 */
#define EXTI_LINE_14                        (0x00004000U)  /*!< External interrupt line 14 */
#define EXTI_LINE_15                        (0x00008000U)  /*!< External interrupt line 15 */
#define EXTI_LINE_16                        (0x00010000U)  /*!< External interrupt line 16 */
#define EXTI_LINE_17                        (0x00020000U)  /*!< External interrupt line 17 */
#define EXTI_LINE_18                        (0x00040000U)  /*!< External interrupt line 18 */
#define EXTI_LINE_19                        (0x00080000U)  /*!< External interrupt line 19 */
#define EXTI_LINE_20                        (0x00100000U)  /*!< External interrupt line 20 */
#define EXTI_LINE_21                        (0x00200000U)  /*!< External interrupt line 21 */
#define EXTI_LINE_22                        (0x00400000U)  /*!< External interrupt line 22 */
#define EXTI_LINE_23                        (0x00800000U)  /*!< External interrupt line 23 */
#define EXTI_LINE_24                        (0x01000000U)  /*!< External interrupt line 24 */
#define EXTI_LINE_25                        (0x02000000U)  /*!< External interrupt line 25 */
#define EXTI_LINE_26                        (0x04000000U)  /*!< External interrupt line 26 */
#define EXTI_LINE_27                        (0x08000000U)  /*!< External interrupt line 27 */
#define EXTI_LINE_28                        (0x10000000U)  /*!< External interrupt line 28 */
#define EXTI_LINE_29                        (0x20000000U)  /*!< External interrupt line 29 */
#define EXTI_LINE_30                        (0x40000000U)  /*!< External interrupt line 30 */
#define EXTI_LINE_31                        (0x80000000U)  /*!< External interrupt line 31 */
#define EXTI_LINE_ALL                       (0xFFFFFFFFU)  /*!< All External interrupt lines */
/**
  * @}
  */

/** @defgroup EXTI_Mode  EXTI Mode
  * @{
  */
#define EXTI_MODE_NONE                      0x00000000U
#define EXTI_MODE_INTERRUPT                 0x00000001U
#define EXTI_MODE_EVENT                     0x00000002U
#define EXTI_MODE_D3_INTERRUPT              0x00000010U
#define EXTI_MODE_D3_EVENT                  0x00000020U
/**
  * @}
  */

/** @defgroup EXTI_Trigger  EXTI Trigger
  * @{
  */
#define EXTI_TRIGGER_NONE                   0x00000000U
#define EXTI_TRIGGER_RISING                 0x00000001U
#define EXTI_TRIGGER_FALLING                0x00000002U
#define EXTI_TRIGGER_RISING_FALLING         (EXTI_TRIGGER_RISING | EXTI_TRIGGER_FALLING)
/**
  * @}
  */

/** @defgroup EXTI_GPIOSel  EXTI GPIOSel
  * @brief
  * @{
  */
#define EXTI_GPIOA                          0x00000000U
#define EXTI_GPIOB                          0x00000001U
#define EXTI_GPIOC                          0x00000002U
#define EXTI_GPIOD                          0x00000003U
#define EXTI_GPIOE                          0x00000004U
#define EXTI_GPIOF                          0x00000005U
#define EXTI_GPIOG                          0x00000006U
#define EXTI_GPIOH                          0x00000007U
#define EXTI_GPIOI                          0x00000008U
#define EXTI_GPIOJ                          0x00000009U
#define EXTI_GPIOK                          0x0000000AU
/**
  * @}
  */

/** @defgroup EXTI_PendClear_Source  EXTI PendClear Source
  * @brief
  * @{
  */
#define EXTI_D1_PENDCLR_SRC_NONE            0x00000000U
#define EXTI_D1_PENDCLR_SRC_DMACH6          0x00000001U
#define EXTI_D1_PENDCLR_SRC_DMACH7          0x00000002U
#define EXTI_D1_PENDCLR_SRC_LPTIM4          0x00000004U
#define EXTI_D1_PENDCLR_SRC_LPTIM5          0x00000008U
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup EXTI_Exported_Macros EXTI Exported Macros
  * @{
  */

/**
  * @}
  */

/* Private constants --------------------------------------------------------*/
/** @defgroup EXTI_Private_Constants EXTI Private Constants
  * @{
  */
/**
  * @brief  EXTI Line property definition
  */
#define EXTI_PROPERTY_SHIFT                 24U
#define EXTI_DIRECT                         (0x01UL << EXTI_PROPERTY_SHIFT)
#define EXTI_CONFIG                         (0x02UL << EXTI_PROPERTY_SHIFT)
#define EXTI_GPIO                           ((0x04UL << EXTI_PROPERTY_SHIFT) | EXTI_CONFIG)
#define EXTI_RESERVED                       (0x08UL << EXTI_PROPERTY_SHIFT)
#define EXTI_PROPERTY_MASK                  (EXTI_DIRECT | EXTI_CONFIG | EXTI_GPIO)

/**
  * @brief  EXTI Register and bit usage
  */
#define EXTI_REG_SHIFT                      16U
#define EXTI_REG1                           (0x00UL << EXTI_REG_SHIFT)
#define EXTI_REG2                           (0x01UL << EXTI_REG_SHIFT)
#define EXTI_REG3                           (0x02UL << EXTI_REG_SHIFT)
#define EXTI_REG_MASK                       (EXTI_REG1 | EXTI_REG2 | EXTI_REG3)
#define EXTI_PIN_MASK                       0x0000001FU

/**
  * @brief  EXTI Mask for interrupt & event mode
  */
#define EXTI_MODE_MASK                      (EXTI_MODE_EVENT | EXTI_MODE_INTERRUPT | EXTI_MODE_D3_EVENT | EXTI_MODE_D3_INTERRUPT)

/**
  * @brief  EXTI Mask for trigger possibilities
  */
#define EXTI_TRIGGER_MASK                   (EXTI_TRIGGER_RISING | EXTI_TRIGGER_FALLING)

/**
  * @brief  EXTI Line number
  */
#define EXTI_LINE_NB                        72UL

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup EXTI_Private_Macros EXTI Private Macros
  * @{
  */
#define IS_EXTI_LINE(__LINE__)          ((((__LINE__) & ~EXTI_LINE_ALL) == 0x00U) && ((__LINE__) != 0x00U))
#define IS_EXTI_MODE(__MODE__)          (((__MODE__) & ~EXTI_MODE_MASK) == 0x00U)
#define IS_EXTI_TRIGGER(__TRIGGER__)    (((__TRIGGER__) & ~EXTI_TRIGGER_MASK) == 0x00U)
#define IS_EXTI_PENDING_EDGE(__EDGE__)  (((__EDGE__) == EXTI_TRIGGER_RISING) || \
                                         ((__EDGE__) == EXTI_TRIGGER_FALLING))
#define IS_EXTI_CONFIG_LINE(__LINE__)   (((__LINE__) & EXTI_CONFIG) != 0x00U)
#define IS_EXTI_GPIO_PORT(__PORT__)     (((__PORT__) == EXTI_GPIOA) || \
                                         ((__PORT__) == EXTI_GPIOB) || \
                                         ((__PORT__) == EXTI_GPIOC) || \
                                         ((__PORT__) == EXTI_GPIOD) || \
                                         ((__PORT__) == EXTI_GPIOE) || \
                                         ((__PORT__) == EXTI_GPIOF) || \
                                         ((__PORT__) == EXTI_GPIOG) || \
                                         ((__PORT__) == EXTI_GPIOH) || \
                                         ((__PORT__) == EXTI_GPIOI) || \
                                         ((__PORT__) == EXTI_GPIOJ) || \
                                         ((__PORT__) == EXTI_GPIOK))
#define IS_EXTI_GPIO_PIN(__PIN__)       ((__PIN__) < 16U)
#define IS_EXTI_D1_PENDCLR_SRC(__SRC__) (((__SRC__) == EXTI_D1_PENDCLR_SRC_NONE) || \
                                         ((__SRC__) == EXTI_D1_PENDCLR_SRC_DMACH6) || \
                                         ((__SRC__) == EXTI_D1_PENDCLR_SRC_DMACH7) || \
                                         ((__SRC__) == EXTI_D1_PENDCLR_SRC_LPTIM4) || \
                                         ((__SRC__) == EXTI_D1_PENDCLR_SRC_LPTIM5))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup EXTI_Exported_Functions EXTI Exported Functions
  * @brief    EXTI Exported Functions
  * @{
  */

/** @defgroup EXTI_Exported_Functions_Group1 Configuration functions
  * @brief    Configuration functions
  * @{
  */
/* Configuration functions ****************************************************/
HAL_StatusTypeDef HAL_EXTI_SetConfigLine(EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig);
HAL_StatusTypeDef HAL_EXTI_GetConfigLine(EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig);
HAL_StatusTypeDef HAL_EXTI_ClearConfigLine(EXTI_HandleTypeDef *hexti);
HAL_StatusTypeDef HAL_EXTI_RegisterCallback(EXTI_HandleTypeDef *hexti, EXTI_CallbackIDTypeDef CallbackID, void (*pPendingCbfn)(void));
HAL_StatusTypeDef HAL_EXTI_GetHandle(EXTI_HandleTypeDef *hexti, uint32_t ExtiLine);
/**
  * @}
  */

/** @defgroup EXTI_Exported_Functions_Group2 IO operation functions
  * @brief    IO operation functions
  * @{
  */
/* IO operation functions *****************************************************/
void              HAL_EXTI_IRQHandler(EXTI_HandleTypeDef *hexti);
uint32_t          HAL_EXTI_GetPending(EXTI_HandleTypeDef *hexti, uint32_t Edge);
void              HAL_EXTI_ClearPending(EXTI_HandleTypeDef *hexti, uint32_t Edge);
void              HAL_EXTI_GenerateSWI(EXTI_HandleTypeDef *hexti);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7xx_HAL_EXTI_H */
