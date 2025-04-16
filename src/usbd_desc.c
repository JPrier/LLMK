/**
  ******************************************************************************
  * @file    usbd_desc.c
  * @brief   USB Device Descriptors for LLMK HID Keyboard.
  ******************************************************************************
  * @attention
  *
  * This file implements the descriptor retrieval functions for the USB Device
  * Library. Adjust the VID, PID, string literals, and other values as needed.
  *
  ******************************************************************************
  */

  /* Includes ------------------------------------------------------------------*/
#include "usbd_desc.h"
#include "usbd_def.h"
#include <string.h>

/*----------------------------------------------------------------------------
  If USB_LEN_DEV_DESC is already defined by the middleware, do not redefine.
 *----------------------------------------------------------------------------*/
#ifndef USB_LEN_DEV_DESC
#define USB_LEN_DEV_DESC       18U   // 0x12U
#endif

 /*----------------------------------------------------------------------------
   Define device descriptor parameters.
   These values may be adjusted for your hardware.
  *----------------------------------------------------------------------------*/
#ifndef USBD_VID
#define USBD_VID                      0x1234U
#endif

#ifndef USBD_PID
#define USBD_PID                      0x5678U
#endif

#ifndef USBD_LANGID_STRING
#define USBD_LANGID_STRING            0x0409U  /* English (United States) */
#endif

#ifndef USBD_BCD_DEVICE
#define USBD_BCD_DEVICE               0x0200U  /* Device release number 2.00 */
#endif

#ifndef USBD_MANUFACTURER_STRING
#define USBD_MANUFACTURER_STRING      "LLMK"
#endif

#ifndef USBD_PRODUCT_STRING
#define USBD_PRODUCT_STRING           "LLMK HID Keyboard"
#endif

#ifndef USBD_CONFIGURATION_STRING
#define USBD_CONFIGURATION_STRING     "LLMK Config"
#endif

#ifndef USBD_INTERFACE_STRING
#define USBD_INTERFACE_STRING         "LLMK HID Interface"
#endif

  /*----------------------------------------------------------------------------
    Device Descriptor: 18 bytes.
   *----------------------------------------------------------------------------*/
static uint8_t USBD_DeviceDesc[USB_LEN_DEV_DESC] = {
  0x12,                       /* bLength */
  USB_DESC_TYPE_DEVICE,       /* bDescriptorType */
  LOBYTE(0x0200), HIBYTE(0x0200), /* bcdUSB (2.00) */
  0x00,                       /* bDeviceClass (defined at interface level) */
  0x00,                       /* bDeviceSubClass */
  0x00,                       /* bDeviceProtocol */
  USB_MAX_EP0_SIZE,           /* bMaxPacketSize0 */
  LOBYTE(USBD_VID), HIBYTE(USBD_VID),   /* idVendor */
  LOBYTE(USBD_PID), HIBYTE(USBD_PID),   /* idProduct */
  LOBYTE(USBD_BCD_DEVICE), HIBYTE(USBD_BCD_DEVICE), /* bcdDevice */
  USBD_IDX_MFC_STR,           /* iManufacturer */
  USBD_IDX_PRODUCT_STR,       /* iProduct */
  USBD_IDX_SERIAL_STR,        /* iSerialNumber */
  0x01                        /* bNumConfigurations */
};

/*----------------------------------------------------------------------------
  LangID Descriptor.
 *----------------------------------------------------------------------------*/
static uint8_t USBD_LangIDDesc[] = {
  0x04,                       /* bLength */
  USB_DESC_TYPE_STRING,       /* bDescriptorType */
  LOBYTE(USBD_LANGID_STRING),
  HIBYTE(USBD_LANGID_STRING)
};

/*----------------------------------------------------------------------------
  A static buffer for converting ASCII strings into UTF-16LE descriptors.
 *----------------------------------------------------------------------------*/
static uint8_t USBD_StrDesc[USBD_MAX_STR_DESC_SIZ];

