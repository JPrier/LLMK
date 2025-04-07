/**
 * @file keyboard.c
 * @brief Keyboard handling implementation
 */

#include "../Inc/keyboard.h"
#include "../Inc/usb_device.h"
#include <string.h>

/* Private defines -----------------------------------------------------------*/
#define MAX_KEYS 87  /* Tenkeyless keyboard has 87 keys */

/* USB HID Keyboard scan codes as per USB spec 1.11 */
#define KEY_NONE        0x00
#define KEY_A           0x04
#define KEY_B           0x05
#define KEY_C           0x06
#define KEY_D           0x07
#define KEY_E           0x08
#define KEY_F           0x09
#define KEY_G           0x0A
#define KEY_H           0x0B
#define KEY_I           0x0C
#define KEY_J           0x0D
#define KEY_K           0x0E
#define KEY_L           0x0F
#define KEY_M           0x10
#define KEY_N           0x11
#define KEY_O           0x12
#define KEY_P           0x13
#define KEY_Q           0x14
#define KEY_R           0x15
#define KEY_S           0x16
#define KEY_T           0x17
#define KEY_U           0x18
#define KEY_V           0x19
#define KEY_W           0x1A
#define KEY_X           0x1B
#define KEY_Y           0x1C
#define KEY_Z           0x1D
#define KEY_1           0x1E
#define KEY_2           0x1F
#define KEY_3           0x20
#define KEY_4           0x21
#define KEY_5           0x22
#define KEY_6           0x23
#define KEY_7           0x24
#define KEY_8           0x25
#define KEY_9           0x26
#define KEY_0           0x27
#define KEY_ENTER       0x28
#define KEY_ESCAPE      0x29
#define KEY_BACKSPACE   0x2A
#define KEY_TAB         0x2B
#define KEY_SPACE       0x2C
#define KEY_MINUS       0x2D
#define KEY_EQUAL       0x2E
#define KEY_LEFTBRACE   0x2F
#define KEY_RIGHTBRACE  0x30
#define KEY_BACKSLASH   0x31
#define KEY_SEMICOLON   0x33
#define KEY_APOSTROPHE  0x34
#define KEY_GRAVE       0x35
#define KEY_COMMA       0x36
#define KEY_DOT         0x37
#define KEY_SLASH       0x38
#define KEY_CAPSLOCK    0x39
#define KEY_F1          0x3A
#define KEY_F2          0x3B
#define KEY_F3          0x3C
#define KEY_F4          0x3D
#define KEY_F5          0x3E
#define KEY_F6          0x3F
#define KEY_F7          0x40
#define KEY_F8          0x41
#define KEY_F9          0x42
#define KEY_F10         0x43
#define KEY_F11         0x44
#define KEY_F12         0x45

/* Private variables ---------------------------------------------------------*/
static Key_TypeDef keys[MAX_KEYS];
static uint8_t keyState[MAX_KEYS];
static uint8_t keyReport[8] = {0}; /* Standard HID keyboard report */

/* Private function prototypes -----------------------------------------------*/
static void USB_Send_Keypress(uint8_t key);

/**
 * @brief Initialize the keyboard handling
 * @retval None
 */
