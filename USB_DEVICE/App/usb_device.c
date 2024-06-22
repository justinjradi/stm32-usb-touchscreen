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
} Contact;

typedef struct __attribute__((packed))
{
	uint8_t report_ID;
	Contact contacts[TOUCHSCREEN_MAX_CONTACTS];
	uint16_t scan_time;
	uint8_t contact_count;
} TouchReport;

Contact contact_0;
Contact contact_1;
TouchReport touchReport;
uint8_t contacts_counted[TOUCHSCREEN_MAX_CONTACTS];
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

void touchscreen_init(void)
{
	touchReport.report_ID = REPORTID_TOUCH;
	Contact contacts[2] = {contact_0, contact_1};
	memcpy(touchReport.contacts, contacts, sizeof(contacts));
	touchReport.contacts[0].contact_ID = 0;
	touchReport.contacts[1].contact_ID = 1;
}

int touchscreen_set(uint8_t ID, uint16_t x, uint16_t y)
{
	if ((ID >= TOUCHSCREEN_MAX_CONTACTS) || (x > TOUCHSCREEN_WIDTH) || (y > TOUCHSCREEN_HEIGHT))
	{
		return TOUCHSCREEN_FAILURE;
	}
	touchReport.contacts[ID].tip_switch = 1;
	contacts_counted[ID] = 1;
	touchReport.contacts[ID].x = x;
	touchReport.contacts[ID].y = y;
	return TOUCHSCREEN_SUCCESS;
}

int touchscreen_reset(uint8_t ID)
{
	if (ID >= TOUCHSCREEN_MAX_CONTACTS)
	{
		return TOUCHSCREEN_FAILURE;
	}
	touchReport.contacts[ID].tip_switch = 0;
	return TOUCHSCREEN_SUCCESS;
}

void touchscreen_update(uint16_t scan_time)
{
	int contact_count = 0;
	for (int ID = 0; ID < TOUCHSCREEN_MAX_CONTACTS; ID++)
	{
		if (contacts_counted[ID])
		{
			contact_count++;
		}
		if (touchReport.contacts[ID].tip_switch == 0)
		{
			contacts_counted[ID] = 0;
		}
	}
	touchReport.contact_count = contact_count;
	touchReport.scan_time = scan_time;
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

