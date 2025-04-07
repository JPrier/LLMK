/**
 * @file usb_device.h
 * @brief USB Device header file
 */

#ifndef __USB_DEVICE_H
#define __USB_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Exported defines ----------------------------------------------------------*/
#define USB_HID_CONFIG_DESC_SIZ       34
#define USB_DESC_TYPE_CONFIGURATION   0x02
#define HID_DESCRIPTOR_TYPE           0x21
#define HID_KEYBOARD_REPORT_DESC_SIZE 63
#define HID_EPIN_ADDR                 0x81
#define HID_EPIN_SIZE                 0x08
#define HID_FS_BINTERVAL              0x0A
#define DEVICE_FS                     0

/* Exported functions prototypes ---------------------------------------------*/
void MX_USB_DEVICE_Init(void);
uint8_t USBD_HID_SendReport(uint8_t *report, uint16_t len);

/* External variables --------------------------------------------------------*/
extern USBD_HandleTypeDef hUsbDeviceFS;

#ifdef __cplusplus
}
#endif

#endif /* __USB_DEVICE_H */
