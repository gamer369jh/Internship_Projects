/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file         stm32u5xx_hal_msp.c
  * @brief        This file provides code for the MSP Initialization
  *               and de-Initialization codes.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Define */

/* USER CODE END Define */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Macro */

/* USER CODE END Macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */

/* USER CODE END ExternalFunctions */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  __HAL_RCC_PWR_CLK_ENABLE();

  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_3);

  /* System interrupt init*/

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

/**
* @brief DCMI MSP Initialization
* This function configures the hardware resources used in this example
* @param hdcmi: DCMI handle pointer
* @retval None
*/
void HAL_DCMI_MspInit(DCMI_HandleTypeDef* hdcmi)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hdcmi->Instance==DCMI)
  {
  /* USER CODE BEGIN DCMI_MspInit 0 */

  /* USER CODE END DCMI_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_DCMI_PSSI_CLK_ENABLE();

    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    /**DCMI GPIO Configuration
    PI6     ------> DCMI_D6
    PI5     ------> DCMI_VSYNC
    PI4     ------> DCMI_D5
    PH12     ------> DCMI_D3
    PI7     ------> DCMI_D7
    PH14     ------> DCMI_D4
    PH10     ------> DCMI_D1
    PH11     ------> DCMI_D2
    PH8     ------> DCMI_HSYNC
    PH9     ------> DCMI_D0
    PH5     ------> DCMI_PIXCLK
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF10_DCMI;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_14|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF10_DCMI;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    /* DCMI interrupt Init */
    HAL_NVIC_SetPriority(DCMI_PSSI_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DCMI_PSSI_IRQn);
  /* USER CODE BEGIN DCMI_MspInit 1 */

  /* USER CODE END DCMI_MspInit 1 */
  }

}

/**
* @brief DCMI MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hdcmi: DCMI handle pointer
* @retval None
*/
void HAL_DCMI_MspDeInit(DCMI_HandleTypeDef* hdcmi)
{
  if(hdcmi->Instance==DCMI)
  {
  /* USER CODE BEGIN DCMI_MspDeInit 0 */

  /* USER CODE END DCMI_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_DCMI_PSSI_CLK_DISABLE();

    /**DCMI GPIO Configuration
    PI6     ------> DCMI_D6
    PI5     ------> DCMI_VSYNC
    PI4     ------> DCMI_D5
    PH12     ------> DCMI_D3
    PI7     ------> DCMI_D7
    PH14     ------> DCMI_D4
    PH10     ------> DCMI_D1
    PH11     ------> DCMI_D2
    PH8     ------> DCMI_HSYNC
    PH9     ------> DCMI_D0
    PH5     ------> DCMI_PIXCLK
    */
    HAL_GPIO_DeInit(GPIOI, GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_7);

    HAL_GPIO_DeInit(GPIOH, GPIO_PIN_12|GPIO_PIN_14|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_5);

    /* DCMI interrupt DeInit */
    HAL_NVIC_DisableIRQ(DCMI_PSSI_IRQn);
  /* USER CODE BEGIN DCMI_MspDeInit 1 */

  /* USER CODE END DCMI_MspDeInit 1 */
  }

}

static uint32_t FMC_Initialized = 0;

static void HAL_FMC_MspInit(void){
  /* USER CODE BEGIN FMC_MspInit 0 */

  /* USER CODE END FMC_MspInit 0 */
  GPIO_InitTypeDef GPIO_InitStruct ={0};
  if (FMC_Initialized) {
    return;
  }
  FMC_Initialized = 1;

  /* Peripheral clock enable */
  __HAL_RCC_FMC_CLK_ENABLE();

  /** FMC GPIO Configuration
  PD0   ------> FMC_D2
  PE1   ------> FMC_NBL1
  PD4   ------> FMC_NOE
  PE3   ------> FMC_A19
  PE0   ------> FMC_NBL0
  PD7   ------> FMC_NE1
  PF0   ------> FMC_A0
  PE6   ------> FMC_A22
  PG12   ------> FMC_NE4
  PD5   ------> FMC_NWE
  PF1   ------> FMC_A1
  PF2   ------> FMC_A2
  PD1   ------> FMC_D3
  PF5   ------> FMC_A5
  PF3   ------> FMC_A3
  PF4   ------> FMC_A4
  PG1   ------> FMC_A11
  PE10   ------> FMC_D7
  PG4   ------> FMC_A14
  PG0   ------> FMC_A10
  PE9   ------> FMC_D6
  PG3   ------> FMC_A13
  PG5   ------> FMC_A15
  PD14   ------> FMC_D0
  PD15   ------> FMC_D1
  PF12   ------> FMC_A6
  PE8   ------> FMC_D5
  PE14   ------> FMC_D11
  PD12   ------> FMC_A17
  PD10   ------> FMC_D15
  PD13   ------> FMC_A18
  PG2   ------> FMC_A12
  PF14   ------> FMC_A8
  PE7   ------> FMC_D4
  PE13   ------> FMC_D10
  PD8   ------> FMC_D13
  PD9   ------> FMC_D14
  PF13   ------> FMC_A7
  PE11   ------> FMC_D8
  PE15   ------> FMC_D12
  PD11   ------> FMC_A16
  PF15   ------> FMC_A9
  PE12   ------> FMC_DA9
  PE12   ------> FMC_D9
  */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_4|GPIO_PIN_7|GPIO_PIN_5
                          |GPIO_PIN_1|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_12
                          |GPIO_PIN_10|GPIO_PIN_13|GPIO_PIN_8|GPIO_PIN_9
                          |GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_0|FMC_A22_LCD_RS_Pin
                          |GPIO_PIN_10|GPIO_PIN_9|GPIO_PIN_8|GPIO_PIN_14
                          |GPIO_PIN_7|GPIO_PIN_13|GPIO_PIN_11|GPIO_PIN_15
                          |GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_5
                          |GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_12|GPIO_PIN_14
                          |GPIO_PIN_13|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_0
                          |GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /* USER CODE BEGIN FMC_MspInit 1 */

  /* USER CODE END FMC_MspInit 1 */
}

