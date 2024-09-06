/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BTN1_Pin GPIO_PIN_0
#define BTN1_GPIO_Port GPIOC
#define BTN2_Pin GPIO_PIN_1
#define BTN2_GPIO_Port GPIOC
#define BTN3_Pin GPIO_PIN_3
#define BTN3_GPIO_Port GPIOC
#define RED_Pin GPIO_PIN_5
#define RED_GPIO_Port GPIOC
#define S3_Pin GPIO_PIN_1
#define S3_GPIO_Port GPIOB
#define Control_Pin GPIO_PIN_2
#define Control_GPIO_Port GPIOB
#define S0_Pin GPIO_PIN_13
#define S0_GPIO_Port GPIOB
#define S1_Pin GPIO_PIN_14
#define S1_GPIO_Port GPIOB
#define S2_Pin GPIO_PIN_15
#define S2_GPIO_Port GPIOB
#define GREEN_Pin GPIO_PIN_6
#define GREEN_GPIO_Port GPIOC
#define BLUE_Pin GPIO_PIN_8
#define BLUE_GPIO_Port GPIOC
#define Winner2_Pin GPIO_PIN_11
#define Winner2_GPIO_Port GPIOA
#define Winner1_Pin GPIO_PIN_12
#define Winner1_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
