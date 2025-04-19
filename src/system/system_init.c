#include "stm32h7xx.h"

void init_clocks(void) {
    // 1. Enable power interface and allow voltage scaling config
    RCC->APB4ENR |= RCC_APB4ENR_PWRDEN;
    PWR->CR3 |= PWR_CR3_SCUEN;

    // 2. Set voltage scaling to VOS1 (scale 1)
    PWR->D3CR = (PWR->D3CR & ~PWR_D3CR_VOS) | (0x3 << PWR_D3CR_VOS_Pos);
    while ((PWR->D3CR & PWR_D3CR_VOSRDY) == 0); // Wait until voltage scaling is ready

    // 3. Set Flash wait states (4WS for 400-550 MHz)
    FLASH->ACR |= FLASH_ACR_LATENCY_4WS;

    // 4. Enable HSE (assume 25 MHz external crystal)
    RCC->CR |= RCC_CR_HSEON;
    while ((RCC->CR & RCC_CR_HSERDY) == 0); // Wait for HSE ready

    // 5. Select HSE as PLL source and set PLL1 dividers (HSE = 25MHz)
    RCC->PLLCKSELR = (1 << RCC_PLLCKSELR_PLLSRC_Pos) | // HSE selected
                     (1 << RCC_PLLCKSELR_DIVM1_Pos);   // DIVM1 = 1

    // Set PLL1 VCO output frequency: 25MHz * 44 = 1100MHz
    // SYSCLK = 1100 / 2 = 550 MHz (DIVP1 = 2)
    RCC->PLL1DIVR = ((44 - 1) << RCC_PLL1DIVR_N1_Pos) |  // N = 44
                    ((2 - 1)  << RCC_PLL1DIVR_P1_Pos) |  // P = 2
                    ((2 - 1)  << RCC_PLL1DIVR_Q1_Pos) |
                    ((2 - 1)  << RCC_PLL1DIVR_R1_Pos);

    // 6. Enable PLL1
    RCC->CR |= RCC_CR_PLL1ON;
    while ((RCC->CR & RCC_CR_PLL1RDY) == 0); // Wait until PLL1 is locked

    // 7. Set AHB prescaler = 1 (HPRE = 0b0000)
    RCC->D1CFGR = (RCC->D1CFGR & ~RCC_D1CFGR_HPRE) | (0 << RCC_D1CFGR_HPRE_Pos);

    // 8. Select PLL1 as system clock source
    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | (0x3 << RCC_CFGR_SW_Pos); // SW = 0b011 = PLL1
    while ((RCC->CFGR & RCC_CFGR_SWS) != (0x3 << RCC_CFGR_SWS_Pos)); // Wait for switch

    // 9. Enable instruction and data caches
    SCB_EnableICache();
    SCB_EnableDCache();
}