void HAL_SRAM_MspInit(SRAM_HandleTypeDef* hsram){
  /* USER CODE BEGIN SRAM_MspInit 0 */

  /* USER CODE END SRAM_MspInit 0 */
  HAL_FMC_MspInit();
  /* USER CODE BEGIN SRAM_MspInit 1 */

  /* USER CODE END SRAM_MspInit 1 */
}

static uint32_t FMC_DeInitialized = 0;

static void HAL_FMC_MspDeInit(void){
  /* USER CODE BEGIN FMC_MspDeInit 0 */

  /* USER CODE END FMC_MspDeInit 0 */
  if (FMC_DeInitialized) {
    return;
  }
  FMC_DeInitialized = 1;
  /* Peripheral clock enable */
  __HAL_RCC_FMC_CLK_DISABLE();

  /** FMC GPIO Configuration
  PD0   ------> FMC_D2
  PE1   ------> FMC_NBL1
  PD4   ------> FMC_NOE
  PE3   ------> FMC_A19
  PE0   ------> FMC_NBL0
  PD7   ------> FMC_NE1
  PF0   ------> FMC_A0
  PE6   ------> FMC_A22
  PG12   ------> FMC_NE4
  PD5   ------> FMC_NWE
  PF1   ------> FMC_A1
  PF2   ------> FMC_A2
  PD1   ------> FMC_D3
  PF5   ------> FMC_A5
  PF3   ------> FMC_A3
  PF4   ------> FMC_A4
  PG1   ------> FMC_A11
  PE10   ------> FMC_D7
  PG4   ------> FMC_A14
  PG0   ------> FMC_A10
  PE9   ------> FMC_D6
  PG3   ------> FMC_A13
  PG5   ------> FMC_A15
  PD14   ------> FMC_D0
  PD15   ------> FMC_D1
  PF12   ------> FMC_A6
  PE8   ------> FMC_D5
  PE14   ------> FMC_D11
  PD12   ------> FMC_A17
  PD10   ------> FMC_D15
  PD13   ------> FMC_A18
  PG2   ------> FMC_A12
  PF14   ------> FMC_A8
  PE7   ------> FMC_D4
  PE13   ------> FMC_D10
  PD8   ------> FMC_D13
  PD9   ------> FMC_D14
  PF13   ------> FMC_A7
  PE11   ------> FMC_D8
  PE15   ------> FMC_D12
  PD11   ------> FMC_A16
  PF15   ------> FMC_A9
  PE12   ------> FMC_DA9
  PE12   ------> FMC_D9
  */
  HAL_GPIO_DeInit(GPIOD, GPIO_PIN_0|GPIO_PIN_4|GPIO_PIN_7|GPIO_PIN_5
                          |GPIO_PIN_1|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_12
                          |GPIO_PIN_10|GPIO_PIN_13|GPIO_PIN_8|GPIO_PIN_9
                          |GPIO_PIN_11);

  HAL_GPIO_DeInit(GPIOE, GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_0|FMC_A22_LCD_RS_Pin
                          |GPIO_PIN_10|GPIO_PIN_9|GPIO_PIN_8|GPIO_PIN_14
                          |GPIO_PIN_7|GPIO_PIN_13|GPIO_PIN_11|GPIO_PIN_15
                          |GPIO_PIN_12);

  HAL_GPIO_DeInit(GPIOF, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_5
                          |GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_12|GPIO_PIN_14
                          |GPIO_PIN_13|GPIO_PIN_15);

  HAL_GPIO_DeInit(GPIOG, GPIO_PIN_12|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_0
                          |GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_2);

  /* USER CODE BEGIN FMC_MspDeInit 1 */

  /* USER CODE END FMC_MspDeInit 1 */
}

void HAL_SRAM_MspDeInit(SRAM_HandleTypeDef* hsram){
  /* USER CODE BEGIN SRAM_MspDeInit 0 */

  /* USER CODE END SRAM_MspDeInit 0 */
  HAL_FMC_MspDeInit();
  /* USER CODE BEGIN SRAM_MspDeInit 1 */

  /* USER CODE END SRAM_MspDeInit 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
