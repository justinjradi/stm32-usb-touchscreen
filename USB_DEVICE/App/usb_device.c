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
int TIP_SWITCH_SET = 0b00000001;
int CONTACT_RESET = 0;
int CONTACT_REMOVED = -1;
int CONTACT_SET = 1;
int DELAY_AFTER_SENDING = 100;

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
	Contact contacts[MAX_CONTACT_COUNT];
	uint16_t scan_time;
	uint8_t contact_count;
} TouchReport;

Contact contact_0;
Contact contact_1;
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

void touchscreen_init(void)
{
	touchReport.report_ID = REPORTID_TOUCH;
	Contact contacts[2] = {contact_0, contact_1};
	memcpy(touchReport.contacts, contacts, sizeof(contacts));
	touchReport.contacts[0].contact_ID = 0;
	touchReport.contacts[1].contact_ID = 1;
}

void touchscreen_test(void)
{
	// Set

	touchReport.contacts[0].tip_switch = TIP_SWITCH_SET;
	touchReport.contacts[0].x = 700;
	touchReport.contacts[0].y = 600;

	touchReport.contacts[1].tip_switch = TIP_SWITCH_SET;
	touchReport.contacts[1].x = 700;
	touchReport.contacts[1].y = 700;


	touchReport.contact_count = 2;
	touchReport.scan_time = 0;
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t *) &touchReport, sizeof (touchReport));
	HAL_Delay(250);

	// Set

	touchReport.contacts[0].tip_switch = TIP_SWITCH_SET;
	touchReport.contacts[0].x = 750;
	touchReport.contacts[0].y = 600;

	touchReport.contacts[1].tip_switch = TIP_SWITCH_SET;
	touchReport.contacts[1].x = 750;
	touchReport.contacts[1].y = 700;


	touchReport.contact_count = 2;
	touchReport.scan_time = 2500;
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t *) &touchReport, sizeof (touchReport));
	HAL_Delay(250);

	// Set

	touchReport.contacts[0].tip_switch = TIP_SWITCH_SET;
	touchReport.contacts[0].x = 800;
	touchReport.contacts[0].y = 600;

	touchReport.contacts[1].tip_switch = TIP_SWITCH_SET;
	touchReport.contacts[1].x = 800;
	touchReport.contacts[1].y = 700;


	touchReport.contact_count = 2;
	touchReport.scan_time = 5000;
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t *) &touchReport, sizeof (touchReport));
	HAL_Delay(250);

	// Set

	touchReport.contacts[0].tip_switch = TIP_SWITCH_SET;
	touchReport.contacts[0].x = 800;
	touchReport.contacts[0].y = 600;

	touchReport.contacts[1].tip_switch = TIP_SWITCH_SET;
	touchReport.contacts[1].x = 800;
	touchReport.contacts[1].y = 700;


	touchReport.contact_count = 2;
	touchReport.scan_time = 7500;
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t *) &touchReport, sizeof (touchReport));
	HAL_Delay(250);

	// Set

	touchReport.contacts[0].tip_switch = TIP_SWITCH_SET;
	touchReport.contacts[0].x = 850;
	touchReport.contacts[0].y = 600;

	touchReport.contacts[1].tip_switch = TIP_SWITCH_SET;
	touchReport.contacts[1].x = 850;
	touchReport.contacts[1].y = 700;


	touchReport.contact_count = 2;
	touchReport.scan_time = 10000;
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t *) &touchReport, sizeof (touchReport));
	HAL_Delay(250);

	// Remove

	touchReport.contacts[0].tip_switch = TIP_SWITCH_RESET;
	touchReport.contacts[1].tip_switch = TIP_SWITCH_RESET;

	touchReport.contact_count = 2;
	touchReport.scan_time = 12500;
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t *) &touchReport, sizeof (touchReport));
	HAL_Delay(250);

	// Reset

	touchReport.contacts[0].tip_switch = TIP_SWITCH_RESET;
	touchReport.contacts[1].tip_switch = TIP_SWITCH_RESET;

	touchReport.contact_count = 0;
	touchReport.scan_time = 15000;
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t *) &touchReport, sizeof (touchReport));
	HAL_Delay(250);
}

void touchscreen_press(uint16_t scan_time)
{
	touchReport.contacts[0].tip_switch = TIP_SWITCH_SET;
	touchReport.contacts[0].x = 700;
	touchReport.contacts[0].y = 600;
	touchReport.contact_count = 1;
	touchReport.scan_time = scan_time;
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t *) &touchReport, sizeof (touchReport));
}

void touchscreen_unpress(uint16_t scan_time)
{
	touchReport.contacts[0].tip_switch = TIP_SWITCH_RESET;
	touchReport.scan_time = scan_time;
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t *) &touchReport, sizeof (touchReport));
}

void touchscreen_reset(uint16_t scan_time)
{
	touchReport.contact_count = 0;
	touchReport.scan_time = scan_time;
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t *) &touchReport, sizeof (touchReport));
}

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

int touchscreen_send(uint16_t scan_time)
{
	touchReport.report_ID = REPORTID_TOUCH;
	int count;
	for (int i = 0; i < MAX_CONTACT_COUNT; i++)
		{
			touchReport.contacts[i].contact_ID = i;
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

