/**
 * @file stm32h7xx_hal_ci.h
 * @brief STM32H7xx HAL header file for CI builds only
 */

#ifndef __STM32H7XX_HAL_CI_H
#define __STM32H7XX_HAL_CI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Basic type definitions */
#include <stdint.h>
#include <stddef.h>

/* IO definitions */
#define __I     volatile const       /* 'read only' permissions */
#define __O     volatile             /* 'write only' permissions */
#define __IO    volatile             /* 'read / write' permissions */

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

/* GPIO definitions for CI build */
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

/* EXTI Mode definitions */
#define EXTI_MODE_NONE        0x00000000U
#define EXTI_MODE_IT          0x00000001U
#define EXTI_MODE_EVT         0x00000002U
#define EXTI_MODE_IT_EVT      (EXTI_MODE_IT | EXTI_MODE_EVT)

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

/* EXTI Line Command definitions */
#define EXTI_DISABLE          0x00000000U
#define EXTI_ENABLE           0x00000001U

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

/* Define EXTI_TypeDef for CI build to avoid conflicts */
typedef struct
{
  volatile uint32_t IMR1;        /* EXTI Interrupt mask register 1 */
  volatile uint32_t EMR1;        /* EXTI Event mask register 1 */
  volatile uint32_t RTSR1;       /* EXTI Rising trigger selection register 1 */
  volatile uint32_t FTSR1;       /* EXTI Falling trigger selection register 1 */
  volatile uint32_t SWIER1;      /* EXTI Software interrupt event register 1 */
  volatile uint32_t PR1;         /* EXTI Pending register 1 */
  volatile uint32_t IMR2;        /* EXTI Interrupt mask register 2 */
  volatile uint32_t EMR2;        /* EXTI Event mask register 2 */
  volatile uint32_t RTSR2;       /* EXTI Rising trigger selection register 2 */
  volatile uint32_t FTSR2;       /* EXTI Falling trigger selection register 2 */
  volatile uint32_t SWIER2;      /* EXTI Software interrupt event register 2 */
  volatile uint32_t PR2;         /* EXTI Pending register 2 */
  volatile uint32_t D3PMR1;      /* EXTI D3 pending mask register 1 */
  volatile uint32_t D3PCR1L;     /* EXTI D3 pending clear register 1 low */
  volatile uint32_t D3PCR1H;     /* EXTI D3 pending clear register 1 high */
} EXTI_TypeDef;

/* Define EXTI base address for CI build */
#define D3_APB1PERIPH_BASE       (0x58000000UL)
#define EXTI_BASE                (D3_APB1PERIPH_BASE + 0x0000UL)

/* Define EXTI pointers for CI build */
#define EXTI                     ((EXTI_TypeDef *) EXTI_BASE)
#define EXTI_D1                  ((EXTI_TypeDef *) EXTI_BASE)
#define EXTI_D2                  ((EXTI_TypeDef *) EXTI_BASE)
#define EXTI_D3                  ((EXTI_TypeDef *) EXTI_BASE)

/* Define validation macros for CI build */
#define IS_EXTI_MODE_LINE(MODE)  (((MODE) == EXTI_MODE_NONE) || \
                                  ((MODE) == EXTI_MODE_IT)   || \
                                  ((MODE) == EXTI_MODE_EVT)  || \
                                  ((MODE) == EXTI_MODE_IT_EVT))

#define IS_EXTI_D3_LINE(LINE)    (((LINE) == EXTI_LINE0) || ((LINE) == EXTI_LINE1) || \
                                  ((LINE) == EXTI_LINE2) || ((LINE) == EXTI_LINE3) || \
                                  ((LINE) == EXTI_LINE4) || ((LINE) == EXTI_LINE5) || \
                                  ((LINE) == EXTI_LINE6) || ((LINE) == EXTI_LINE7) || \
                                  ((LINE) == EXTI_LINE8) || ((LINE) == EXTI_LINE9) || \
                                  ((LINE) == EXTI_LINE10) || ((LINE) == EXTI_LINE11) || \
                                  ((LINE) == EXTI_LINE12) || ((LINE) == EXTI_LINE13) || \
                                  ((LINE) == EXTI_LINE14) || ((LINE) == EXTI_LINE15))

#define IS_EXTI_D1_LINE          IS_EXTI_D3_LINE
#define IS_EXTI_D2_LINE          IS_EXTI_D3_LINE
#define IS_EXTI_EDGE_LINE        IS_EXTI_D3_LINE
#define IS_HAL_EXTI_CONFIG_LINE  IS_EXTI_D3_LINE

#define IS_EXTI_D3_CLEAR(CLEAR)  (((CLEAR) == EXTI_D3_CLEAR_NONE) || \
                                  ((CLEAR) == EXTI_D3_CLEAR_EXTI) || \
                                  ((CLEAR) == EXTI_D3_CLEAR_RTC)  || \
                                  ((CLEAR) == EXTI_D3_CLEAR_LPTIM1))

/* Register access macros */
#define READ_REG(REG)         ((REG))
#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define READ_BIT(REG, BIT)    ((REG) & (BIT))
#define WRITE_BIT(REG, BIT, VAL) ((REG) = (((REG) & (~(BIT))) | ((VAL) & (BIT))))
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

/* FMC definitions for CI build */
typedef struct {
  volatile uint32_t BTCR[8];
} FMC_Bank1_TypeDef;

extern FMC_Bank1_TypeDef* FMC_Bank1_R;

#define FMC_BCR1_BMAP         0x00000002U

/* External variables */
extern volatile uint32_t uwTick;
extern uint32_t uwTickPrio;
extern HAL_TickFreqTypeDef uwTickFreq;

/* Define GPIO ports for CI build */
extern GPIO_TypeDef* GPIOA;
extern GPIO_TypeDef* GPIOB;
extern GPIO_TypeDef* GPIOC;
extern GPIO_TypeDef* GPIOD;
extern GPIO_TypeDef* GPIOE;
extern GPIO_TypeDef* GPIOF;
extern GPIO_TypeDef* GPIOG;
extern GPIO_TypeDef* GPIOH;

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
void HAL_EXTI_D1_EventInputConfig(uint32_t EXTI_Line, uint32_t EXTI_Mode, uint32_t EXTI_LineCmd);
void HAL_EXTI_D2_EventInputConfig(uint32_t EXTI_Line, uint32_t EXTI_Mode, uint32_t EXTI_LineCmd);
void HAL_EXTI_D3_EventInputConfig(uint32_t EXTI_Line, uint32_t EXTI_LineCmd, uint32_t EXTI_ClearSrc);

#ifdef __cplusplus
}
#endif

#endif /* __STM32H7XX_HAL_CI_H */