/*----------------------------------------------------------------------------
  Helper function to convert an ASCII string into a USB string descriptor.
 *----------------------------------------------------------------------------*/
static uint8_t* USBD_GetString(const char* desc, uint8_t* pbuf)
{
    uint32_t len = 0;
    while (desc[len] != '\0') { len++; }

    pbuf[0] = (uint8_t)(len * 2 + 2);   /* Descriptor length */
    pbuf[1] = USB_DESC_TYPE_STRING;
    for (uint32_t idx = 0; idx < len; idx++) {
        pbuf[2 * idx + 2] = desc[idx];
        pbuf[2 * idx + 3] = 0;
    }
    return pbuf;
}

/*----------------------------------------------------------------------------
  Descriptor retrieval functions.
  Note: The speed parameter is not used in this simple template.
 *----------------------------------------------------------------------------*/
uint8_t* USBD_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t* length)
{
    (void)speed;  /* Unused parameter */
    *length = sizeof(USBD_DeviceDesc);
    return USBD_DeviceDesc;
}

uint8_t* USBD_LangIDStrDescriptor(USBD_SpeedTypeDef speed, uint16_t* length)
{
    (void)speed;
    *length = sizeof(USBD_LangIDDesc);
    return USBD_LangIDDesc;
}

uint8_t* USBD_ManufacturerStrDescriptor(USBD_SpeedTypeDef speed, uint16_t* length)
{
    (void)speed;
    (void)length; /* Optionally update length */
    return USBD_GetString(USBD_MANUFACTURER_STRING, USBD_StrDesc);
}

uint8_t* USBD_ProductStrDescriptor(USBD_SpeedTypeDef speed, uint16_t* length)
{
    (void)speed;
    (void)length;
    return USBD_GetString(USBD_PRODUCT_STRING, USBD_StrDesc);
}

uint8_t* USBD_SerialStrDescriptor(USBD_SpeedTypeDef speed, uint16_t* length)
{
    (void)speed;
    (void)length;
    /* For demonstration, a fixed serial number is used.
       In production, you may generate the serial from hardware UID. */
    return USBD_GetString("00000001", USBD_StrDesc);
}

uint8_t* USBD_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t* length)
{
    (void)speed;
    (void)length;
    return USBD_GetString(USBD_CONFIGURATION_STRING, USBD_StrDesc);
}

uint8_t* USBD_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t* length)
{
    (void)speed;
    (void)length;
    return USBD_GetString(USBD_INTERFACE_STRING, USBD_StrDesc);
}

#if (USBD_LPM_ENABLED == 1) || (USBD_CLASS_BOS_ENABLED == 1)
uint8_t* USBD_BOSDesc(USBD_SpeedTypeDef speed, uint16_t* length)
{
    (void)speed;
    static uint8_t USBD_BOSDesc[USB_SIZ_BOS_DESC] = {
      USB_SIZ_BOS_DESC,         /* bLength */
      USB_DESC_TYPE_BOS,        /* bDescriptorType */
      USB_SIZ_BOS_DESC, 0x00,     /* wTotalLength */
      0x01                     /* bNumDeviceCaps */
      /* Additional fields could be added here */
    };
    *length = USB_SIZ_BOS_DESC;
    return USBD_BOSDesc;
}
#endif /* USBD_LPM_ENABLED || USBD_CLASS_BOS_ENABLED */

/*----------------------------------------------------------------------------
  Export the descriptor structure.
  This structure is used during USB initialization.
 *----------------------------------------------------------------------------*/
USBD_DescriptorsTypeDef HID_Desc = {
  USBD_DeviceDescriptor,
  USBD_LangIDStrDescriptor,
  USBD_ManufacturerStrDescriptor,
  USBD_ProductStrDescriptor,
  USBD_SerialStrDescriptor,
  USBD_ConfigStrDescriptor,
  USBD_InterfaceStrDescriptor,
#if (USBD_LPM_ENABLED == 1) || (USBD_CLASS_BOS_ENABLED == 1)
  USBD_BOSDesc,
#endif
};
