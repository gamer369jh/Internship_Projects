/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "linked_list.h"
#include "stm32u575i_eval.h"
#include "stm32u575i_eval_io.h"
#include "stm32u575i_eval_lcd.h"
#include "stm32u575i_eval_bus.h"
#include "../lcd/stm32_lcd.h"
#include "../Components/ov5640/ov5640.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define FRAME_WIDTH            320
#define FRAME_HEIGHT           240
#define FMC_ADDRESS            FMC_BANK1_4
#define REGION_SIZE            0x0CFFFFFF

#define XSDN_PIN               GPIO_PIN_3
#define XSDN_PORT              GPIOI
#define RSTI_PIN               GPIO_PIN_2
#define RSTI_PORT              GPIOI
#define CAM_PLUG_PIN           GPIO_PIN_10
#define CAM_PLUG_PORT          GPIOG
#define CAMERA_OV5640_ADDRESS  0x78U
#define CAMERA_R320x240        1U     /* QVGA Resolution             */
/* Camera Pixel Format */
#define CAMERA_PF_RGB565       0U     /* Pixel Format RGB565         */
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define GYRO_ACC_INT_Pin GPIO_PIN_15
#define GYRO_ACC_INT_GPIO_Port GPIOH
#define SDCARD_DETECT_Pin GPIO_PIN_0
#define SDCARD_DETECT_GPIO_Port GPIOI
#define CAMERA_PLUG_Pin GPIO_PIN_10
#define CAMERA_PLUG_GPIO_Port GPIOG
#define CAMERA_XSDN_Pin GPIO_PIN_3
#define CAMERA_XSDN_GPIO_Port GPIOI
#define CAMERA_RSTI_Pin GPIO_PIN_2
#define CAMERA_RSTI_GPIO_Port GPIOI
#define USER_BUTTON_Pin GPIO_PIN_13
#define USER_BUTTON_GPIO_Port GPIOC
#define USER_BUTTON_EXTI_IRQn EXTI13_IRQn
#define FMC_A22_LCD_RS_Pin GPIO_PIN_6
#define FMC_A22_LCD_RS_GPIO_Port GPIOE
#define UCPD_FLT_Pin GPIO_PIN_8
#define UCPD_FLT_GPIO_Port GPIOB
#define LED_GREEN_Pin GPIO_PIN_7
#define LED_GREEN_GPIO_Port GPIOB
#define LED_RED_Pin GPIO_PIN_7
#define LED_RED_GPIO_Port GPIOH
#define LCD_BL_CTRL_Pin GPIO_PIN_8
#define LCD_BL_CTRL_GPIO_Port GPIOA
#define IBUS_SENSE_Pin GPIO_PIN_0
#define IBUS_SENSE_GPIO_Port GPIOA
#define VBUS_SENSE_Pin GPIO_PIN_5
#define VBUS_SENSE_GPIO_Port GPIOA
#define MFX_IRQ_OUT_Pin GPIO_PIN_5
#define MFX_IRQ_OUT_GPIO_Port GPIOC
#define MFX_WAKEUP_Pin GPIO_PIN_11
#define MFX_WAKEUP_GPIO_Port GPIOF

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
