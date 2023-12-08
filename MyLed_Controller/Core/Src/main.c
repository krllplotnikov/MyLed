/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ESP_AT.h"
#include "WS2812B.h"
#include "WS2812B_Effects.h"
#include "FlashPROM.h"
#include <stdio.h>
#include <stdlib.h>

#define RX_BUFF_SIZE 33
#define MAX_LEDS 240
#define FIRST_WRITE_KEY 13
#define SETTINGS_BUFFSIZE (sizeof(Settings))
#define AUTOSAVE_PERIOD 10000
unsigned long autosaveTimer = 0;

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
DMA_HandleTypeDef hdma_tim1_ch1;

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//---------Commands-----------
enum Commands{
	SET_BRIGHTNESS,
	SET_COLOR,
    SET_EFFECT,
	SET_EFFECT_DELAY,
	SET_COLOR_MUSIC,
	SET_COLOR_MUSIC_DELAY,
	SET_COLOR_MUSIC_SENSIVITY,
    SET_NUM_LEDS,
    SET_WIFI_SETTENGS,
	SET_AP_SETTINGS,
	SET_ON_OFF
};

//---------Settings-----------
typedef struct{
	uint8_t firstWriteKey;
	uint8_t brightness;
	uint8_t colorR;
	uint8_t colorG;
	uint8_t colorB;
	uint8_t effect;
	uint8_t effectDelay;
	uint8_t colorMusic;
	uint8_t colorMusicDelay;
	uint8_t colorMusicLowSensivity;
	uint8_t colorMusicMediumSensivity;
	uint8_t colorMusicHighSensivity;
	uint8_t numleds;
	uint8_t ssidSTA[16];
	uint8_t passSTA[16];
	uint8_t ssidAP[16];
	uint8_t passAP[16];
	uint8_t onOff;
}Settings;
Settings settings = {0};

WS2812B_t myled;
uint8_t rxBuff[RX_BUFF_SIZE] = {};
uint8_t dataReceivedFlag = 0;

