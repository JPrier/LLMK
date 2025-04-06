/**
 * @file stm32h7xx_hal_ci.c
 * @brief STM32H7xx HAL implementation for CI builds only
 */

#ifdef CI_BUILD

#include "stm32h7xx_hal.h"

/* GPIO port instances for CI build */
GPIO_TypeDef* GPIOA = NULL;
GPIO_TypeDef* GPIOB = NULL;
GPIO_TypeDef* GPIOC = NULL;
GPIO_TypeDef* GPIOD = NULL;
GPIO_TypeDef* GPIOE = NULL;
GPIO_TypeDef* GPIOF = NULL;
GPIO_TypeDef* GPIOG = NULL;
GPIO_TypeDef* GPIOH = NULL;

/* FMC instance for CI build */
FMC_Bank1_TypeDef* FMC_Bank1_R = NULL;

/* HAL variables */
volatile uint32_t uwTick = 0;
uint32_t uwTickPrio = 0;
HAL_TickFreqTypeDef uwTickFreq = HAL_TICK_FREQ_DEFAULT;

/* System clock variables */
uint32_t SystemCoreClock = 550000000U; /* Default to 550 MHz */
uint32_t SystemD2Clock = 275000000U;   /* Default to 275 MHz */
const uint8_t D1CorePrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};

/**
 * @brief  Initialize the HAL Library.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_Init(void)
{
  /* Set Interrupt Group Priority */
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
  
  /* Use SysTick as time base source and configure 1ms tick */
  HAL_InitTick(TICK_INT_PRIORITY);
  
  /* Init the low level hardware */
  HAL_MspInit();
  
  return HAL_OK;
}

/**
 * @brief  DeInitialize the HAL Library.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_DeInit(void)
{
  /* Reset of all peripherals */
  __HAL_RCC_APB1L_FORCE_RESET();
  __HAL_RCC_APB1L_RELEASE_RESET();
  __HAL_RCC_APB1H_FORCE_RESET();
  __HAL_RCC_APB1H_RELEASE_RESET();
  __HAL_RCC_APB2_FORCE_RESET();
  __HAL_RCC_APB2_RELEASE_RESET();
  __HAL_RCC_APB3_FORCE_RESET();
  __HAL_RCC_APB3_RELEASE_RESET();
  __HAL_RCC_APB4_FORCE_RESET();
  __HAL_RCC_APB4_RELEASE_RESET();
  __HAL_RCC_AHB1_FORCE_RESET();
  __HAL_RCC_AHB1_RELEASE_RESET();
  __HAL_RCC_AHB2_FORCE_RESET();
  __HAL_RCC_AHB2_RELEASE_RESET();
  __HAL_RCC_AHB3_FORCE_RESET();
  __HAL_RCC_AHB3_RELEASE_RESET();
  __HAL_RCC_AHB4_FORCE_RESET();
  __HAL_RCC_AHB4_RELEASE_RESET();

  /* De-Init the low level hardware */
  HAL_MspDeInit();
    
  /* Return to default Tick Freq */
  uwTickFreq = HAL_TICK_FREQ_DEFAULT;
  
  return HAL_OK;
}

/**
 * @brief  Initialize the MSP.
 * @retval None
 */
void HAL_MspInit(void)
{
}

/**
 * @brief  DeInitialize the MSP.
 * @retval None
 */
void HAL_MspDeInit(void)
{
}

/**
 * @brief  This function configures the source of the time base.
 * @param  TickPriority: Tick interrupt priority.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  uwTickPrio = TickPriority;
  return HAL_OK;
}

/**
 * @brief  Increment a tick value.
 * @retval None
 */
void HAL_IncTick(void)
{
  uwTick++;
}

/**
 * @brief  Get tick value.
 * @retval Tick value
 */
uint32_t HAL_GetTick(void)
{
  return uwTick;
}

/**
 * @brief  Get tick priority.
 * @retval Tick priority
 */
uint32_t HAL_GetTickPrio(void)
{
  return uwTickPrio;
}

/**
 * @brief  Set new tick frequency.
 * @param  Freq: Tick frequency
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_SetTickFreq(HAL_TickFreqTypeDef Freq)
{
  uwTickFreq = Freq;
  return HAL_OK;
}

/**
 * @brief  Get tick frequency.
 * @retval Tick frequency
 */
HAL_TickFreqTypeDef HAL_GetTickFreq(void)
{
  return uwTickFreq;
}

/**
 * @brief  Delay execution for a given number of milliseconds.
 * @param  Delay: Delay in milliseconds
 * @retval None
 */
void HAL_Delay(uint32_t Delay)
{
  uint32_t tickstart = HAL_GetTick();
  while((HAL_GetTick() - tickstart) < Delay)
  {
  }
}

/**
 * @brief  Suspend Tick increment.
 * @retval None
 */
void HAL_SuspendTick(void)
{
}

