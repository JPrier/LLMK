/**
 * @file stm32h7xx.h
 * @brief CMSIS STM32H7xx Device Peripheral Access Layer Header File
 */

#ifndef __STM32H7XX_H
#define __STM32H7XX_H

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * @brief STM32H7xx Interrupt Number Definition
 */
typedef enum {
  NonMaskableInt_IRQn         = -14,    /*!< Non Maskable Interrupt                                          */
  HardFault_IRQn              = -13,    /*!< Hard Fault Interrupt                                            */
  MemoryManagement_IRQn       = -12,    /*!< Memory Management Interrupt                                     */
  BusFault_IRQn               = -11,    /*!< Bus Fault Interrupt                                             */
  UsageFault_IRQn             = -10,    /*!< Usage Fault Interrupt                                           */
  SVCall_IRQn                 = -5,     /*!< SV Call Interrupt                                               */
  DebugMonitor_IRQn           = -4,     /*!< Debug Monitor Interrupt                                         */
  PendSV_IRQn                 = -2,     /*!< Pend SV Interrupt                                               */
  SysTick_IRQn                = -1,     /*!< System Tick Interrupt                                           */
  WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                                       */
  PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt                       */
  TAMP_STAMP_IRQn             = 2,      /*!< Tamper and TimeStamp interrupts through the EXTI line           */
  RTC_WKUP_IRQn               = 3,      /*!< RTC Wakeup interrupt through the EXTI line                      */
  FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                                          */
  RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                            */
  EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                            */
  EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                            */
  EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                            */
  EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                            */
  EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                            */
  DMA1_Stream0_IRQn           = 11,     /*!< DMA1 Stream 0 global Interrupt                                  */
  DMA1_Stream1_IRQn           = 12,     /*!< DMA1 Stream 1 global Interrupt                                  */
  DMA1_Stream2_IRQn           = 13,     /*!< DMA1 Stream 2 global Interrupt                                  */
  DMA1_Stream3_IRQn           = 14,     /*!< DMA1 Stream 3 global Interrupt                                  */
  DMA1_Stream4_IRQn           = 15,     /*!< DMA1 Stream 4 global Interrupt                                  */
  DMA1_Stream5_IRQn           = 16,     /*!< DMA1 Stream 5 global Interrupt                                  */
  DMA1_Stream6_IRQn           = 17,     /*!< DMA1 Stream 6 global Interrupt                                  */
  ADC_IRQn                    = 18      /*!< ADC1 and ADC2 global Interrupts                                 */
} IRQn_Type;

/* Cortex-M7 processor and core peripherals */
#include "core_cm7.h"

/* Memory and peripheral registers structures */
typedef struct
{
  volatile uint32_t CR;          /*!< RCC clock control register,                                  Address offset: 0x00 */
  volatile uint32_t CFGR;        /*!< RCC clock configuration register,                            Address offset: 0x04 */
  volatile uint32_t CIR;         /*!< RCC clock interrupt register,                                Address offset: 0x08 */
  volatile uint32_t AHB1RSTR;    /*!< RCC AHB1 peripheral reset register,                          Address offset: 0x0C */
  volatile uint32_t AHB2RSTR;    /*!< RCC AHB2 peripheral reset register,                          Address offset: 0x10 */
  volatile uint32_t AHB3RSTR;    /*!< RCC AHB3 peripheral reset register,                          Address offset: 0x14 */
  uint32_t      RESERVED0;       /*!< Reserved, 0x18                                                                    */
  volatile uint32_t APB1RSTR;    /*!< RCC APB1 peripheral reset register,                          Address offset: 0x1C */
  volatile uint32_t APB2RSTR;    /*!< RCC APB2 peripheral reset register,                          Address offset: 0x20 */
  volatile uint32_t APB3RSTR;    /*!< RCC APB3 peripheral reset register,                          Address offset: 0x24 */
  volatile uint32_t APB4RSTR;    /*!< RCC APB4 peripheral reset register,                          Address offset: 0x28 */
  volatile uint32_t GCR;         /*!< RCC global control register,                                 Address offset: 0x2C */
  volatile uint32_t PLLCKSELR;   /*!< RCC PLLs clock source selection register,                    Address offset: 0x30 */
  volatile uint32_t PLLCFGR;     /*!< RCC PLL configuration register,                              Address offset: 0x34 */
  volatile uint32_t PLL1DIVR;    /*!< RCC PLL1 dividers register,                                  Address offset: 0x38 */
  volatile uint32_t PLL1FRACR;   /*!< RCC PLL1 fractional divider register,                        Address offset: 0x3C */
  volatile uint32_t PLL2DIVR;    /*!< RCC PLL2 dividers register,                                  Address offset: 0x40 */
  volatile uint32_t PLL2FRACR;   /*!< RCC PLL2 fractional divider register,                        Address offset: 0x44 */
  volatile uint32_t PLL3DIVR;    /*!< RCC PLL3 dividers register,                                  Address offset: 0x48 */
  volatile uint32_t PLL3FRACR;   /*!< RCC PLL3 fractional divider register,                        Address offset: 0x4C */
} RCC_TypeDef;

/* Peripheral memory map */
#define PERIPH_BASE           0x40000000UL /*!< Peripheral base address */
#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000UL)
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000UL)
#define AHB2PERIPH_BASE       (PERIPH_BASE + 0x10000000UL)

#define RCC_BASE              (AHB1PERIPH_BASE + 0x4400UL)
#define GPIOA_BASE            (AHB2PERIPH_BASE + 0x0000UL)
#define GPIOB_BASE            (AHB2PERIPH_BASE + 0x0400UL)
#define GPIOC_BASE            (AHB2PERIPH_BASE + 0x0800UL)

#define RCC                 ((RCC_TypeDef *) RCC_BASE)

/* Exported functions prototypes ---------------------------------------------*/
extern void SystemInit(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32H7XX_H */
