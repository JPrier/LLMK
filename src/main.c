/**
 * @file main.c
 * @brief Main entry point for the LLMK firmware
 */

#include "main.h"
#include "stm32h7xx_hal.h"  // ensure HAL is included
#include "keyboard.h"
#include "usb_device.h"

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock to 550 MHz */
  /* This would be implemented in a real application */
  
  /* Initialize all configured peripherals */
  /* This would configure GPIO pins for key inputs with external interrupts */
  
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
