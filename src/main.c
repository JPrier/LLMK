/**
 * @file main.c
 * @brief Main entry point for the LLMK firmware
 */

#include "main.h"
#include "stm32h7xx_hal.h"
#include "usb_device.h"
#include "keyboard.h"

/* Private function prototypes */
static void SystemClock_Config(void);
static void GPIO_Init(void);
static void Error_Handler(void);

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock to 550 MHz */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  GPIO_Init();
  
  /* Initialize USB device */
  MX_USB_DEVICE_Init();
  
  /* Initialize keyboard handling */
  Keyboard_Init();

  /* Infinite loop */
  while (1)
  {
    /* Process keyboard events */
    Keyboard_Process();
  }
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
static void SystemClock_Config(void)
{
  /* Configure the system clock to 550 MHz using PLL with HSE as source */
  /* TODO: Add proper clock configuration for STM32H723ZGT6 */
}

/**
 * @brief GPIO Initialization
 * @retval None
 */
static void GPIO_Init(void)
{
  /* TODO: Add GPIO initialization for key inputs with external interrupts */
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
static void Error_Handler(void)
{
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
}
