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
int TIP_SWITCH_RESET = 0b00000000;
int TIP_SWITCH_SET = 0b10000000;
int CONTACT_RESET = 0;
int CONTACT_REMOVED = -1;
int CONTACT_SET = 1;
int DELAY_AFTER_SENDING = 100;

typedef struct
{
	uint8_t tip_switch;
	uint8_t contact_ID;
	uint16_t x;
	uint16_t y;
} Contact;

typedef struct
{
	uint8_t report_ID;
	Contact contacts[MAX_CONTACT_COUNT];
	uint16_t scan_time;
	uint8_t contact_count;
} TouchReport;

TouchReport touchReport;
int8_t contact_states[MAX_CONTACT_COUNT];
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

int touchscreen_set_contact(uint8_t ID, uint16_t x, uint16_t y)
{
	if (ID >= MAX_CONTACT_COUNT)
	{
		return TOUCHSCREEN_FAILURE;
	}
	contact_states[ID] = CONTACT_SET;
	touchReport.contacts[ID].tip_switch = TIP_SWITCH_SET;
	touchReport.contacts[ID].x = x;
	touchReport.contacts[ID].y = y;
	return TOUCHSCREEN_SUCCESS;
}

int touchscreen_remove_contact(uint8_t ID)
{
	if (ID >= MAX_CONTACT_COUNT)
	{
		return TOUCHSCREEN_FAILURE;
	}
	contact_states[ID] = CONTACT_REMOVED;
	touchReport.contacts[ID].tip_switch = TIP_SWITCH_RESET;
	return TOUCHSCREEN_SUCCESS;
}

void touchscreen_clear(void)
{

}

int touchscreen_send(uint16_t scan_time)
{
	touchReport.report_ID = REPORTID_TOUCH;
	int count;
	for (int i = 0; i < MAX_CONTACT_COUNT; i++)
		{
			if (contact_states[i] != CONTACT_RESET)
			{
				count++;
			}
		}
	touchReport.contact_count = count;
	touchReport.scan_time = scan_time;
	int result = USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t *) &touchReport, sizeof (touchReport));
	for (int i = 0; i < MAX_CONTACT_COUNT; i++)
	{
		if (contact_states[i] == CONTACT_REMOVED)
		{
			contact_states[i] = CONTACT_RESET;
		}
	}
	HAL_Delay(DELAY_AFTER_SENDING);
	if (result == USBD_OK)
	{
		return TOUCHSCREEN_SUCCESS;
	}
	else
	{
		return TOUCHSCREEN_FAILURE;
	}
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

