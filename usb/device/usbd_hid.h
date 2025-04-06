/**
 * @file usbd_hid.h
 * @brief USB Device HID Class header file
 */

#ifndef __USBD_HID_H
#define __USBD_HID_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint8_t  *Report_Desc;
  uint16_t Report_Desc_Size;
  uint16_t Report_Size;
} USBD_HID_HandleTypeDef;

typedef struct
{
  uint8_t  (*Init)             (void);
  uint8_t  (*DeInit)           (void);
  uint8_t  (*OutEvent)         (uint8_t event_idx, uint8_t state);
} USBD_HID_ItfTypeDef;

typedef struct
{
  uint8_t  (*Init)             (void);
  uint8_t  (*DeInit)           (void);
  uint8_t  (*Control)          (uint8_t cmd, uint8_t* pbuf, uint16_t length);
  uint8_t  (*Receive)          (uint8_t* pbuf, uint32_t *Len);
  uint8_t  (*TransmitCplt)     (uint8_t* pbuf, uint32_t *Len, uint8_t epnum);
} USBD_ClassTypeDef;

typedef struct
{
  uint8_t  (*GetDeviceDescriptor)           (uint8_t speed, uint16_t *length);
  uint8_t  (*GetLangIDStrDescriptor)        (uint8_t speed, uint16_t *length);
  uint8_t  (*GetManufacturerStrDescriptor)  (uint8_t speed, uint16_t *length);
  uint8_t  (*GetProductStrDescriptor)       (uint8_t speed, uint16_t *length);
  uint8_t  (*GetSerialStrDescriptor)        (uint8_t speed, uint16_t *length);
  uint8_t  (*GetConfigurationStrDescriptor) (uint8_t speed, uint16_t *length);
  uint8_t  (*GetInterfaceStrDescriptor)     (uint8_t speed, uint16_t *length);
} USBD_DescriptorsTypeDef;

/* Exported constants --------------------------------------------------------*/
#define HID_EPIN_ADDR                 0x81U
#define HID_EPIN_SIZE                 0x04U

#define USB_HID_CONFIG_DESC_SIZ       34U
#define USB_HID_DESC_SIZ              9U
#define HID_KEYBOARD_REPORT_DESC_SIZE 63U

#define HID_DESCRIPTOR_TYPE           0x21U
#define HID_REPORT_DESC               0x22U

#define HID_HS_BINTERVAL              0x07U
#define HID_FS_BINTERVAL              0x0AU
#define HID_POLLING_INTERVAL          0x0AU

#define HID_REQ_SET_PROTOCOL          0x0BU
#define HID_REQ_GET_PROTOCOL          0x03U

#define HID_REQ_SET_IDLE              0x0AU
#define HID_REQ_GET_IDLE              0x02U

#define HID_REQ_SET_REPORT            0x09U
#define HID_REQ_GET_REPORT            0x01U

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
uint8_t USBD_HID_SendReport(uint8_t *report, uint16_t len);
uint8_t USBD_HID_GetPollingInterval(USBD_HandleTypeDef *pdev);

/* External variables --------------------------------------------------------*/
extern USBD_ClassTypeDef  USBD_HID;
extern USBD_HID_ItfTypeDef USBD_HID_fops;
extern USBD_DescriptorsTypeDef HID_Desc;

#ifdef __cplusplus
}
#endif

#endif /* __USBD_HID_H */
