/**
 * @file usb_device.c
 * @brief USB Device implementation for HID keyboard
 */

#include "../Inc/usb_device.h"
#include "../USB/Device/usbd_hid.h"

/* Private variables ---------------------------------------------------------*/
static USBD_HandleTypeDef hUsbDeviceFS;

/* USB HID device Configuration Descriptor */
static uint8_t USBD_HID_CfgDesc[USB_HID_CONFIG_DESC_SIZ] = {
  0x09,                          /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION,   /* bDescriptorType: Configuration */
  USB_HID_CONFIG_DESC_SIZ,       /* wTotalLength: Bytes returned */
  0x00,
  0x01,                          /* bNumInterfaces: 1 interface */
  0x01,                          /* bConfigurationValue: Configuration value */
  0x00,                          /* iConfiguration: Index of string descriptor describing the configuration */
  0xC0,                          /* bmAttributes: Bus powered and Support Remote Wake-up */
  0x32,                          /* MaxPower 100 mA: this current is used for detecting Vbus */
  
  /************** Descriptor of Keyboard interface ****************/
  0x09,                          /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE,       /* bDescriptorType: Interface descriptor type */
  0x00,                          /* bInterfaceNumber: Number of Interface */
  0x00,                          /* bAlternateSetting: Alternate setting */
  0x01,                          /* bNumEndpoints */
  0x03,                          /* bInterfaceClass: HID */
  0x01,                          /* bInterfaceSubClass: 1=BOOT, 0=no boot */
  0x01,                          /* nInterfaceProtocol: 0=none, 1=keyboard, 2=mouse */
  0x00,                          /* iInterface: Index of string descriptor */
  
  /******************** Descriptor of Keyboard HID ********************/
  0x09,                          /* bLength: HID Descriptor size */
  HID_DESCRIPTOR_TYPE,           /* bDescriptorType: HID */
  0x11,                          /* bcdHID: HID Class Spec release number */
  0x01,
  0x00,                          /* bCountryCode: Hardware target country */
  0x01,                          /* bNumDescriptors: Number of HID class descriptors to follow */
  0x22,                          /* bDescriptorType */
  HID_KEYBOARD_REPORT_DESC_SIZE, /* wItemLength: Total length of Report descriptor */
  0x00,
  
  /******************** Descriptor of Keyboard endpoint ********************/
  0x07,                          /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,        /* bDescriptorType: */
  HID_EPIN_ADDR,                 /* bEndpointAddress: Endpoint Address (IN) */
  0x03,                          /* bmAttributes: Interrupt endpoint */
  HID_EPIN_SIZE,                 /* wMaxPacketSize: 8 Byte max */
  0x00,
  HID_FS_BINTERVAL,              /* bInterval: Polling Interval */
};

/* USB HID device Report Descriptor for Keyboard */
static uint8_t USBD_HID_ReportDesc[HID_KEYBOARD_REPORT_DESC_SIZE] = {
  0x05, 0x01,                    /* USAGE_PAGE (Generic Desktop) */
  0x09, 0x06,                    /* USAGE (Keyboard) */
  0xa1, 0x01,                    /* COLLECTION (Application) */
  0x05, 0x07,                    /* USAGE_PAGE (Keyboard) */
  
  /* Modifier byte */
  0x19, 0xe0,                    /* USAGE_MINIMUM (Keyboard LeftControl) */
  0x29, 0xe7,                    /* USAGE_MAXIMUM (Keyboard Right GUI) */
  0x15, 0x00,                    /* LOGICAL_MINIMUM (0) */
  0x25, 0x01,                    /* LOGICAL_MAXIMUM (1) */
  0x75, 0x01,                    /* REPORT_SIZE (1) */
  0x95, 0x08,                    /* REPORT_COUNT (8) */
  0x81, 0x02,                    /* INPUT (Data,Var,Abs) */
  
  /* Reserved byte */
  0x95, 0x01,                    /* REPORT_COUNT (1) */
  0x75, 0x08,                    /* REPORT_SIZE (8) */
  0x81, 0x01,                    /* INPUT (Cnst,Var,Abs) */
  
  /* LED report */
  0x95, 0x05,                    /* REPORT_COUNT (5) */
  0x75, 0x01,                    /* REPORT_SIZE (1) */
  0x05, 0x08,                    /* USAGE_PAGE (LEDs) */
  0x19, 0x01,                    /* USAGE_MINIMUM (Num Lock) */
  0x29, 0x05,                    /* USAGE_MAXIMUM (Kana) */
  0x91, 0x02,                    /* OUTPUT (Data,Var,Abs) */
  
  /* LED report padding */
  0x95, 0x01,                    /* REPORT_COUNT (1) */
  0x75, 0x03,                    /* REPORT_SIZE (3) */
  0x91, 0x01,                    /* OUTPUT (Cnst,Var,Abs) */
  
  /* Key array (6 keys) */
  0x95, 0x06,                    /* REPORT_COUNT (6) */
  0x75, 0x08,                    /* REPORT_SIZE (8) */
  0x15, 0x00,                    /* LOGICAL_MINIMUM (0) */
  0x25, 0x65,                    /* LOGICAL_MAXIMUM (101) */
  0x05, 0x07,                    /* USAGE_PAGE (Keyboard) */
  0x19, 0x00,                    /* USAGE_MINIMUM (Reserved (no event indicated)) */
  0x29, 0x65,                    /* USAGE_MAXIMUM (Keyboard Application) */
  0x81, 0x00,                    /* INPUT (Data,Ary,Abs) */
  
  0xc0                           /* END_COLLECTION */
};

/* USB HID device Configuration */
USBD_HID_HandleTypeDef hhid;

/* USB Device Core handle declaration */
USBD_HandleTypeDef hUsbDeviceFS;

/**
  * @brief  Initialize the USB device
  * @retval None
  */
void MX_USB_DEVICE_Init(void)
{
  /* Init Device Library */
  USBD_Init(&hUsbDeviceFS, &HID_Desc, DEVICE_FS);
  
  /* Add Supported Class */
  USBD_RegisterClass(&hUsbDeviceFS, &USBD_HID);
  
  /* Add HID Interface Class */
  USBD_HID_RegisterInterface(&hUsbDeviceFS, &USBD_HID_fops);
  
  /* Start Device Process */
  USBD_Start(&hUsbDeviceFS);
}

/**
  * @brief  Send HID Report
  * @param  report: Pointer to report
  * @param  len: Report length
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
uint8_t USBD_HID_SendReport(uint8_t *report, uint16_t len)
{
  return USBD_HID_SendReport(&hUsbDeviceFS, report, len);
}
