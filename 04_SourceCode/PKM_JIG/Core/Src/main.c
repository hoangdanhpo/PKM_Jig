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
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "CLCD.h"
#include "string.h"
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
TIM_HandleTypeDef htim3;

/* USER CODE BEGIN PV */
CLCD_Name     LCD1;                 /* Create LCD*/
SETTING_STATE enl_setting_state;    /* System state: SETTING or RUNNING */
uint8_t u1l_LCD_pos_Vol[3][2] =
{
  { 1U, 1U},
  { 1U, 2U},
  { 1U, 3U}
}; /* Postion of option on LCD (x,y)*/
uint8_t u1l_LCD_pos_Sig[4][2] =
{
  { 1U, 1U},
  { 1U, 2U},
  { 9U, 1U},
  { 9U, 2U}
}; /* Postion of option on LCD (x,y)*/
uint8_t u1l_LCD_pos_cur;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */
void clear_LCD_pos(void);
void f_display_voltage(void);
void f_display_sw_signal(void);
void f_clr_pos_lcd(uint8_t u1l_LCD_pos[][2]);
void f_pos_lcd(uint8_t u1l_LCD_pos[][2] ,uint8_t row);
void f_voltage_0V(void);
void f_voltage_12V(void);
void f_voltage_24V(void);
void f_active_sw(void);
void f_deactive_sw(void);
void f_active_ST(void);
void f_active_BLE(void);
void f_active_UWB(void);
void f_sw_signal_not_use(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void USBRxHandler(uint8_t* buf, uint32_t len)
{
	if (strncmp(buf,"0",len) == 0)
	{
		f_voltage_0V();
	}
	if (strncmp(buf,"1",len) == 0)
	{
		f_voltage_12V();
	}
	else if (strncmp(buf,"2",len) == 0)
	{
		f_voltage_24V();
	}
	else if (strncmp(buf,"3",len) == 0)
	{
		f_active_ST();
	}
	else if (strncmp(buf,"4",len) == 0)
	{
		f_active_BLE();
	}
	else if (strncmp(buf,"5",len) == 0)
	{
		f_active_UWB();
	}
	else if (strncmp(buf,"6",len) == 0)
	{
		f_sw_signal_not_use();
	}

	return;
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
  MX_TIM3_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
  /* ADJ for LCD */
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, 50);

  /* Enable LCD */
  HAL_GPIO_WritePin(LCD_LED_GPIO_Port, LCD_LED_Pin, GPIO_PIN_SET);

  /* Init LCD */
  CLCD_4BIT_Init(&LCD1, 20, 4, LCD_RS_GPIO_Port, LCD_RS_Pin, LCD_EN_GPIO_Port, LCD_EN_Pin,
                  LCD_D4_GPIO_Port, LCD_D4_Pin, LCD_D5_GPIO_Port, LCD_D5_Pin,
                  LCD_D6_GPIO_Port, LCD_D6_Pin, LCD_D7_GPIO_Port, LCD_D7_Pin);

  /* Init setting for system*/
  enl_setting_state = EN_VOLTAGE;
  u1l_LCD_pos_cur = 0U;
  f_display_voltage();
  f_voltage_0V();
  f_deactive_sw();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
          //CDC_Transmit_FS(myString1,strlen((const char*)myString1));
          switch (enl_setting_state)
          {
          case EN_VOLTAGE:

            if (HAL_GPIO_ReadPin(BTN3_GPIO_Port, BTN3_Pin) == 0)
            {
                HAL_Delay(5);
                if( HAL_GPIO_ReadPin(BTN3_GPIO_Port, BTN3_Pin) == 0)
                {
                    u1l_LCD_pos_cur++;
                    if (u1l_LCD_pos_cur > 2)
                    {
                      u1l_LCD_pos_cur = 0;
                    }
                    else
                    {
                      /* do nothing */
                    }
                    f_pos_lcd(u1l_LCD_pos_Vol, u1l_LCD_pos_cur);
                    switch (u1l_LCD_pos_cur)
                    {
                      case 0:
                        f_voltage_0V();
                        break;
                      case 1:
                        f_voltage_12V();
                        break;
                      case 2:
                        f_voltage_24V();
                        break;
                    }
                    while(HAL_GPIO_ReadPin(BTN3_GPIO_Port, BTN3_Pin) == 0);
                }
            }
            if (HAL_GPIO_ReadPin(BTN2_GPIO_Port, BTN2_Pin) == 0)
            {
                HAL_Delay(5);
                if( HAL_GPIO_ReadPin(BTN2_GPIO_Port, BTN2_Pin) == 0)
                {
                    enl_setting_state = EN_SWITCH_SIGNAL;
                    u1l_LCD_pos_cur = 0U;
                    f_active_sw();
                    CLCD_Clear(&LCD1);
                    f_display_sw_signal();
                    while(HAL_GPIO_ReadPin(BTN2_GPIO_Port, BTN2_Pin) == 0);
                }
            }
						break;

          case EN_SWITCH_SIGNAL:

            if (HAL_GPIO_ReadPin(BTN3_GPIO_Port, BTN3_Pin) == 0)
            {
                HAL_Delay(5);
                if( HAL_GPIO_ReadPin(BTN3_GPIO_Port, BTN3_Pin) == 0)
                {
                    u1l_LCD_pos_cur++;
                    if (u1l_LCD_pos_cur > 3)
                    {
                      u1l_LCD_pos_cur = 0;
                    }
                    else
                    {
                      /* do nothing */
                    }
                    f_pos_lcd(u1l_LCD_pos_Sig, u1l_LCD_pos_cur);
                    switch (u1l_LCD_pos_cur)
                    {
                      case 0:
                        f_active_ST();
                        break;
                      case 1:
                        f_active_BLE();
                        break;
                      case 2:
                        f_active_UWB();
                        break;
                      case 3:
                        f_sw_signal_not_use();
                        break;
                    }
                    while(HAL_GPIO_ReadPin(BTN3_GPIO_Port, BTN3_Pin) == 0);
                }
            }
            if (HAL_GPIO_ReadPin(BTN2_GPIO_Port, BTN2_Pin) == 0)
            {
                HAL_Delay(5);
                if( HAL_GPIO_ReadPin(BTN2_GPIO_Port, BTN2_Pin) == 0)
                {
                    enl_setting_state = EN_VOLTAGE;
                    u1l_LCD_pos_cur = 0U;
										f_voltage_0V();
                    f_deactive_sw();
                    CLCD_Clear(&LCD1);
                    f_display_voltage();
                    while(HAL_GPIO_ReadPin(BTN2_GPIO_Port, BTN2_Pin) == 0);
                }
            }
            break;

          default:
            break;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
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

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 7199;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 99;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LCD_LED_Pin|LCD_D7_Pin|LCD_D6_Pin|LCD_D5_Pin
                          |LCD_D4_Pin|LCD_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_RS_Pin|JTAG_EN_n_Pin|JTAG_S0_Pin|JTAG_S1_Pin
                          |EN_12V_n_Pin|EN_24V_n_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LCD_LED_Pin LCD_D7_Pin LCD_D6_Pin LCD_D5_Pin
                           LCD_D4_Pin LCD_EN_Pin */
  GPIO_InitStruct.Pin = LCD_LED_Pin|LCD_D7_Pin|LCD_D6_Pin|LCD_D5_Pin
                          |LCD_D4_Pin|LCD_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_RS_Pin JTAG_EN_n_Pin JTAG_S0_Pin JTAG_S1_Pin
                           EN_12V_n_Pin EN_24V_n_Pin */
  GPIO_InitStruct.Pin = LCD_RS_Pin|JTAG_EN_n_Pin|JTAG_S0_Pin|JTAG_S1_Pin
                          |EN_12V_n_Pin|EN_24V_n_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : BTN1_Pin BTN2_Pin BTN3_Pin */
  GPIO_InitStruct.Pin = BTN1_Pin|BTN2_Pin|BTN3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void f_display_voltage(void)
{
  CLCD_SetCursor(&LCD1, 0, 0);
  CLCD_WriteString(&LCD1,"Select Voltage");
  CLCD_SetCursor(&LCD1, 3, 1);
  CLCD_WriteString(&LCD1,"0V");
  CLCD_SetCursor(&LCD1, 3, 2);
  CLCD_WriteString(&LCD1,"12V");
	CLCD_SetCursor(&LCD1, 3, 3);
  CLCD_WriteString(&LCD1,"24V");
  f_pos_lcd(u1l_LCD_pos_Vol, 0);
}
void f_display_sw_signal(void)
{
  CLCD_SetCursor(&LCD1, 0, 0);
  CLCD_WriteString(&LCD1,"Switch signal");
  CLCD_SetCursor(&LCD1, 3, 1);
  CLCD_WriteString(&LCD1,"ST uC");
  CLCD_SetCursor(&LCD1, 11, 1);
  CLCD_WriteString(&LCD1,"BLE");
  CLCD_SetCursor(&LCD1, 3, 2);
  CLCD_WriteString(&LCD1,"UWB");
  CLCD_SetCursor(&LCD1, 11, 2);
  CLCD_WriteString(&LCD1,"Not use");
  f_pos_lcd(u1l_LCD_pos_Sig, 0);
}

void f_clr_pos_lcd(uint8_t u1l_LCD_pos[][2])
{
  uint8_t len;
  if (enl_setting_state == EN_VOLTAGE)
  {
    len = 3U;
  }
  else
  {
    len = 4U;
  }
  for (uint8_t i = 0U; i < len; i++)
  {
    CLCD_SetCursor(&LCD1, u1l_LCD_pos[i][0],u1l_LCD_pos[i][1] );
    CLCD_WriteString(&LCD1," ");
  }
}

void f_pos_lcd(uint8_t u1l_LCD_pos[][2],uint8_t row)
{
    f_clr_pos_lcd(u1l_LCD_pos);
    CLCD_SetCursor(&LCD1, u1l_LCD_pos[row][0],u1l_LCD_pos[row][1] );
    CLCD_WriteString(&LCD1,">");
}

void f_voltage_0V(void)
{
    HAL_GPIO_WritePin(EN_12V_n_GPIO_Port, EN_12V_n_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(EN_24V_n_GPIO_Port, EN_24V_n_Pin, GPIO_PIN_RESET);
}

void f_voltage_12V(void)
{
    HAL_GPIO_WritePin(EN_12V_n_GPIO_Port, EN_12V_n_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(EN_24V_n_GPIO_Port, EN_24V_n_Pin, GPIO_PIN_RESET);
}

void f_voltage_24V(void)
{
    HAL_GPIO_WritePin(EN_12V_n_GPIO_Port, EN_12V_n_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(EN_24V_n_GPIO_Port, EN_24V_n_Pin, GPIO_PIN_SET);
}

void f_active_sw(void)
{
    HAL_GPIO_WritePin(JTAG_EN_n_GPIO_Port, JTAG_EN_n_Pin, GPIO_PIN_RESET);
}

void f_deactive_sw(void)
{
    /*T.B.D*/
    HAL_GPIO_WritePin(JTAG_EN_n_GPIO_Port, JTAG_EN_n_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(JTAG_S0_GPIO_Port, JTAG_S0_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(JTAG_S1_GPIO_Port, JTAG_S1_Pin, GPIO_PIN_RESET);
}

void f_active_ST(void)
{
    HAL_GPIO_WritePin(JTAG_S0_GPIO_Port, JTAG_S0_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(JTAG_S1_GPIO_Port, JTAG_S1_Pin, GPIO_PIN_RESET);
}

void f_active_BLE(void)
{
    HAL_GPIO_WritePin(JTAG_S0_GPIO_Port, JTAG_S0_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(JTAG_S1_GPIO_Port, JTAG_S1_Pin, GPIO_PIN_RESET);
}

void f_active_UWB(void)
{
    HAL_GPIO_WritePin(JTAG_S0_GPIO_Port, JTAG_S0_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(JTAG_S1_GPIO_Port, JTAG_S1_Pin, GPIO_PIN_SET);
}

void f_sw_signal_not_use(void)
{
    HAL_GPIO_WritePin(JTAG_S0_GPIO_Port, JTAG_S0_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(JTAG_S1_GPIO_Port, JTAG_S1_Pin, GPIO_PIN_SET);
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
