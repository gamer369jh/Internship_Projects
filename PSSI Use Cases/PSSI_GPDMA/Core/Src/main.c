/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include <stdlib.h>
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
TIM_HandleTypeDef    htim;
TIM_OC_InitTypeDef   sConfig; /* Timer Output Compare Configuration Structure declaration */
//#define MASTER_BOARD
#define  TIMx                TIM1
#define  PERIOD_VALUE       (uint32_t)(1000 - 1)              /* Period Value             */
#define  PULSE1_VALUE       (uint32_t)(PERIOD_VALUE/2)        /* Capture Compare 1 Value  */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
uint32_t uhPrescalerValue = 0;
uint32_t Request_received = 0 ;
uint32_t data_cmp = 0 ;
uint32_t i;
uint32_t PSSI_HAL_PSSI_TransmitComplete_count = 0;
uint32_t PSSI_HAL_PSSI_ReceiveComplete_count = 0;
uint32_t PSSI_HAL_PSSI_ErrorCallback_count = 0;

#ifndef MASTER_BOARD
//ALIGN_32BYTES (char     pData8_S_TRSMT[64] ="Hello from Slave");  /* Data to transmit from Slave */
#define ALIGN_32BYTES __attribute__((aligned(32)))
char pData8_S_TRSMT[64] ALIGN_32BYTES = "Hello from Slave";
ALIGN_32BYTES char pData8_S_RCV[64];
#else
ALIGN_32BYTES (char     pData8_M_RCV[64]);
ALIGN_32BYTES (char     pData8_M_TRSMT[64]); /* Data to transmit from Master */
#endif
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

DMA_HandleTypeDef handle_GPDMA1_Channel13;
DMA_HandleTypeDef handle_GPDMA1_Channel12;

