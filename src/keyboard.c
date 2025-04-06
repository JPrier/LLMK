/**
 * @file keyboard.c
 * @brief Keyboard handling implementation
 */

#include "keyboard.h"
#include "usb_device.h"

/* Private defines -----------------------------------------------------------*/
#define MAX_KEYS 26  /* We'll map A-Z keys */

/* USB HID Keyboard scan codes as per USB spec */
#define KEY_A 0x04
#define KEY_B 0x05
#define KEY_C 0x06
#define KEY_D 0x07
#define KEY_E 0x08
#define KEY_F 0x09
#define KEY_G 0x0A
#define KEY_H 0x0B
#define KEY_I 0x0C
#define KEY_J 0x0D
#define KEY_K 0x0E
#define KEY_L 0x0F
#define KEY_M 0x10
#define KEY_N 0x11
#define KEY_O 0x12
#define KEY_P 0x13
#define KEY_Q 0x14
#define KEY_R 0x15
#define KEY_S 0x16
#define KEY_T 0x17
#define KEY_U 0x18
#define KEY_V 0x19
#define KEY_W 0x1A
#define KEY_X 0x1B
#define KEY_Y 0x1C
#define KEY_Z 0x1D

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
  /* Initialize key mapping for GPIO pins A0-A9, B0-B9, C0-C5 to A-Z keys */
  
  /* GPIO Port A pins */
  keys[0].keycode = KEY_A;
  keys[0].port = GPIOA;
  keys[0].pin = GPIO_PIN_0;
  
  keys[1].keycode = KEY_B;
  keys[1].port = GPIOA;
  keys[1].pin = GPIO_PIN_1;
  
  keys[2].keycode = KEY_C;
  keys[2].port = GPIOA;
  keys[2].pin = GPIO_PIN_2;
  
  keys[3].keycode = KEY_D;
  keys[3].port = GPIOA;
  keys[3].pin = GPIO_PIN_3;
  
  keys[4].keycode = KEY_E;
  keys[4].port = GPIOA;
  keys[4].pin = GPIO_PIN_4;
  
  keys[5].keycode = KEY_F;
  keys[5].port = GPIOA;
  keys[5].pin = GPIO_PIN_5;
  
  keys[6].keycode = KEY_G;
  keys[6].port = GPIOA;
  keys[6].pin = GPIO_PIN_6;
  
  keys[7].keycode = KEY_H;
  keys[7].port = GPIOA;
  keys[7].pin = GPIO_PIN_7;
  
  keys[8].keycode = KEY_I;
  keys[8].port = GPIOA;
  keys[8].pin = GPIO_PIN_8;
  
  keys[9].keycode = KEY_J;
  keys[9].port = GPIOA;
  keys[9].pin = GPIO_PIN_9;
  
  /* GPIO Port B pins */
  keys[10].keycode = KEY_K;
  keys[10].port = GPIOB;
  keys[10].pin = GPIO_PIN_0;
  
  keys[11].keycode = KEY_L;
  keys[11].port = GPIOB;
  keys[11].pin = GPIO_PIN_1;
  
  keys[12].keycode = KEY_M;
  keys[12].port = GPIOB;
  keys[12].pin = GPIO_PIN_2;
  
  keys[13].keycode = KEY_N;
  keys[13].port = GPIOB;
  keys[13].pin = GPIO_PIN_3;
  
  keys[14].keycode = KEY_O;
  keys[14].port = GPIOB;
  keys[14].pin = GPIO_PIN_4;
  
  keys[15].keycode = KEY_P;
  keys[15].port = GPIOB;
  keys[15].pin = GPIO_PIN_5;
  
  keys[16].keycode = KEY_Q;
  keys[16].port = GPIOB;
  keys[16].pin = GPIO_PIN_6;
  
  keys[17].keycode = KEY_R;
  keys[17].port = GPIOB;
  keys[17].pin = GPIO_PIN_7;
  
  keys[18].keycode = KEY_S;
  keys[18].port = GPIOB;
  keys[18].pin = GPIO_PIN_8;
  
  keys[19].keycode = KEY_T;
  keys[19].port = GPIOB;
  keys[19].pin = GPIO_PIN_9;
  
  /* GPIO Port C pins */
  keys[20].keycode = KEY_U;
  keys[20].port = GPIOC;
  keys[20].pin = GPIO_PIN_0;
  
  keys[21].keycode = KEY_V;
  keys[21].port = GPIOC;
  keys[21].pin = GPIO_PIN_1;
  
  keys[22].keycode = KEY_W;
  keys[22].port = GPIOC;
  keys[22].pin = GPIO_PIN_2;
  
  keys[23].keycode = KEY_X;
  keys[23].port = GPIOC;
  keys[23].pin = GPIO_PIN_3;
  
  keys[24].keycode = KEY_Y;
  keys[24].port = GPIOC;
  keys[24].pin = GPIO_PIN_4;
  
  keys[25].keycode = KEY_Z;
  keys[25].port = GPIOC;
  keys[25].pin = GPIO_PIN_5;
  
  /* Clear all key states */
  for (int i = 0; i < MAX_KEYS; i++) {
    keyState[i] = 0;
  }
  
  /* Clear the HID report */
  for (int i = 0; i < 8; i++) {
    keyReport[i] = 0;
  }
}

/**
 * @brief Process keyboard events (debouncing, etc.)
 * @retval None
 */
void Keyboard_Process(void)
{
  uint8_t reportIndex = 2; /* Start at index 2 (after modifier and reserved bytes) */
  uint8_t reportChanged = 0;
  
  /* Clear the key report (except modifiers) */
  for (int i = 2; i < 8; i++) {
    keyReport[i] = 0;
  }
  
  /* Add pressed keys to the report */
  for (int i = 0; i < MAX_KEYS; i++) {
    if (keyState[i]) {
      if (reportIndex < 8) { /* Maximum 6 keys in the report */
        keyReport[reportIndex++] = keys[i].keycode;
        reportChanged = 1;
      }
    }
  }
  
  /* Send the report if any keys are pressed or released */
  if (reportChanged) {
    Keyboard_SendReport();
  }
}

/**
 * @brief Send HID keyboard report over USB
 * @retval None
 */
void Keyboard_SendReport(void)
{
  USBD_HID_SendReport(keyReport, 8);
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
      GPIO_PinState pinState = HAL_GPIO_ReadPin(keys[i].port, keys[i].pin);
      keyState[i] = (pinState == GPIO_PIN_RESET) ? 1 : 0;
      break;
    }
  }
}
