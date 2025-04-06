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

/* HAL variables */
volatile uint32_t uwTick = 0;
uint32_t uwTickPrio = 0;
HAL_TickFreqTypeDef uwTickFreq = HAL_TICK_FREQ_DEFAULT;

/**
 * @brief  Initialize the HAL Library.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_Init(void)
{
  return HAL_OK;
}

/**
 * @brief  DeInitialize the HAL Library.
 * @retval None
 */
void HAL_DeInit(void)
{
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
 * @param  EXTI_LineCmd: EXTI line command
 * @retval None
 */
void HAL_EXTI_D1_EventInputConfig(uint32_t EXTI_Line, uint32_t EXTI_LineCmd)
{
}

/**
 * @brief  Configure the EXTI event input for D2 domain.
 * @param  EXTI_Line: EXTI line
 * @param  EXTI_LineCmd: EXTI line command
 * @retval None
 */
void HAL_EXTI_D2_EventInputConfig(uint32_t EXTI_Line, uint32_t EXTI_LineCmd)
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