PSSI_HandleTypeDef hpssi;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
extern DMA_QListTypeDef  PSSITXQueue;
extern DMA_QListTypeDef  PSSIRXQueue;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void SystemPower_Config(void);
static void MX_GPIO_Init(void);
static void MX_GPDMA1_Init(void);
static void MX_ICACHE_Init(void);
static void MX_PSSI_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
#ifdef MASTER_BOARD
static void Timer_Config(TIM_HandleTypeDef *htim);
static void CLK_On(void);
static void CLK_Off(void);
static uint32_t Fetch_Slave_Request(char Received_Buffer[64]);
#endif /*MASTER_BOARD*/
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len) {
  HAL_UART_Transmit(&huart1, (uint8_t*) ptr, len, HAL_MAX_DELAY);
  return len;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* Configure the System Power */
  SystemPower_Config();

  /* USER CODE BEGIN SysInit */
  MX_PSSIRXQueue_Config();
  MX_PSSITXQueue_Config();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_GPDMA1_Init();
  MX_ICACHE_Init();
  MX_PSSI_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_DMAEx_List_LinkQ(&handle_GPDMA1_Channel13, &PSSITXQueue);
  __HAL_LINKDMA(&hpssi, hdmatx, handle_GPDMA1_Channel13);
  HAL_DMAEx_List_LinkQ(&handle_GPDMA1_Channel12, &PSSIRXQueue);
  __HAL_LINKDMA(&hpssi, hdmarx, handle_GPDMA1_Channel12);



#ifdef MASTER_BOARD
  printf("Hello this is the master board \n\r");
   HAL_Delay(500);
  /* Configure Tim to generate the clock for PSSI slave */
  Timer_Config(&htim) ;

  while(1)
  {
    CLK_On();



    while(Request_received != 1)
    {

      if(HAL_PSSI_Receive_DMA(&hpssi, (uint32_t*)pData8_M_RCV , sizeof(pData8_M_RCV)/4)!= HAL_OK)
      {
        Error_Handler();
      }

      while(PSSI_HAL_PSSI_ReceiveComplete_count !=1)
      {
        /* wait until receiving data is complete */
      }

      if(Fetch_Slave_Request(pData8_M_RCV) == 1)
      {
        Request_received = 1;
      }


      PSSI_HAL_PSSI_ReceiveComplete_count = 0 ;
    }

    /* Start transmitting the received & modified data */
    if(HAL_PSSI_Transmit_DMA(&hpssi, (uint32_t*)pData8_M_TRSMT, sizeof(pData8_M_TRSMT)/4)!= HAL_OK)
    {
      Error_Handler();
    }

    HAL_Delay(2);

    while(PSSI_HAL_PSSI_TransmitComplete_count != 1)
    {
      /* wait until transmit data is complete */
    }

    printf("Transmission completed\n\r");
    HAL_Delay(200);


    HAL_Delay(20);

    /* Transmit done */
    Request_received = 0 ;

    PSSI_HAL_PSSI_TransmitComplete_count = 0 ;

    CLK_Off();

    /*Wait 1s before the next loop*/
    HAL_Delay(1000);


  }
#else
  /*PSSI slave Part*/
  printf("Hello this is the slave board \n\r");
    HAL_Delay(500);
  /* Start transmitting the data */
  if(HAL_PSSI_Transmit_DMA(&hpssi, (uint32_t*)(pData8_S_TRSMT), sizeof(pData8_S_TRSMT))!= HAL_OK)
  {
    Error_Handler();
  }

  while(PSSI_HAL_PSSI_TransmitComplete_count != 1)
  {
    /* wait until transmit data is complete */
  }



  HAL_Delay(2);
  /* Start receiving the data */
  if(HAL_PSSI_Receive_DMA(&hpssi, (uint32_t*)(pData8_S_RCV), sizeof(pData8_S_RCV)/4)!= HAL_OK)
  {
    Error_Handler();
  }

  while(PSSI_HAL_PSSI_ReceiveComplete_count != 1)
  {
    /* wait until receiving data is complete */
  }



  /*********************************************************************************************/

  /* Check first that the transmitted data is received */
  for(i = 0; i < strlen(pData8_S_TRSMT) ;i++)
  {
    if(pData8_S_TRSMT[i] != pData8_S_RCV[i])
    {
      data_cmp++;
	  break;
    }
  }

  /*if OK , check then, that the Master has modified the transmitted data*/
  if((data_cmp == 0) && (strstr(pData8_S_RCV," Master") != 0))
  { /* Infinite loop */
    while (1)
    {
    	printf("data has been modified\n\r");
    	printf("%s\n\r",pData8_S_RCV);
    	HAL_Delay(1000);
    }
  }
  else /*KO*/
  {
    Error_Handler();
  }

#endif /*MASTER_BOARD*/
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_4;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLMBOOST = RCC_PLLMBOOST_DIV1;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLLVCIRANGE_0;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Power Configuration
  * @retval None
  */
static void SystemPower_Config(void)
{
  HAL_PWREx_EnableVddIO2();

  /*
   * Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral
   */
  HAL_PWREx_DisableUCPDDeadBattery();

  /*
   * Switch to SMPS regulator instead of LDO
   */
  if (HAL_PWREx_ConfigSupply(PWR_SMPS_SUPPLY) != HAL_OK)
  {
    Error_Handler();
  }
/* USER CODE BEGIN PWR */
/* USER CODE END PWR */
}

/**
  * @brief GPDMA1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPDMA1_Init(void)
{

  /* USER CODE BEGIN GPDMA1_Init 0 */

  /* USER CODE END GPDMA1_Init 0 */

  /* Peripheral clock enable */
  __HAL_RCC_GPDMA1_CLK_ENABLE();

  /* GPDMA1 interrupt Init */
    HAL_NVIC_SetPriority(GPDMA1_Channel12_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(GPDMA1_Channel12_IRQn);
    HAL_NVIC_SetPriority(GPDMA1_Channel13_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(GPDMA1_Channel13_IRQn);

  /* USER CODE BEGIN GPDMA1_Init 1 */

  /* USER CODE END GPDMA1_Init 1 */
  handle_GPDMA1_Channel13.Instance = GPDMA1_Channel13;
  handle_GPDMA1_Channel13.InitLinkedList.Priority = DMA_LOW_PRIORITY_LOW_WEIGHT;
  handle_GPDMA1_Channel13.InitLinkedList.LinkStepMode = DMA_LSM_FULL_EXECUTION;
  handle_GPDMA1_Channel13.InitLinkedList.LinkAllocatedPort = DMA_LINK_ALLOCATED_PORT1;
  handle_GPDMA1_Channel13.InitLinkedList.TransferEventMode = DMA_TCEM_EACH_LL_ITEM_TRANSFER;
  handle_GPDMA1_Channel13.InitLinkedList.LinkedListMode = DMA_LINKEDLIST_CIRCULAR;
  if (HAL_DMAEx_List_Init(&handle_GPDMA1_Channel13) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DMA_ConfigChannelAttributes(&handle_GPDMA1_Channel13, DMA_CHANNEL_NPRIV) != HAL_OK)
  {
    Error_Handler();
  }
  handle_GPDMA1_Channel12.Instance = GPDMA1_Channel12;
  handle_GPDMA1_Channel12.InitLinkedList.Priority = DMA_LOW_PRIORITY_LOW_WEIGHT;
  handle_GPDMA1_Channel12.InitLinkedList.LinkStepMode = DMA_LSM_FULL_EXECUTION;
  handle_GPDMA1_Channel12.InitLinkedList.LinkAllocatedPort = DMA_LINK_ALLOCATED_PORT1;
  handle_GPDMA1_Channel12.InitLinkedList.TransferEventMode = DMA_TCEM_EACH_LL_ITEM_TRANSFER;
  handle_GPDMA1_Channel12.InitLinkedList.LinkedListMode = DMA_LINKEDLIST_CIRCULAR;
  if (HAL_DMAEx_List_Init(&handle_GPDMA1_Channel12) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DMA_ConfigChannelAttributes(&handle_GPDMA1_Channel12, DMA_CHANNEL_NPRIV) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN GPDMA1_Init 2 */

  /* USER CODE END GPDMA1_Init 2 */

}

/**
  * @brief ICACHE Initialization Function
  * @param None
  * @retval None
  */
static void MX_ICACHE_Init(void)
{

  /* USER CODE BEGIN ICACHE_Init 0 */

  /* USER CODE END ICACHE_Init 0 */

  /* USER CODE BEGIN ICACHE_Init 1 */

  /* USER CODE END ICACHE_Init 1 */

  /** Enable instruction cache in 1-way (direct mapped cache)
  */
  if (HAL_ICACHE_ConfigAssociativityMode(ICACHE_1WAY) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_ICACHE_Enable() != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ICACHE_Init 2 */

  /* USER CODE END ICACHE_Init 2 */

}

/**
  * @brief PSSI Initialization Function
  * @param None
  * @retval None
  */
static void MX_PSSI_Init(void)
{

  /* USER CODE BEGIN PSSI_Init 0 */

  /* USER CODE END PSSI_Init 0 */

  /* USER CODE BEGIN PSSI_Init 1 */

  /* USER CODE END PSSI_Init 1 */
  hpssi.Instance = PSSI;
  hpssi.Init.DataWidth = HAL_PSSI_32BITS;
  hpssi.Init.BusWidth = HAL_PSSI_8LINES;
  hpssi.Init.ControlSignal = HAL_PSSI_DE_RDY_ALT_ENABLE;
  hpssi.Init.ClockPolarity = HAL_PSSI_FALLING_EDGE;
  hpssi.Init.DataEnablePolarity = HAL_PSSI_DEPOL_ACTIVE_LOW;
  hpssi.Init.ReadyPolarity = HAL_PSSI_RDYPOL_ACTIVE_LOW;
  if (HAL_PSSI_Init(&hpssi) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN PSSI_Init 2 */

  /* USER CODE END PSSI_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(UCPD_DBn_GPIO_Port, UCPD_DBn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_BUTTON_Pin */
  GPIO_InitStruct.Pin = USER_BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_BUTTON_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : VBUS_SENSE_Pin */
  GPIO_InitStruct.Pin = VBUS_SENSE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(VBUS_SENSE_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PA2 PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : UCPD_FLT_Pin */
  GPIO_InitStruct.Pin = UCPD_FLT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(UCPD_FLT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_RED_Pin */
  GPIO_InitStruct.Pin = LED_RED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_RED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_GREEN_Pin */
  GPIO_InitStruct.Pin = LED_GREEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GREEN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF10_USB;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : UCPD_DBn_Pin */
  GPIO_InitStruct.Pin = UCPD_DBn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(UCPD_DBn_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */


#ifdef MASTER_BOARD
void Timer_Config(TIM_HandleTypeDef *htim)
{
    /* Compute the prescaler value to have TIM1 counter clock equal to 20000 Hz */
  uhPrescalerValue = (uint32_t)(250000000 / (20000000)) - 1;

  htim->Instance = TIMx;

  htim->Init.Prescaler         = uhPrescalerValue;
  htim->Init.Period            = PERIOD_VALUE;
  htim->Init.ClockDivision     = 0;
  htim->Init.CounterMode       = TIM_COUNTERMODE_UP;
  htim->Init.RepetitionCounter = 0;

  if (HAL_TIM_PWM_Init(htim) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /*##-2- Configure the PWM channel #########################################*/
  /* configuration for the channel */
  sConfig.OCMode       = TIM_OCMODE_PWM1;
  sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;
  sConfig.OCFastMode   = TIM_OCFAST_DISABLE;
  sConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
  sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;

  sConfig.OCIdleState  = TIM_OCIDLESTATE_RESET;

  /* Set the pulse value for channel 1 */
  sConfig.Pulse = PULSE1_VALUE;

  if (HAL_TIM_PWM_ConfigChannel(htim, &sConfig, TIM_CHANNEL_1) != HAL_OK)
  {
    /* Configuration Error */
    Error_Handler();
  }

}

static void CLK_On(void)
{
  /*Start PWM signals generation #######################################*/
  /* Start channel 1 */
  if (HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_1) != HAL_OK)
  {
    /* PWM Generation Error */
    Error_Handler();
  }
}

static void CLK_Off(void)
{
  if (HAL_TIM_PWM_Stop(&htim, TIM_CHANNEL_1) != HAL_OK)
  {
    /* PWM Generation Error */
    Error_Handler();
  }
}

uint32_t Fetch_Slave_Request(char Received_Buffer[64])
{
  uint32_t j;
  char REPLY[23] = ": received, from Master" ;

  if(strstr(Received_Buffer,"Slave") != 0)
  {
    for(i=0 ; i < strlen(Received_Buffer) ; i++)
    {
      pData8_M_TRSMT[i] = Received_Buffer[i];
    }

    for(j=0;j<strlen(REPLY);j++)
    {
      pData8_M_TRSMT[i] = REPLY[j];
      i++;
    }
    return 1;
  }
  else
  {
    return 0;
  }
}

#endif /* MASTER_BOARD */



void HAL_PSSI_TxCpltCallback(PSSI_HandleTypeDef *hpssi)
{
  PSSI_HAL_PSSI_TransmitComplete_count++;
}
/**
  * @brief PSSI receive complete callback
  * @par hppsi: PSSI HAL handle
  * @retval None
  */
 void HAL_PSSI_RxCpltCallback(PSSI_HandleTypeDef *hpssi)
{
  PSSI_HAL_PSSI_ReceiveComplete_count++;
}

/**
  * @brief PSSI transfer error callback
  * @par hppsi: PSSI HAL handle
  * @retval None
  */
void HAL_PSSI_ErrorCallback(PSSI_HandleTypeDef *hpssi)
{
  PSSI_HAL_PSSI_ErrorCallback_count++;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
