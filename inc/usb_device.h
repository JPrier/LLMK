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
#include "usbd_def.h"
#include "usbd_hid.h"

/* Exported functions prototypes ---------------------------------------------*/
void MX_USB_DEVICE_Init(void);
uint8_t USB_Send_Report(uint8_t* report, uint16_t len);

/* Exported defines ----------------------------------------------------------*/
#define DEVICE_FS                     0

/* External variables --------------------------------------------------------*/
extern USBD_HandleTypeDef hUsbDeviceFS;

#ifdef __cplusplus
}
#endif

#endif /* __USB_DEVICE_H */
