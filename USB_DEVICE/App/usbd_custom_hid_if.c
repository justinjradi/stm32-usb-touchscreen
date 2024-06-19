/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_custom_hid_if.c
  * @version        : v1.0_Cube
  * @brief          : USB Device Custom HID interface file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_custom_hid_if.h"

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device.
  * @{
  */

/** @addtogroup USBD_CUSTOM_HID
  * @{
  */

/** @defgroup USBD_CUSTOM_HID_Private_TypesDefinitions USBD_CUSTOM_HID_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Defines USBD_CUSTOM_HID_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */

/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Macros USBD_CUSTOM_HID_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Variables USBD_CUSTOM_HID_Private_Variables
  * @brief Private variables.
  * @{
  */

/** Usb HID report descriptor. */
__ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
{
  /* USER CODE BEGIN 0 */
		0x05, 0x0d,                         // USAGE_PAGE (Digitizers)
		// Touch Input Report
		    0x09, 0x04,                         // USAGE (Touch Screen)
		    0xa1, 0x01,                         // COLLECTION (Application)
		    0x85, REPORTID_TOUCH,               //   REPORT_ID (Touch)
				// Contact 1
		    0x09, 0x22,                         //   USAGE (Finger)
		    0xa1, 0x02,                         //     COLLECTION (Logical)
		    0x09, 0x42,                         //       USAGE (Tip Switch)
		    0x15, 0x00,                         //       LOGICAL_MINIMUM (0)
		    0x25, 0x01,                         //       LOGICAL_MAXIMUM (1)
		    0x75, 0x01,                         //       REPORT_SIZE (1)
		    0x95, 0x01,                         //       REPORT_COUNT (1)
		    0x81, 0x02,                         //       INPUT (Data,Var,Abs)
		    0x95, 0x07,                         //       REPORT_COUNT (7)
		    0x81, 0x03,                         //       INPUT (Cnst,Ary,Abs)
		    0x75, 0x08,                         //       REPORT_SIZE (8)
		    0x09, 0x51,                         //       USAGE (Contact Identifier)
		    0x95, 0x01,                         //       REPORT_COUNT (1)
		    0x81, 0x02,                         //       INPUT (Data,Var,Abs)
		    0x05, 0x01,                         //       USAGE_PAGE (Generic Desk..
		    0x26, 0xff, 0x0f,                   //       LOGICAL_MAXIMUM (4095)
		    0x75, 0x10,                         //       REPORT_SIZE (16)
		    0x55, 0x0e,                         //       UNIT_EXPONENT (-2)
		    0x65, 0x13,                         //       UNIT(Inch,EngLinear)
		    0x09, 0x30,                         //       USAGE (X)
		    0x35, 0x00,                         //       PHYSICAL_MINIMUM (0)
		    0x46, 0xb5, 0x04,                   //       PHYSICAL_MAXIMUM (1205)
		    0x95, 0x01,                         //       REPORT_COUNT (1)
		    0x81, 0x02,                         //       INPUT (Data,Var,Abs)
		    0x46, 0x8a, 0x03,                   //       PHYSICAL_MAXIMUM (906)
		    0x09, 0x31,                         //       USAGE (Y)
		    0x81, 0x02,                         //       INPUT (Data,Var,Abs)
		    0xc0,                               //     END_COLLECTION
				// Contact 2
		    0x09, 0x22,                         //   USAGE (Finger)
		    0xa1, 0x02,                         //     COLLECTION (Logical)
		    0x09, 0x42,                         //       USAGE (Tip Switch)
		    0x15, 0x00,                         //       LOGICAL_MINIMUM (0)
		    0x25, 0x01,                         //       LOGICAL_MAXIMUM (1)
		    0x75, 0x01,                         //       REPORT_SIZE (1)
		    0x95, 0x01,                         //       REPORT_COUNT (1)
		    0x81, 0x02,                         //       INPUT (Data,Var,Abs)
		    0x95, 0x07,                         //       REPORT_COUNT (7)
		    0x81, 0x03,                         //       INPUT (Cnst,Ary,Abs)
		    0x75, 0x08,                         //       REPORT_SIZE (8)
		    0x09, 0x51,                         //       USAGE (Contact Identifier)
		    0x95, 0x01,                         //       REPORT_COUNT (1)
		    0x81, 0x02,                         //       INPUT (Data,Var,Abs)
		    0x05, 0x01,                         //       USAGE_PAGE (Generic Desk..
		    0x26, 0xff, 0x0f,                   //       LOGICAL_MAXIMUM (4095)
		    0x75, 0x10,                         //       REPORT_SIZE (16)
		    0x55, 0x0e,                         //       UNIT_EXPONENT (-2)
		    0x65, 0x13,                         //       UNIT(Inch,EngLinear)
		    0x09, 0x30,                         //       USAGE (X)
		    0x35, 0x00,                         //       PHYSICAL_MINIMUM (0)
		    0x46, 0xb5, 0x04,                   //       PHYSICAL_MAXIMUM (1205)
		    0x95, 0x01,                         //       REPORT_COUNT (1)
		    0x81, 0x02,                         //       INPUT (Data,Var,Abs)
		    0x46, 0x8a, 0x03,                   //       PHYSICAL_MAXIMUM (906)
		    0x09, 0x31,                         //       USAGE (Y)
		    0x81, 0x02,                         //       INPUT (Data,Var,Abs)
		    0xc0,                               //     END_COLLECTION
				// Scan Time
		    0x05, 0x0d,                         //   USAGE_PAGE (Digitizers)
				0x55, 0x0C,                         //     UNIT_EXPONENT (-4)
				0x66, 0x01, 0x10,                   //     UNIT (Seconds)
				0x47, 0xff, 0xff, 0x00, 0x00,       //       PHYSICAL_MAXIMUM (65535)
				0x27, 0xff, 0xff, 0x00, 0x00,       //   LOGICAL_MAXIMUM (65535)
				0x75, 0x10,                         //   REPORT_SIZE (16)
				0x95, 0x01,                         //   REPORT_COUNT (1)
				0x09, 0x56,                         //   USAGE (Scan Time)
				0x81, 0x02,                         //   INPUT (Data,Var,Abs)
		    // Contact Count
				0x09, 0x54,                         //   USAGE (Contact count)
		    0x25, 0x7f,                         //   LOGICAL_MAXIMUM (127)
		    0x95, 0x01,                         //   REPORT_COUNT (1)
		    0x75, 0x08,                         //   REPORT_SIZE (8)
		    0x81, 0x02,                         //   INPUT (Data,Var,Abs)
				// Contact Count Maximum Feature Report
		    0x85, REPORTID_MAX_COUNT,           //   REPORT_ID (Feature)
		    0x09, 0x55,                         //   USAGE(Contact Count Maximum)
		    0x95, 0x01,                         //   REPORT_COUNT (1)
		    0x25, 0x02,                         //   LOGICAL_MAXIMUM (2)
		    0xb1, 0x02,                         //   FEATURE (Data,Var,Abs)
				// Certification Feature Report
		    0x85, REPORTID_CERTIFICATION,       //   REPORT_ID (Feature)
		    0x06, 0x00, 0xff,                   //   USAGE_PAGE (Vendor Defined)
		    0x09, 0xC5,                         //   USAGE (Vendor Usage 0xC5)
		    0x15, 0x00,                         //   LOGICAL_MINIMUM (0)
		    0x26, 0xff, 0x00,                   //   LOGICAL_MAXIMUM (0xff)
		    0x75, 0x08,                         //   REPORT_SIZE (8)
		    0x96, 0x00,  0x01,                  //   REPORT_COUNT (0x100 (256))
		    0xb1, 0x02,                         //   FEATURE (Data,Var,Abs)
		    0xc0,                               // END_COLLECTION
  /* USER CODE END 0 */
  0xC0    /*     END_COLLECTION	             */
};

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Exported_Variables USBD_CUSTOM_HID_Exported_Variables
  * @brief Public variables.
  * @{
  */
extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */
/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_FunctionPrototypes USBD_CUSTOM_HID_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t CUSTOM_HID_Init_FS(void);
static int8_t CUSTOM_HID_DeInit_FS(void);
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state);

/**
  * @}
  */

USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_FS =
{
  CUSTOM_HID_ReportDesc_FS,
  CUSTOM_HID_Init_FS,
  CUSTOM_HID_DeInit_FS,
  CUSTOM_HID_OutEvent_FS
};

/** @defgroup USBD_CUSTOM_HID_Private_Functions USBD_CUSTOM_HID_Private_Functions
  * @brief Private functions.
  * @{
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_Init_FS(void)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  DeInitializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_DeInit_FS(void)
{
  /* USER CODE BEGIN 5 */
  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  Manage the CUSTOM HID class events
  * @param  event_idx: Event index
  * @param  state: Event state
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state)
{
  /* USER CODE BEGIN 6 */
  UNUSED(event_idx);
  UNUSED(state);

  /* Start next USB packet transfer once data processing is completed */
  if (USBD_CUSTOM_HID_ReceivePacket(&hUsbDeviceFS) != (uint8_t)USBD_OK)
  {
    return -1;
  }

  return (USBD_OK);
  /* USER CODE END 6 */
}

/* USER CODE BEGIN 7 */
/**
  * @brief  Send the report to the Host
  * @param  report: The report to be sent
  * @param  len: The report length
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
/*
static int8_t USBD_CUSTOM_HID_SendReport_FS(uint8_t *report, uint16_t len)
{
  return USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, report, len);
}
*/
/* USER CODE END 7 */

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

