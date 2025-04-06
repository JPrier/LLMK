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

/* For assert_param */
#include <assert.h>

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

/* Define validation macro for FMC */
#define IS_FMC_SWAPBMAP_MODE(MODE) (((MODE) == 0x00000000U) || ((MODE) == FMC_BCR1_BMAP))

/* NVIC definitions for CI build */
#define NVIC_PRIORITYGROUP_0         0x00000007U
#define NVIC_PRIORITYGROUP_1         0x00000006U
#define NVIC_PRIORITYGROUP_2         0x00000005U
#define NVIC_PRIORITYGROUP_3         0x00000004U
#define NVIC_PRIORITYGROUP_4         0x00000003U

/* DBGMCU definitions for CI build */
typedef struct {
  volatile uint32_t CR;
  volatile uint32_t APB3FZ1;
  volatile uint32_t APB1LFZ1;
  volatile uint32_t APB1HFZ1;
  volatile uint32_t APB2FZ1;
  volatile uint32_t APB4FZ1;
  uint32_t RESERVED1[2];
  volatile uint32_t APB3FZ2;
  volatile uint32_t APB1LFZ2;
  volatile uint32_t APB1HFZ2;
  volatile uint32_t APB2FZ2;
  volatile uint32_t APB4FZ2;
  uint32_t RESERVED2[2];
  volatile uint32_t IDCODE;
} DBGMCU_TypeDef;

#define DBGMCU_BASE             (0x5C001000UL)
#define DBGMCU                  ((DBGMCU_TypeDef *)DBGMCU_BASE)

/* DBGMCU CR register bit definitions */
#define DBGMCU_CR_DBG_SLEEPD1       0x00000001U
#define DBGMCU_CR_DBG_STOPD1        0x00000002U
#define DBGMCU_CR_DBG_STANDBYD1     0x00000004U

/* RCC definitions for CI build */
typedef struct {
  volatile uint32_t CR;
  volatile uint32_t HSICFGR;
  volatile uint32_t CRRCR;
  volatile uint32_t CSICFGR;
  volatile uint32_t CFGR;
  volatile uint32_t RESERVED0;
  volatile uint32_t CDCFGR1;
  volatile uint32_t CDCFGR2;
  volatile uint32_t RESERVED1;
  volatile uint32_t PLLCKSELR;
  volatile uint32_t PLLCFGR;
  volatile uint32_t PLL1DIVR;
  volatile uint32_t PLL1FRACR;
  volatile uint32_t PLL2DIVR;
  volatile uint32_t PLL2FRACR;
  volatile uint32_t PLL3DIVR;
  volatile uint32_t PLL3FRACR;
  volatile uint32_t RESERVED2;
  volatile uint32_t D1CCIPR;
  volatile uint32_t D2CCIP1R;
  volatile uint32_t D2CCIP2R;
  volatile uint32_t D3CCIPR;
  volatile uint32_t RESERVED3;
  volatile uint32_t CIER;
  volatile uint32_t CIFR;
  volatile uint32_t CICR;
  volatile uint32_t RESERVED4;
  volatile uint32_t BDCR;
  volatile uint32_t CSR;
  volatile uint32_t RESERVED5;
  volatile uint32_t AHB3RSTR;
  volatile uint32_t AHB1RSTR;
  volatile uint32_t AHB2RSTR;
  volatile uint32_t AHB4RSTR;
  volatile uint32_t APB3RSTR;
  volatile uint32_t APB1LRSTR;
  volatile uint32_t APB1HRSTR;
  volatile uint32_t APB2RSTR;
  volatile uint32_t APB4RSTR;
  volatile uint32_t GCR;
  volatile uint32_t RESERVED6;
  volatile uint32_t D3AMR;
  volatile uint32_t RESERVED7[9];
  volatile uint32_t RSR;
  volatile uint32_t AHB3ENR;
  volatile uint32_t AHB1ENR;
  volatile uint32_t AHB2ENR;
  volatile uint32_t AHB4ENR;
  volatile uint32_t APB3ENR;
  volatile uint32_t APB1LENR;
  volatile uint32_t APB1HENR;
  volatile uint32_t APB2ENR;
  volatile uint32_t APB4ENR;
  volatile uint32_t RESERVED8;
  volatile uint32_t AHB3LPENR;
  volatile uint32_t AHB1LPENR;
  volatile uint32_t AHB2LPENR;
  volatile uint32_t AHB4LPENR;
  volatile uint32_t APB3LPENR;
  volatile uint32_t APB1LLPENR;
  volatile uint32_t APB1HLPENR;
  volatile uint32_t APB2LPENR;
  volatile uint32_t APB4LPENR;
  volatile uint32_t RESERVED9[4];
} RCC_TypeDef;

