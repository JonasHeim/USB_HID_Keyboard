/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usb_device.c
  * @version        : v2.0_Cube
  * @brief          : This file implements the USB Device
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/

#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_hid.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

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
static uint8_t keyboard_report[8] = {0};
/* USER CODE END 0 */

/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 1 */
void MX_USB_Send_Run(void)
{
  keyboard_report[0] = 0x08; //send LEFT_GUI_META
  USBD_HID_SendReport(&hUsbDeviceFS, keyboard_report, 8);
  HAL_Delay(50);
  keyboard_report[2] = 0x15; //send r
  USBD_HID_SendReport(&hUsbDeviceFS, keyboard_report, 8);
}

void MX_USB_DEVICE_Send(uint8_t keycode)
{
  keyboard_report[2] = keycode; //send keycode

  USBD_HID_SendReport(&hUsbDeviceFS, keyboard_report, 8);
}

void MX_USB_DEVICE_Set_n(uint8_t keycode, uint8_t n)
{
  if(n < 8)
  {
    keyboard_report[n] = keycode; //set keycode
  }
}

void MX_USB_DEVICE_Send_MOD(uint8_t modcode, uint8_t keycode)
{
  keyboard_report[0] = modcode; //send modifier
  keyboard_report[2] = keycode; //send keycode

  USBD_HID_SendReport(&hUsbDeviceFS, keyboard_report, 8);
}

void MX_USB_DEVICE_Release(void)
{
  //clear modifier
  for(int i = 0; i < 8; i++)
  {
    if(keyboard_report[i])
    {
      keyboard_report[i] = 0;
    }
  }

  USBD_HID_SendReport(&hUsbDeviceFS, keyboard_report, 8);
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
  if (USBD_RegisterClass(&hUsbDeviceFS, &USBD_HID) != USBD_OK)
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