void ESP_IPD_Callback(uint8_t id, uint16_t len, char* data){
	if(!dataReceivedFlag){
		memcpy(rxBuff, data, len);
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		dataReceivedFlag = 1;
	}
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

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HAL_Delay(100);
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);

  FlashPROM_Init(SETTINGS_BUFFSIZE);
  FlashPROM_Read((void*)&settings);
  if(settings.firstWriteKey != FIRST_WRITE_KEY){
	  settings.firstWriteKey = FIRST_WRITE_KEY;
	  settings.brightness = 32;
	  settings.numleds = 60;
	  settings.effectDelay = 50;
	  settings.colorR = 255;
	  settings.colorG = 0;
	  settings.colorB = 0;
	  settings.effect = 0;
	  settings.effectDelay = 50;
	  settings.colorMusic = 0;
	  settings.colorMusicDelay = 50;
	  settings.colorMusicLowSensivity = 35;
	  settings.colorMusicMediumSensivity = 35;
	  settings.colorMusicHighSensivity = 35;
	  sprintf((char*)settings.ssidSTA, "none");
	  sprintf((char*)settings.passSTA, "none");
	  sprintf((char*)settings.ssidAP, "MyLed");
	  sprintf((char*)settings.passAP, "myled1305");
	  settings.onOff = 1;
	  FlashPROM_Write((void*)&settings);
  }

  ESP_Init(&huart1);
  ESP_STA_Mode();
  ESP_STA_IP("192.168.0.113", "192.168.0.1", "255.255.255.0");
  if(!ESP_ConnectToAP((char*)settings.ssidSTA, (char*)settings.passSTA))
  {
	  ESP_AP_Mode();
	  ESP_AP_Config((char*)settings.ssidAP, (char*)settings.passAP, 1, 2);
	  ESP_AP_IP("192.168.0.113", "192.168.0.1", "255.255.255.0");
  }
  ESP_StartTCPServer(1305);
  ESP_EnableCallbacs();

  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  WS2812B_Init(&myled, MAX_LEDS, &htim1, TIM_CHANNEL_1);
  WS2812B_SetBrightness(&myled, settings.brightness);
  WS2812B_SetNumLeds(&myled, settings.numleds);

  memset(rxBuff, 0, RX_BUFF_SIZE);

  while (1)
  {
		if(settings.onOff){
			WS2812B_MakeEffect(&myled, settings.effect, settings.effectDelay);

			if(!settings.effect){
				for(size_t i = 0; i < MAX_LEDS; i++){
					WS2812B_SetPixelRGB(&myled, settings.colorR, settings.colorG, settings.colorB, i);
				}
			}
			WS2812B_Show(&myled);
		}else{
			WS2812B_Off(&myled);
		}
		if(HAL_GetTick() - autosaveTimer > AUTOSAVE_PERIOD && autosaveTimer != 0){
			FlashPROM_Write((void*)&settings);
			autosaveTimer = 0;
		}

	  if(dataReceivedFlag){
		  switch (rxBuff[0])
		  	{
		  	case SET_BRIGHTNESS:
		  	{
		  		settings.brightness = rxBuff[1];
		  		WS2812B_SetBrightness(&myled, settings.brightness);
		  		break;
		  	}
		  	case SET_COLOR:
		  	{
		  		settings.colorR = rxBuff[1];
		  		settings.colorG = rxBuff[2];
		  		settings.colorB = rxBuff[3];
		  		for(int i = 0; i < settings.numleds; i++)
		  			WS2812B_SetPixelRGB(&myled, settings.colorR, settings.colorG, settings.colorB, i);
		  		break;
		  	}
		  	case SET_EFFECT:
		  	{
		  		settings.effect = rxBuff[1];
		  		break;
		  	}
		  	case SET_EFFECT_DELAY:
		  	{
		  		settings.effectDelay = rxBuff[1];
		  		break;
		  	}
		  	case SET_COLOR_MUSIC:
		  	{
		  		settings.colorMusic = rxBuff[1];
		  		break;
		  	}
		  	case SET_COLOR_MUSIC_DELAY:
		  	{
		  		settings.colorMusicDelay = rxBuff[1];
		  		break;
		  	}
		  	case SET_COLOR_MUSIC_SENSIVITY:
		  	{
		  		settings.colorMusicLowSensivity = rxBuff[1];
		  		settings.colorMusicMediumSensivity = rxBuff[2];
		  		settings.colorMusicHighSensivity = rxBuff[3];
		  		break;
		  	}
		  	case SET_NUM_LEDS:
		  	{
		  		if(rxBuff[1] <= MAX_LEDS){
		  			settings.numleds = rxBuff[1];
		  			WS2812B_SetNumLeds(&myled, settings.numleds);
		  		}
		  		break;
		  	}
		  	case SET_WIFI_SETTENGS:
		  	{
		  		for(int i = 1; i < sizeof(settings.ssidSTA); i++)
		  			settings.ssidSTA[i - 1] = rxBuff[i];
		  		for(int i = 1; i < sizeof(settings.passSTA); i++)
		  			settings.passSTA[i - 1] = rxBuff[i + sizeof(settings.ssidSTA)];

		  		FlashPROM_Write((void*)&settings);
		  		HAL_Delay(5);
		  		__set_FAULTMASK(1);
		  		NVIC_SystemReset();
		  		break;
		  	}
		  	case SET_AP_SETTINGS:
		  	{
		  		for(int i = 1; i < sizeof(settings.ssidAP); i++)
		  			settings.ssidAP[i - 1] = rxBuff[i];
		  		for(int i = 1; i < sizeof(settings.passAP); i++)
		  			settings.passAP[i - 1] = rxBuff[i + sizeof(settings.ssidAP)];

		  		FlashPROM_Write((void*)&settings);
		  		HAL_Delay(5);
		  		__set_FAULTMASK(1);
		  		NVIC_SystemReset();
		  		break;
		  	}
		  	case SET_ON_OFF:
		  	{
		  		settings.onOff = !settings.onOff;
		  		if(!settings.onOff){
		  			for(int i = 0; i < settings.numleds; i++)
		  				WS2812B_SetPixelRGB(&myled, 0, 0, 0, i);
		  			WS2812B_MakeEffect(&myled, EFFECT_NONE, settings.effectDelay);
		  			WS2812B_Show(&myled);
		  			FlashPROM_Write((void*)&settings);
		  			HAL_Delay(5);
		  		}
		  		break;
		  	}
		  	}
		  	memset(rxBuff, 0, RX_BUFF_SIZE);
		  	autosaveTimer = HAL_GetTick();
		  	dataReceivedFlag = 0;
	  }
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T3_TRGO;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_71CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 90-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 4500-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

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
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
  /* DMA1_Channel5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
