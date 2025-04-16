/**
  ******************************************************************************
  * @file    usbd_conf.h
  * @brief   USB Device library configuration header for LLMK HID Keyboard project.
  ******************************************************************************
  * @attention
  *
  * This file has been customized for the LLMK project based on STM32CubeH7.
  * Adjust the definitions as needed for your board and application.
  *
  ******************************************************************************
  */

  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_CONF_H
#define __USBD_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

	/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** USB Device Library Configurations ***************************************/
#define USBD_MAX_NUM_INTERFACES         1U
#define USBD_MAX_NUM_CONFIGURATION      1U
#define USBD_MAX_STR_DESC_SIZ           0x100U
#define USBD_SELF_POWERED               1U
#define USBD_DEBUG_LEVEL                2U

/* Memory management macros (you must implement these in usbd_conf.c) */
#define USBD_malloc         (void *)USBD_static_malloc
#define USBD_free           USBD_static_free
#define USBD_memset         memset
#define USBD_memcpy         memcpy
#define USBD_Delay          HAL_Delay

/* DEBUG macros */
#if (USBD_DEBUG_LEVEL > 0U)
#define  USBD_UsrLog(...)   do { printf(__VA_ARGS__); printf("\r\n"); } while(0)
#else
#define USBD_UsrLog(...)   do {} while(0)
#endif

#if (USBD_DEBUG_LEVEL > 1U)
#define  USBD_ErrLog(...)   do { printf("ERROR: "); printf(__VA_ARGS__); printf("\r\n"); } while(0)
#else
#define USBD_ErrLog(...)   do {} while(0)
#endif

#if (USBD_DEBUG_LEVEL > 2U)
#define  USBD_DbgLog(...)   do { printf("DEBUG: "); printf(__VA_ARGS__); printf("\r\n"); } while(0)
#else
#define USBD_DbgLog(...)   do {} while(0)
#endif

/* HID Class Configuration ***************************************************/
#define HID_KEYBOARD_REPORT_DESC_SIZE   63U  /* Size in bytes of your HID keyboard report descriptor */
#define USB_HID_CONFIG_DESC_SIZ          34U  /* Size of the HID configuration descriptor */

/* HID Endpoint Configuration */
//#define HID_EPIN_ADDR                    0x81U  /* Endpoint address (IN) */
//#define HID_EPIN_SIZE                    8U     /* Maximum packet size for HID IN endpoint */
//#define HID_FS_BINTERVAL                 10U    /* Polling interval in frames */

/* Exported functions for memory management (implement in a corresponding source file) */
	void* USBD_static_malloc(uint32_t size);
	void USBD_static_free(void* p);

#ifdef __cplusplus
}
#endif

#endif /* __USBD_CONF_H */

