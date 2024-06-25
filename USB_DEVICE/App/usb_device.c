/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usb_device.c
  * @version        : v1.0_Cube
  * @brief          : This file implements the USB Device
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

#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_customhid.h"
#include "usbd_custom_hid_if.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

typedef struct __attribute__((packed))
{
	uint8_t tip_switch;
	uint8_t contact_ID;
	uint16_t x;
	uint16_t y;
} Contact;	// contact size = 6 bytes

typedef struct __attribute__((packed))
{
	uint8_t report_ID;
	Contact reported_contacts[TOUCHSCREEN_MAX_CONTACTS];
	uint16_t scan_time;
	uint8_t contact_count;
} TouchReport;	// touch report size = 4 + (contact size * TOUCHSCREEN_MAX_CONTACTS) = 4 + 30 = 34

Contact contacts_by_ID[TOUCHSCREEN_MAX_CONTACTS];
/* USER CODE END PV */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USB Device Core handle declaration. */
USBD_HandleTypeDef hUsbDeviceFS;

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 1 */

void touchscreen_set(uint8_t contact_ID, uint16_t x, uint16_t y)
{
	contacts_by_ID[contact_ID].tip_switch = 1;
	contacts_by_ID[contact_ID].x = x;
	contacts_by_ID[contact_ID].y = y;
}

void touchscreen_reset(uint8_t contact_ID)
{
	contacts_by_ID[contact_ID].tip_switch = 0;
}

void touchscreen_update(int scan_time_ms)
{
	TouchReport touchReport;
	int reporting_order = 0;
	for (int id = 0; id < TOUCHSCREEN_MAX_CONTACTS; id++)
	{
		if (contacts_by_ID[id].tip_switch)
		{
			contacts_by_ID[id].contact_ID = id;
			touchReport.reported_contacts[reporting_order] = contacts_by_ID[id];
			reporting_order++;
		}
	}
	for (int j = reporting_order; j < TOUCHSCREEN_MAX_CONTACTS; j++)
	{
		memset(&touchReport.reported_contacts[j], 0, sizeof (Contact));
	}
	touchReport.report_ID = REPORTID_TOUCH;
	touchReport.scan_time = (uint16_t) (scan_time_ms * 10);	// Convert 100μs units to 1ms units and let overflow wrap around
	touchReport.contact_count = reporting_order;
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t *) &touchReport, sizeof (touchReport));
}

/* USER CODE END 1 */

/**
  * Init USB device Library, add supported class and start the library
  * @retval None
  */
void MX_USB_DEVICE_Init(void)
{
  /* USER CODE BEGIN USB_DEVICE_Init_PreTreatment */

  /* USER CODE END USB_DEVICE_Init_PreTreatment */

  /* Init Device Library, add supported class and start the library. */
  if (USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS) != USBD_OK)
  {
    Error_Handler();
  }
  if (USBD_RegisterClass(&hUsbDeviceFS, &USBD_CUSTOM_HID) != USBD_OK)
  {
    Error_Handler();
  }
  if (USBD_CUSTOM_HID_RegisterInterface(&hUsbDeviceFS, &USBD_CustomHID_fops_FS) != USBD_OK)
  {
    Error_Handler();
  }
  if (USBD_Start(&hUsbDeviceFS) != USBD_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN USB_DEVICE_Init_PostTreatment */

  /* USER CODE END USB_DEVICE_Init_PostTreatment */
}

/**
  * @}
  */

/**
  * @}
  */

