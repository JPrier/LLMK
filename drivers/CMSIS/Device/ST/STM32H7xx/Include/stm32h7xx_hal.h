/**
 * @file stm32h7xx_hal.h
 * @brief STM32H7xx HAL header file
 */

#ifndef __STM32H7XX_HAL_H
#define __STM32H7XX_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;

typedef enum
{
  HAL_TICK_FREQ_10HZ         = 100U,
  HAL_TICK_FREQ_100HZ        = 10U,
  HAL_TICK_FREQ_1KHZ         = 1U,
  HAL_TICK_FREQ_DEFAULT      = HAL_TICK_FREQ_1KHZ
} HAL_TickFreqTypeDef;

typedef struct
{
  uint32_t MODER;       /*!< GPIO port mode register */
  uint32_t OTYPER;      /*!< GPIO port output type register */
  uint32_t OSPEEDR;     /*!< GPIO port output speed register */
  uint32_t PUPDR;       /*!< GPIO port pull-up/pull-down register */
  uint32_t IDR;         /*!< GPIO port input data register */
  uint32_t ODR;         /*!< GPIO port output data register */
  uint32_t BSRR;        /*!< GPIO port bit set/reset register */
  uint32_t LCKR;        /*!< GPIO port configuration lock register */
  uint32_t AFR[2];      /*!< GPIO alternate function registers */
} GPIO_TypeDef;

typedef struct
{
  uint32_t Type1;       /*!< FMC Bank1 registers */
} FMC_Bank1_TypeDef;

/* Exported constants --------------------------------------------------------*/
#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected */
#define GPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected */
#define GPIO_PIN_2                 ((uint16_t)0x0004)  /* Pin 2 selected */
#define GPIO_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected */
#define GPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected */
#define GPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected */
#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected */
#define GPIO_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected */
#define GPIO_PIN_8                 ((uint16_t)0x0100)  /* Pin 8 selected */
#define GPIO_PIN_9                 ((uint16_t)0x0200)  /* Pin 9 selected */
#define GPIO_PIN_10                ((uint16_t)0x0400)  /* Pin 10 selected */
#define GPIO_PIN_11                ((uint16_t)0x0800)  /* Pin 11 selected */
#define GPIO_PIN_12                ((uint16_t)0x1000)  /* Pin 12 selected */
#define GPIO_PIN_13                ((uint16_t)0x2000)  /* Pin 13 selected */
#define GPIO_PIN_14                ((uint16_t)0x4000)  /* Pin 14 selected */
#define GPIO_PIN_15                ((uint16_t)0x8000)  /* Pin 15 selected */
#define GPIO_PIN_All               ((uint16_t)0xFFFF)  /* All pins selected */

#define GPIO_PIN_RESET             0U  /*!< PIN RESET */
#define GPIO_PIN_SET               1U  /*!< PIN SET */

#define TICK_INT_PRIORITY          0x0FU  /*!< Tick interrupt priority */

#define NVIC_PRIORITYGROUP_0       0x00000007U  /*!< 0 bit for pre-emption priority, 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1       0x00000006U  /*!< 1 bit for pre-emption priority, 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2       0x00000005U  /*!< 2 bits for pre-emption priority, 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3       0x00000004U  /*!< 3 bits for pre-emption priority, 1 bit for subpriority */
#define NVIC_PRIORITYGROUP_4       0x00000003U  /*!< 4 bits for pre-emption priority, 0 bit for subpriority */

/* Exported macro ------------------------------------------------------------*/
#define __HAL_RCC_APB1L_FORCE_RESET()             do { } while(0)
#define __HAL_RCC_APB1L_RELEASE_RESET()           do { } while(0)
#define __HAL_RCC_APB1H_FORCE_RESET()             do { } while(0)
#define __HAL_RCC_APB1H_RELEASE_RESET()           do { } while(0)
#define __HAL_RCC_APB2_FORCE_RESET()              do { } while(0)
#define __HAL_RCC_APB2_RELEASE_RESET()            do { } while(0)
#define __HAL_RCC_APB3_FORCE_RESET()              do { } while(0)
#define __HAL_RCC_APB3_RELEASE_RESET()            do { } while(0)
#define __HAL_RCC_APB4_FORCE_RESET()              do { } while(0)
#define __HAL_RCC_APB4_RELEASE_RESET()            do { } while(0)
#define __HAL_RCC_AHB1_FORCE_RESET()              do { } while(0)
#define __HAL_RCC_AHB1_RELEASE_RESET()            do { } while(0)
#define __HAL_RCC_AHB2_FORCE_RESET()              do { } while(0)
#define __HAL_RCC_AHB2_RELEASE_RESET()            do { } while(0)
#define __HAL_RCC_AHB3_FORCE_RESET()              do { } while(0)
#define __HAL_RCC_AHB3_RELEASE_RESET()            do { } while(0)
#define __HAL_RCC_AHB4_FORCE_RESET()              do { } while(0)
#define __HAL_RCC_AHB4_RELEASE_RESET()            do { } while(0)

/* Exported functions --------------------------------------------------------*/
HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_DeInit(void);
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
uint32_t HAL_RCC_GetSysClockFreq(void);
void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup);
void HAL_NVIC_SetPriority(uint32_t IRQn, uint32_t PreemptPriority, uint32_t SubPriority);
uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb);
HAL_StatusTypeDef HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t PinState);
void __disable_irq(void);
void HAL_EXTI_EdgeConfig(uint32_t EXTI_Line, uint32_t EXTI_Edge);
void HAL_EXTI_GenerateSWInterrupt(uint32_t EXTI_Line);
void HAL_EXTI_D1_ClearFlag(uint32_t EXTI_Line);
void HAL_EXTI_D2_ClearFlag(uint32_t EXTI_Line);
void HAL_EXTI_D1_EventInputConfig(uint32_t EXTI_Line, uint32_t EXTI_Mode, uint32_t EXTI_LineCmd);
void HAL_EXTI_D2_EventInputConfig(uint32_t EXTI_Line, uint32_t EXTI_Mode, uint32_t EXTI_LineCmd);
void HAL_EXTI_D3_EventInputConfig(uint32_t EXTI_Line, uint32_t EXTI_LineCmd, uint32_t EXTI_ClearSrc);

/* External variables --------------------------------------------------------*/
extern GPIO_TypeDef* GPIOA;
extern GPIO_TypeDef* GPIOB;
extern GPIO_TypeDef* GPIOC;
extern GPIO_TypeDef* GPIOD;
extern GPIO_TypeDef* GPIOE;
extern GPIO_TypeDef* GPIOF;
extern GPIO_TypeDef* GPIOG;
extern GPIO_TypeDef* GPIOH;
extern FMC_Bank1_TypeDef* FMC_Bank1_R;
extern volatile uint32_t uwTick;
extern uint32_t uwTickPrio;
extern HAL_TickFreqTypeDef uwTickFreq;
extern uint32_t SystemCoreClock;
extern uint32_t SystemD2Clock;
extern const uint8_t D1CorePrescTable[16];

#ifdef __cplusplus
}
#endif

#endif /* __STM32H7XX_HAL_H */