#define RCC_BASE              (0x58024400UL)
#define RCC                   ((RCC_TypeDef *)RCC_BASE)

/* RCC register bit definitions */
#define RCC_CDCFGR1_CDCPRE        0x00000700U
#define RCC_CDCFGR1_CDCPRE_Pos    8U
#define RCC_CDCFGR1_HPRE          0x000000F0U
#define RCC_CDCFGR1_HPRE_Pos      4U

/* SYSCFG definitions for CI build */
typedef struct {
  volatile uint32_t PMCR;         /* SYSCFG power management control register */
  volatile uint32_t EXTICR[4];    /* SYSCFG external interrupt configuration registers */
  volatile uint32_t CFGR;         /* SYSCFG configuration register */
  volatile uint32_t CCCSR;        /* SYSCFG compensation cell control and status register */
  volatile uint32_t CCVR;         /* SYSCFG compensation cell value register */
  volatile uint32_t CCCR;         /* SYSCFG compensation cell code register */
} SYSCFG_TypeDef;

#define PERIPH_BASE              (0x40000000UL)
#define APB3PERIPH_BASE          (PERIPH_BASE + 0x10000000UL)
#define SYSCFG_BASE              (APB3PERIPH_BASE + 0x0000UL)
#define SYSCFG                   ((SYSCFG_TypeDef *)SYSCFG_BASE)

/* SYSCFG CCCSR register bit definitions */
#define SYSCFG_CCCSR_EN          0x00000001U
#define SYSCFG_CCCSR_CS          0x00000002U
#define SYSCFG_CCCSR_READY       0x00000004U
#define SYSCFG_CCCSR_HSLV0       0x00000010U
#define SYSCFG_CCCSR_HSLV1       0x00000020U
#define SYSCFG_CCCSR_HSLV2       0x00000040U
#define SYSCFG_CCCSR_HSLV3       0x00000080U

/* SYSCFG CCCR register bit definitions */
#define SYSCFG_CCCR_NCC          0x0000000FU
#define SYSCFG_CCCR_PCC          0x000000F0U

/* SYSCFG validation macros */
#define IS_SYSCFG_CODE_SELECT(CODE) (((CODE) == SYSCFG_CCCSR_CS) || ((CODE) == 0x00000000U))
#define IS_SYSCFG_CODE_CONFIG(CODE) ((CODE) <= 0x0FU)

/* VREFBUF definitions for CI build */
typedef struct {
  volatile uint32_t CSR;         /* VREFBUF control and status register */
  volatile uint32_t CCR;         /* VREFBUF calibration and control register */
} VREFBUF_TypeDef;

#define VREFBUF_BASE              (APB3PERIPH_BASE + 0x0F00UL)
#define VREFBUF                   ((VREFBUF_TypeDef *)VREFBUF_BASE)

/* VREFBUF CSR register bit definitions */
#define VREFBUF_CSR_ENVR          0x00000001U
#define VREFBUF_CSR_HIZ           0x00000002U
#define VREFBUF_CSR_VRR           0x00000008U
#define VREFBUF_CSR_VRS           0x00000010U

/* VREFBUF CCR register bit definitions */
#define VREFBUF_CCR_TRIM          0x0000003FU