/**
 * @brief  Resume Tick increment.
 * @retval None
 */
void HAL_ResumeTick(void)
{
}

/**
 * @brief  Get HAL version.
 * @retval HAL version
 */
uint32_t HAL_GetHalVersion(void)
{
  return 0x01000000U;
}

/**
 * @brief  Get device revision identifier.
 * @retval Device revision identifier
 */
uint32_t HAL_GetREVID(void)
{
  return 0U;
}

/**
 * @brief  Get device identifier.
 * @retval Device identifier
 */
uint32_t HAL_GetDEVID(void)
{
  return 0U;
}

/**
 * @brief  Get first word of the unique device identifier.
 * @retval Device identifier first word
 */
uint32_t HAL_GetUIDw0(void)
{
  return 0U;
}

/**
 * @brief  Get second word of the unique device identifier.
 * @retval Device identifier second word
 */
uint32_t HAL_GetUIDw1(void)
{
  return 0U;
}

/**
 * @brief  Get third word of the unique device identifier.
 * @retval Device identifier third word
 */
uint32_t HAL_GetUIDw2(void)
{
  return 0U;
}

/**
 * @brief  Get system clock frequency.
 * @retval System clock frequency
 */
uint32_t HAL_RCC_GetSysClockFreq(void)
{
  return SystemCoreClock;
}

/**
 * @brief  Set the NVIC priority grouping.
 * @param  PriorityGroup: Priority grouping
 * @retval None
 */
void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
}

/**
 * @brief  Set the priority of an interrupt.
 * @param  IRQn: IRQ number
 * @param  PreemptPriority: Preemption priority
 * @param  SubPriority: Sub-priority
 * @retval None
 */
void HAL_NVIC_SetPriority(uint32_t IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{
}

/**
 * @brief  Configure the SysTick clock source.
 * @param  TicksNumb: Number of ticks between two interrupts
 * @retval Status
 */
uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb)
{
  return 0U;
}

/**
 * @brief  Read the specified GPIO pin.
 * @param  GPIOx: GPIO port
 * @param  GPIO_Pin: GPIO pin
 * @retval GPIO pin state
 */
HAL_StatusTypeDef HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  return GPIO_PIN_RESET;
}

/**
 * @brief  Write to the specified GPIO pin.
 * @param  GPIOx: GPIO port
 * @param  GPIO_Pin: GPIO pin
 * @param  PinState: Pin state
 * @retval None
 */
void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t PinState)
{
}

/**
 * @brief  Disable interrupts.
 * @retval None
 */
void __disable_irq(void)
{
}

/**
 * @brief  Configure the EXTI edge.
 * @param  EXTI_Line: EXTI line
 * @param  EXTI_Edge: EXTI edge
 * @retval None
 */
void HAL_EXTI_EdgeConfig(uint32_t EXTI_Line, uint32_t EXTI_Edge)
{
}

/**
 * @brief  Generate a software interrupt on the EXTI line.
 * @param  EXTI_Line: EXTI line
 * @retval None
 */
void HAL_EXTI_GenerateSWInterrupt(uint32_t EXTI_Line)
{
}

/**
 * @brief  Clear the EXTI flag for D1 domain.
 * @param  EXTI_Line: EXTI line
 * @retval None
 */
void HAL_EXTI_D1_ClearFlag(uint32_t EXTI_Line)
{
}

/**
 * @brief  Clear the EXTI flag for D2 domain.
 * @param  EXTI_Line: EXTI line
 * @retval None
 */
void HAL_EXTI_D2_ClearFlag(uint32_t EXTI_Line)
{
}

/**
 * @brief  Configure the EXTI event input for D1 domain.
 * @param  EXTI_Line: EXTI line
 * @param  EXTI_Mode: EXTI mode
 * @param  EXTI_LineCmd: EXTI line command
 * @retval None
 */
void HAL_EXTI_D1_EventInputConfig(uint32_t EXTI_Line, uint32_t EXTI_Mode, uint32_t EXTI_LineCmd)
{
}

/**
 * @brief  Configure the EXTI event input for D2 domain.
 * @param  EXTI_Line: EXTI line
 * @param  EXTI_Mode: EXTI mode
 * @param  EXTI_LineCmd: EXTI line command
 * @retval None
 */
void HAL_EXTI_D2_EventInputConfig(uint32_t EXTI_Line, uint32_t EXTI_Mode, uint32_t EXTI_LineCmd)
{
}

/**
 * @brief  Configure the EXTI event input for D3 domain.
 * @param  EXTI_Line: EXTI line
 * @param  EXTI_LineCmd: EXTI line command
 * @param  EXTI_ClearSrc: EXTI clear source
 * @retval None
 */
void HAL_EXTI_D3_EventInputConfig(uint32_t EXTI_Line, uint32_t EXTI_LineCmd, uint32_t EXTI_ClearSrc)
{
}

#endif /* CI_BUILD */
