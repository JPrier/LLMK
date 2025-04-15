/**
******************************************************************************
* @file    usbd_desc.h
* @brief   USB Device descriptor header for LLMK HID Keyboard project.
******************************************************************************
*/

#ifndef __USBD_DESC_H
#define __USBD_DESC_H

#ifdef __cplusplus
	extern "C" {
#endif

#include "usbd_def.h"

/*----------------------------------------------------------------------------
Define string descriptor indexes
*----------------------------------------------------------------------------*/
#define USBD_IDX_MFC_STR            0x01U
#define USBD_IDX_PRODUCT_STR        0x02U
#define USBD_IDX_SERIAL_STR         0x03U
#define USBD_IDX_CONFIG_STR         0x04U
#define USBD_IDX_ITF_STR            0x05U

/*----------------------------------------------------------------------------
Exported functions
*----------------------------------------------------------------------------*/
uint8_t* USBD_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t* length);
uint8_t* USBD_LangIDStrDescriptor(USBD_SpeedTypeDef speed, uint16_t* length);
uint8_t* USBD_ManufacturerStrDescriptor(USBD_SpeedTypeDef speed, uint16_t* length);
uint8_t* USBD_ProductStrDescriptor(USBD_SpeedTypeDef speed, uint16_t* length);
uint8_t* USBD_SerialStrDescriptor(USBD_SpeedTypeDef speed, uint16_t* length);
uint8_t* USBD_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t* length);
uint8_t* USBD_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t* length);
#if (USBD_LPM_ENABLED == 1) || (USBD_CLASS_BOS_ENABLED == 1)
	uint8_t* USBD_BOSDesc(USBD_SpeedTypeDef speed, uint16_t* length);
#endif

/*----------------------------------------------------------------------------
Exported USB Descriptor structure for the HID class.
This structure will be passed to USBD_Init.
*----------------------------------------------------------------------------*/
extern USBD_DescriptorsTypeDef HID_Desc;

#ifdef __cplusplus
}
#endif

#endif /* __USBD_DESC_H */
