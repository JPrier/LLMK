/**
 * @file usbd_hid.h
 * @brief USB HID header file placeholder for CI build
 */

#ifndef __USBD_HID_H
#define __USBD_HID_H

#ifdef __cplusplus
extern "C" {
#endif

/* Include standard headers */
#include <stdint.h>

/* Function prototypes */
void USBD_HID_SendReport(void* pdev, uint8_t* report, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif /* __USBD_HID_H */
