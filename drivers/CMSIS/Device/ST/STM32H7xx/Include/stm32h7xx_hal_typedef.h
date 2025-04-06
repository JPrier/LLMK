/**
  ******************************************************************************
  * @file    stm32h7xx_hal_typedef.h
  * @brief   HAL Type definitions for STM32H7xx series.
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
#ifndef STM32H7xx_HAL_TYPEDEF_H
#define STM32H7xx_HAL_TYPEDEF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* IO definitions */
#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions                 */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions                 */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */

/* Compiler specific definitions */
#if defined ( __CC_ARM )
  #define __weak                                   __attribute__((weak))
#elif defined ( __ICCARM__ )
  #define __weak                                   __weak
#elif defined ( __GNUC__ )
  #define __weak                                   __attribute__((weak))
#endif

/* NVIC PRIO bits definition */
#define __NVIC_PRIO_BITS          4U

/**
  * @brief  HAL Status structures definition
  */
typedef enum
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;

/**
  * @brief  HAL Lock structures definition
  */
typedef enum
{
  HAL_UNLOCKED = 0x00U,
  HAL_LOCKED   = 0x01U
} HAL_LockTypeDef;

/**
  * @brief  HAL Tick Frequency structures definition
  */
typedef enum
{
  HAL_TICK_FREQ_10HZ         = 100U,
  HAL_TICK_FREQ_100HZ        = 10U,
  HAL_TICK_FREQ_1KHZ         = 1U,
  HAL_TICK_FREQ_DEFAULT      = HAL_TICK_FREQ_1KHZ
} HAL_TickFreqTypeDef;

/* NVIC definitions */
#define NVIC_PRIORITYGROUP_0         0x00000007U /*!< 0 bits for pre-emption priority
                                                      4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         0x00000006U /*!< 1 bits for pre-emption priority
                                                      3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         0x00000005U /*!< 2 bits for pre-emption priority
                                                      2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         0x00000004U /*!< 3 bits for pre-emption priority
                                                      1 bits for subpriority */
#define NVIC_PRIORITYGROUP_4         0x00000003U /*!< 4 bits for pre-emption priority
                                                      0 bits for subpriority */

/* SysTick definitions */
#define SysTick_CTRL_COUNTFLAG_Pos         16U                                            /*!< SysTick CTRL: COUNTFLAG Position */
#define SysTick_CTRL_COUNTFLAG_Msk         (1UL << SysTick_CTRL_COUNTFLAG_Pos)            /*!< SysTick CTRL: COUNTFLAG Mask */
#define SysTick_CTRL_CLKSOURCE_Pos          2U                                            /*!< SysTick CTRL: CLKSOURCE Position */
#define SysTick_CTRL_CLKSOURCE_Msk         (1UL << SysTick_CTRL_CLKSOURCE_Pos)            /*!< SysTick CTRL: CLKSOURCE Mask */
#define SysTick_CTRL_TICKINT_Pos            1U                                            /*!< SysTick CTRL: TICKINT Position */
#define SysTick_CTRL_TICKINT_Msk           (1UL << SysTick_CTRL_TICKINT_Pos)              /*!< SysTick CTRL: TICKINT Mask */
#define SysTick_CTRL_ENABLE_Pos             0U                                            /*!< SysTick CTRL: ENABLE Position */
#define SysTick_CTRL_ENABLE_Msk            (1UL << SysTick_CTRL_ENABLE_Pos)               /*!< SysTick CTRL: ENABLE Mask */

/* Exported macro ------------------------------------------------------------*/
#define HAL_MAX_DELAY      0xFFFFFFFFU

#define HAL_IS_BIT_SET(REG, BIT)         (((REG) & (BIT)) == (BIT))
#define HAL_IS_BIT_CLR(REG, BIT)         (((REG) & (BIT)) == 0U)

#define __HAL_LINKDMA(__HANDLE__, __PPP_DMA_FIELD__, __DMA_HANDLE__)               \
                        do{                                                      \
                              (__HANDLE__)->__PPP_DMA_FIELD__ = &(__DMA_HANDLE__); \
                              (__DMA_HANDLE__).Parent = (__HANDLE__);             \
                          } while(0U)

#define UNUSED(X) (void)X      /* To avoid gcc/g++ warnings */

/* Bit manipulation macros */
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)    ((REG) & (BIT))
#define CLEAR_REG(REG)        ((REG) = (0x0))
#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define READ_REG(REG)         ((REG))
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

/* Define SysTick for CI build */
typedef struct
{
  volatile uint32_t CTRL;
  volatile uint32_t LOAD;
  volatile uint32_t VAL;
  volatile const uint32_t CALIB;
} SysTick_Type;

/* Memory mapping of Core Hardware */
#define SysTick_BASE        (0xE000E010UL)
#define SysTick             ((SysTick_Type *)SysTick_BASE)

/* IRQn definitions */
typedef enum
{
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                          */
  HardFault_IRQn              = -13,    /*!< 3 Cortex-M Hard Fault Interrupt                                   */
  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M Memory Management Interrupt                            */
  BusFault_IRQn               = -11,    /*!< 5 Cortex-M Bus Fault Interrupt                                    */
  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M Usage Fault Interrupt                                  */
  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M SV Call Interrupt                                     */
  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M Debug Monitor Interrupt                               */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M Pend SV Interrupt                                     */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M System Tick Interrupt                                 */
} IRQn_Type;

/* DBGMCU definition for CI build */
typedef struct
{
  volatile uint32_t CR;        /*!< Debug MCU configuration register,    Address offset: 0x00 */
  volatile uint32_t APB3FZ1;   /*!< Debug MCU APB3 freeze register 1,    Address offset: 0x04 */
  volatile uint32_t APB1LFZ1;  /*!< Debug MCU APB1L freeze register 1,   Address offset: 0x08 */
  volatile uint32_t APB1HFZ1;  /*!< Debug MCU APB1H freeze register 1,   Address offset: 0x0C */
  volatile uint32_t APB2FZ1;   /*!< Debug MCU APB2 freeze register 1,    Address offset: 0x10 */
  volatile uint32_t APB4FZ1;   /*!< Debug MCU APB4 freeze register 1,    Address offset: 0x14 */
  uint32_t      RESERVED1[2];  /*!< Reserved, 0x18-0x1C                                       */
  volatile uint32_t APB3FZ2;   /*!< Debug MCU APB3 freeze register 2,    Address offset: 0x20 */
  volatile uint32_t APB1LFZ2;  /*!< Debug MCU APB1L freeze register 2,   Address offset: 0x24 */
  volatile uint32_t APB1HFZ2;  /*!< Debug MCU APB1H freeze register 2,   Address offset: 0x28 */
  volatile uint32_t APB2FZ2;   /*!< Debug MCU APB2 freeze register 2,    Address offset: 0x2C */
  volatile uint32_t APB4FZ2;   /*!< Debug MCU APB4 freeze register 2,    Address offset: 0x30 */
  uint32_t      RESERVED2[2];  /*!< Reserved, 0x34-0x38                                       */
  volatile uint32_t IDCODE;    /*!< MCU device ID code,                  Address offset: 0x3C */
} DBGMCU_TypeDef;

#define DBGMCU_BASE             (0x5C001000UL)
#define DBGMCU                  ((DBGMCU_TypeDef *)DBGMCU_BASE)

/* UID base address definition */
#define UID_BASE                0x1FF1E800UL   /*!< Unique device ID register base address */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7xx_HAL_TYPEDEF_H */