void Keyboard_Init(void)
{
  /* Initialize key mapping and GPIO interrupts */
  
  /* Map GPIO pins to keyboard keys (arbitrary mapping) */
  /* GPIOA pins */
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
  
  /* GPIOB pins */
  keys[8].keycode = KEY_I;
  keys[8].port = GPIOB;
  keys[8].pin = GPIO_PIN_0;
  
  keys[9].keycode = KEY_J;
  keys[9].port = GPIOB;
  keys[9].pin = GPIO_PIN_1;
  
  keys[10].keycode = KEY_K;
  keys[10].port = GPIOB;
  keys[10].pin = GPIO_PIN_2;
  
  keys[11].keycode = KEY_L;
  keys[11].port = GPIOB;
  keys[11].pin = GPIO_PIN_3;
  
  keys[12].keycode = KEY_M;
  keys[12].port = GPIOB;
  keys[12].pin = GPIO_PIN_4;
  
  keys[13].keycode = KEY_N;
  keys[13].port = GPIOB;
  keys[13].pin = GPIO_PIN_5;
  
  keys[14].keycode = KEY_O;
  keys[14].port = GPIOB;
  keys[14].pin = GPIO_PIN_6;
  
  keys[15].keycode = KEY_P;
  keys[15].port = GPIOB;
  keys[15].pin = GPIO_PIN_7;
  
  /* GPIOC pins */
  keys[16].keycode = KEY_Q;
  keys[16].port = GPIOC;
  keys[16].pin = GPIO_PIN_0;
  
  keys[17].keycode = KEY_R;
  keys[17].port = GPIOC;
  keys[17].pin = GPIO_PIN_1;
  
  keys[18].keycode = KEY_S;
  keys[18].port = GPIOC;
  keys[18].pin = GPIO_PIN_2;
  
  keys[19].keycode = KEY_T;
  keys[19].port = GPIOC;
  keys[19].pin = GPIO_PIN_3;
  
  keys[20].keycode = KEY_U;
  keys[20].port = GPIOC;
  keys[20].pin = GPIO_PIN_4;
  
  keys[21].keycode = KEY_V;
  keys[21].port = GPIOC;
  keys[21].pin = GPIO_PIN_5;
  
  keys[22].keycode = KEY_W;
  keys[22].port = GPIOC;
  keys[22].pin = GPIO_PIN_6;
  
  keys[23].keycode = KEY_X;
  keys[23].port = GPIOC;
  keys[23].pin = GPIO_PIN_7;
  
  /* GPIOD pins */
  keys[24].keycode = KEY_Y;
  keys[24].port = GPIOD;
  keys[24].pin = GPIO_PIN_0;
  
  keys[25].keycode = KEY_Z;
  keys[25].port = GPIOD;
  keys[25].pin = GPIO_PIN_1;
  
  keys[26].keycode = KEY_1;
  keys[26].port = GPIOD;
  keys[26].pin = GPIO_PIN_2;
  
  /* Configure GPIO pins for input with pull-up and interrupt on falling edge */
  /* This would be done in the actual implementation */
  
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
  /* In a real implementation, this would include debouncing logic */
  
  /* For simplicity, we'll just check if any keys are pressed and send the report */
  for (int i = 0; i < MAX_KEYS; i++) {
    if (keyState[i]) {
      USB_Send_Keypress(keys[i].keycode);
      /* Reset key state after sending */
      keyState[i] = 0;
      break; /* Only send one key at a time for simplicity */
    }
  }
}

/**
 * @brief Send HID keyboard report over USB
 * @param key: USB HID keycode to send
 * @retval None
 */
static void USB_Send_Keypress(uint8_t key)
{
  /* Standard HID keyboard report structure:
   * Byte 0: Modifier keys (CTRL, SHIFT, etc.)
   * Byte 1: Reserved (set to 0)
   * Bytes 2-7: Key codes (up to 6 keys can be pressed simultaneously)
   */
  
  /* Clear the report */
  memset(keyReport, 0, sizeof(keyReport));
  
  /* Set the key in the report */
  keyReport[2] = key;
  
  /* Send the report via USB */
  USBD_HID_SendReport(keyReport, sizeof(keyReport));
  
  /* Send empty report to indicate key release */
  memset(keyReport, 0, sizeof(keyReport));
  USBD_HID_SendReport(keyReport, sizeof(keyReport));
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
      /* Update key state based on GPIO input - active low (pressed when pin is low) */
      keyState[i] = (HAL_GPIO_ReadPin(keys[i].port, keys[i].pin) == GPIO_PIN_RESET) ? 1 : 0;
      break;
    }
  }
}
