/**
 * @file stm32h7xx_hal.h
 * @brief STM32H7xx HAL header file placeholder for CI build
 */

#ifndef __STM32H7XX_HAL_H
#define __STM32H7XX_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Basic type definitions */
#include <stdint.h>
#include <stddef.h>
#include "stm32h7xx_hal_typedef.h"
#include "stm32h7xx_hal_def.h"
#include "stm32h7xx_hal_exti.h"
#include "stm32h7xx_hal_exti_reg.h"

/* GPIO definitions */
typedef struct {
  uint32_t Pin;
  uint32_t Mode;
  uint32_t Pull;
  uint32_t Speed;
  uint32_t Alternate;
} GPIO_InitTypeDef;

typedef struct {
  void* Instance;
} GPIO_TypeDef;

/* GPIO Pin states */
#define GPIO_PIN_RESET 0
#define GPIO_PIN_SET   1

/* EXTI Edge definitions */
#define EXTI_RISING_EDGE      0x00000001U
#define EXTI_FALLING_EDGE     0x00000002U
#define EXTI_RISING_FALLING_EDGE  (EXTI_RISING_EDGE | EXTI_FALLING_EDGE)

/* EXTI Line definitions */
#define EXTI_LINE0       (0x00000000U)
#define EXTI_LINE1       (0x00000001U)
#define EXTI_LINE2       (0x00000002U)
#define EXTI_LINE3       (0x00000003U)
#define EXTI_LINE4       (0x00000004U)
#define EXTI_LINE5       (0x00000005U)
#define EXTI_LINE6       (0x00000006U)
#define EXTI_LINE7       (0x00000007U)
#define EXTI_LINE8       (0x00000008U)
#define EXTI_LINE9       (0x00000009U)
#define EXTI_LINE10      (0x0000000AU)
#define EXTI_LINE11      (0x0000000BU)
#define EXTI_LINE12      (0x0000000CU)
#define EXTI_LINE13      (0x0000000DU)
#define EXTI_LINE14      (0x0000000EU)
#define EXTI_LINE15      (0x0000000FU)

/* EXTI D3 Clear Source definitions */
#define EXTI_D3_CLEAR_NONE    0x00000000U
#define EXTI_D3_CLEAR_EXTI    0x00000001U
#define EXTI_D3_CLEAR_RTC     0x00000002U
#define EXTI_D3_CLEAR_LPTIM1  0x00000003U

/* EXTI D3 Line definitions */
#define IS_EXTI_D3_LINE(LINE) (((LINE) == EXTI_LINE0) || ((LINE) == EXTI_LINE1) || \
                              ((LINE) == EXTI_LINE2) || ((LINE) == EXTI_LINE3) || \
                              ((LINE) == EXTI_LINE4) || ((LINE) == EXTI_LINE5) || \
                              ((LINE) == EXTI_LINE6) || ((LINE) == EXTI_LINE7) || \
                              ((LINE) == EXTI_LINE8) || ((LINE) == EXTI_LINE9) || \
                              ((LINE) == EXTI_LINE10) || ((LINE) == EXTI_LINE11) || \
                              ((LINE) == EXTI_LINE12) || ((LINE) == EXTI_LINE13) || \
                              ((LINE) == EXTI_LINE14) || ((LINE) == EXTI_LINE15))

/* EXTI D3 Clear Source check */
#define IS_EXTI_D3_CLEAR(SOURCE) (((SOURCE) == EXTI_D3_CLEAR_NONE) || \
                                 ((SOURCE) == EXTI_D3_CLEAR_EXTI) || \
                                 ((SOURCE) == EXTI_D3_CLEAR_RTC) || \
                                 ((SOURCE) == EXTI_D3_CLEAR_LPTIM1))

/* Function prototypes */
HAL_StatusTypeDef HAL_Init(void);
void HAL_DeInit(void);
void HAL_MspInit(void);
void HAL_MspDeInit(void);
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority);
void HAL_IncTick(void);
uint32_t HAL_GetTick(void);
uint32_t HAL_GetTickPrio(void);
HAL_StatusTypeDef HAL_SetTickFreq(HAL_TickFreqTypeDef Freq);
HAL_TickFreqTypeDef HAL_GetTickFreq(void);
void HAL_Delay(uint32_t Delay);
void HAL_SuspendTick(void);
void HAL_ResumeTick(void);
uint32_t HAL_GetHalVersion(void);
uint32_t HAL_GetREVID(void);
uint32_t HAL_GetDEVID(void);
uint32_t HAL_GetUIDw0(void);
uint32_t HAL_GetUIDw1(void);
uint32_t HAL_GetUIDw2(void);
void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup);
void HAL_NVIC_SetPriority(uint32_t IRQn, uint32_t PreemptPriority, uint32_t SubPriority);
uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb);
HAL_StatusTypeDef HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t PinState);
void __disable_irq(void);

/* EXTI functions */
void HAL_EXTI_EdgeConfig(uint32_t EXTI_Line, uint32_t EXTI_Edge);
void HAL_EXTI_GenerateSWInterrupt(uint32_t EXTI_Line);
void HAL_EXTI_D1_ClearFlag(uint32_t EXTI_Line);
void HAL_EXTI_D2_ClearFlag(uint32_t EXTI_Line);
void HAL_EXTI_D1_EventInputConfig(uint32_t EXTI_Line, uint32_t EXTI_LineCmd);
void HAL_EXTI_D2_EventInputConfig(uint32_t EXTI_Line, uint32_t EXTI_LineCmd);
void HAL_EXTI_D3_EventInputConfig(uint32_t EXTI_Line, uint32_t EXTI_LineCmd, uint32_t EXTI_ClearSrc);

/* Define some GPIO pins for CI build */
#define GPIO_PIN_0  ((uint16_t)0x0001)
#define GPIO_PIN_1  ((uint16_t)0x0002)
#define GPIO_PIN_2  ((uint16_t)0x0004)
#define GPIO_PIN_3  ((uint16_t)0x0008)
#define GPIO_PIN_4  ((uint16_t)0x0010)
#define GPIO_PIN_5  ((uint16_t)0x0020)
#define GPIO_PIN_6  ((uint16_t)0x0040)
#define GPIO_PIN_7  ((uint16_t)0x0080)
#define GPIO_PIN_8  ((uint16_t)0x0100)
#define GPIO_PIN_9  ((uint16_t)0x0200)
#define GPIO_PIN_10 ((uint16_t)0x0400)
#define GPIO_PIN_11 ((uint16_t)0x0800)
#define GPIO_PIN_12 ((uint16_t)0x1000)
#define GPIO_PIN_13 ((uint16_t)0x2000)
#define GPIO_PIN_14 ((uint16_t)0x4000)
#define GPIO_PIN_15 ((uint16_t)0x8000)
#define GPIO_PIN_All ((uint16_t)0xFFFF)

/* External variables */
extern volatile uint32_t uwTick;
extern uint32_t uwTickPrio;
extern HAL_TickFreqTypeDef uwTickFreq;

#ifdef __cplusplus
}
#endif

#endif /* __STM32H7XX_HAL_H */
