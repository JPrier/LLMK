/**
 * @file keyboard.c
 * @brief Keyboard handling implementation
 */

#include "keyboard.h"
#include "usb_device.h"
#include "usbd_hid.h"
#include <string.h>

/* Private defines -----------------------------------------------------------*/
#define MAX_KEYS 87  /* Tenkeyless keyboard has 87 keys */

/* Private variables ---------------------------------------------------------*/
static Key_TypeDef keys[MAX_KEYS];
static uint8_t keyState[MAX_KEYS];
static uint8_t keyReport[8] = {0}; /* Standard HID keyboard report */

/**
 * @brief Initialize the keyboard handling
 * @retval None
 */
void Keyboard_Init(void)
{
  /* Initialize key mapping and GPIO interrupts */
  /* TODO: Configure all key mappings and related GPIO pins */
  
  /* Clear all key states */
  memset(keyState, 0, sizeof(keyState));
  memset(keyReport, 0, sizeof(keyReport));
}

/**
 * @brief Process keyboard events (debouncing, etc.)
 * @retval None
 */
void Keyboard_Process(void)
{
  /* Check if any key state has changed and needs to be reported */
  /* TODO: Implement non-blocking debouncing algorithm */
  
  /* Send HID report if needed */
  Keyboard_SendReport();
}

/**
 * @brief Send HID keyboard report over USB
 * @retval None
 */
void Keyboard_SendReport(void)
{
  /* TODO: Send HID report via USB */
}

/**
 * @brief GPIO EXTI callback - called when a key pin changes state
 * @param GPIO_Pin: Pin that triggered the interrupt
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Find which key corresponds to this pin */
  for (int i = 0; i < MAX_KEYS; i++) {
    if (keys[i].pin == GPIO_Pin) {
      /* Update key state based on GPIO input */
      keyState[i] = HAL_GPIO_ReadPin(keys[i].port, keys[i].pin) == GPIO_PIN_RESET ? 1 : 0;
      break;
    }
  }
}