/* SYSCFG PMCR register bit definitions for analog switch */
#define SYSCFG_PMCR_BOOSTEN       0x00000100U
#define SYSCFG_PMCR_ANASWVDD      0x00010000U
#define SYSCFG_PMCR_ANA1SWVDD     0x00020000U
#define SYSCFG_PMCR_ANA2SWVDD     0x00040000U
#define SYSCFG_PMCR_ANASWVDD_PD   0x00100000U
#define SYSCFG_PMCR_ANA1SWVDD_PD  0x00200000U
#define SYSCFG_PMCR_ANA2SWVDD_PD  0x00400000U

/* SYSCFG validation macros for VREFBUF and analog switch */
#define IS_SYSCFG_VREFBUF_TRIMMING(VALUE) ((VALUE) <= 0x3FU)
#define IS_SYSCFG_VREFBUF_HIGH_IMPEDANCE(VALUE) (((VALUE) == SYSCFG_PMCR_BOOSTEN) || ((VALUE) == 0x00000000U))
#define IS_SYSCFG_VREFBUF_VOLTAGE_SCALE(VALUE) (((VALUE) == SYSCFG_PMCR_BOOSTEN) || ((VALUE) == 0x00000000U))

#define IS_SYSCFG_ANALOG_SWITCH(VALUE) (((VALUE) == SYSCFG_PMCR_ANASWVDD) || \
                                        ((VALUE) == SYSCFG_PMCR_ANA1SWVDD) || \
                                        ((VALUE) == SYSCFG_PMCR_ANA2SWVDD))

#define IS_SYSCFG_SWITCH_STATE(VALUE) (((VALUE) == 0x00000000U) || ((VALUE) == 0x00000001U))

/* System clock variables */
extern uint32_t SystemCoreClock;
extern uint32_t SystemD2Clock;
extern const uint8_t D1CorePrescTable[16];

/* Tick priority definition */
#define TICK_INT_PRIORITY          0x0FU

/* RCC reset macros */
#define __HAL_RCC_AHB3_FORCE_RESET()           (RCC->AHB3RSTR = 0xFFFFFFFFU)
#define __HAL_RCC_AHB3_RELEASE_RESET()         (RCC->AHB3RSTR = 0x00U)
#define __HAL_RCC_AHB1_FORCE_RESET()           (RCC->AHB1RSTR = 0xFFFFFFFFU)
#define __HAL_RCC_AHB1_RELEASE_RESET()         (RCC->AHB1RSTR = 0x00U)
#define __HAL_RCC_AHB2_FORCE_RESET()           (RCC->AHB2RSTR = 0xFFFFFFFFU)
#define __HAL_RCC_AHB2_RELEASE_RESET()         (RCC->AHB2RSTR = 0x00U)
#define __HAL_RCC_AHB4_FORCE_RESET()           (RCC->AHB4RSTR = 0xFFFFFFFFU)
#define __HAL_RCC_AHB4_RELEASE_RESET()         (RCC->AHB4RSTR = 0x00U)
#define __HAL_RCC_APB3_FORCE_RESET()           (RCC->APB3RSTR = 0xFFFFFFFFU)
#define __HAL_RCC_APB3_RELEASE_RESET()         (RCC->APB3RSTR = 0x00U)
#define __HAL_RCC_APB1L_FORCE_RESET()          (RCC->APB1LRSTR = 0xFFFFFFFFU)
#define __HAL_RCC_APB1L_RELEASE_RESET()        (RCC->APB1LRSTR = 0x00U)
#define __HAL_RCC_APB1H_FORCE_RESET()          (RCC->APB1HRSTR = 0xFFFFFFFFU)
#define __HAL_RCC_APB1H_RELEASE_RESET()        (RCC->APB1HRSTR = 0x00U)
#define __HAL_RCC_APB2_FORCE_RESET()           (RCC->APB2RSTR = 0xFFFFFFFFU)
#define __HAL_RCC_APB2_RELEASE_RESET()         (RCC->APB2RSTR = 0x00U)
#define __HAL_RCC_APB4_FORCE_RESET()           (RCC->APB4RSTR = 0xFFFFFFFFU)
#define __HAL_RCC_APB4_RELEASE_RESET()         (RCC->APB4RSTR = 0x00U)

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
uint32_t HAL_RCC_GetSysClockFreq(void);
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
