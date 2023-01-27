/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void USBRxHandler(uint8_t* buf, uint32_t len);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_LED_Pin GPIO_PIN_1
#define LCD_LED_GPIO_Port GPIOA
#define LCD_D7_Pin GPIO_PIN_2
#define LCD_D7_GPIO_Port GPIOA
#define LCD_D6_Pin GPIO_PIN_3
#define LCD_D6_GPIO_Port GPIOA
#define LCD_D5_Pin GPIO_PIN_4
#define LCD_D5_GPIO_Port GPIOA
#define LCD_D4_Pin GPIO_PIN_5
#define LCD_D4_GPIO_Port GPIOA
#define LCD_EN_Pin GPIO_PIN_6
#define LCD_EN_GPIO_Port GPIOA
#define LCD_RS_Pin GPIO_PIN_12
#define LCD_RS_GPIO_Port GPIOB
#define JTAG_EN_n_Pin GPIO_PIN_13
#define JTAG_EN_n_GPIO_Port GPIOB
#define JTAG_S0_Pin GPIO_PIN_14
#define JTAG_S0_GPIO_Port GPIOB
#define JTAG_S1_Pin GPIO_PIN_15
#define JTAG_S1_GPIO_Port GPIOB
#define BTN1_Pin GPIO_PIN_8
#define BTN1_GPIO_Port GPIOA
#define BTN2_Pin GPIO_PIN_9
#define BTN2_GPIO_Port GPIOA
#define BTN3_Pin GPIO_PIN_10
#define BTN3_GPIO_Port GPIOA
#define EN_24V_n_Pin GPIO_PIN_6
#define EN_24V_n_GPIO_Port GPIOB
#define EN_12V_n_Pin GPIO_PIN_7
#define EN_12V_n_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
typedef enum
{
    EN_VOLTAGE = 0x00,
    EN_SWITCH_SIGNAL
} SETTING_STATE;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
