/**
  ******************************************************************************
  * @file    system_stm32h7xx.c
  * @brief   CMSIS Cortex-M7 Device Peripheral Access Layer System Source File
  ******************************************************************************
  */

#include "stm32h7xx.h"

/**
  * @brief  Setup the microcontroller system
  *         Initialize the FPU, set up the memory areas, initialize the 
  *         clock configuration for the application.
  * @param  None
  * @retval None
  */
void SystemInit(void)
{
  /* FPU settings */
  #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    /* Set CP10 and CP11 Full Access */
    SCB->CPACR |= ((3UL << 20U)|(3UL << 22U));
  #endif

  /* Reset the RCC clock configuration to the default reset state */
  /* Set HSION bit */
  RCC->CR |= RCC_CR_HSION;

  /* Reset CFGR register */
  RCC->CFGR = 0x00000000;

  /* Reset HSEON, CSSON , CSION, RC48ON, CSIKERON, PLL1ON, PLL2ON and PLL3ON bits */
  RCC->CR &= 0xEAF6ED7FU;

  /* Reset PLLCKSELR register */
  RCC->PLLCKSELR = 0x02020200U;

  /* Reset PLLCFGR register */
  RCC->PLLCFGR = 0x01FF0000U;

  /* Reset PLL1DIVR register */
  RCC->PLL1DIVR = 0x01010280U;

  /* Reset PLL1FRACR register */
  RCC->PLL1FRACR = 0x00000000U;

  /* Reset PLL2DIVR register */
  RCC->PLL2DIVR = 0x01010280U;

  /* Reset PLL2FRACR register */
  RCC->PLL2FRACR = 0x00000000U;

  /* Reset PLL3DIVR register */
  RCC->PLL3DIVR = 0x01010280U;

  /* Reset PLL3FRACR register */
  RCC->PLL3FRACR = 0x00000000U;

  /* Reset HSEBYP bit */
  RCC->CR &= 0xFFFBFFFFU;

  /* Disable all interrupts */
  RCC->CIER = 0x00000000U;
}
