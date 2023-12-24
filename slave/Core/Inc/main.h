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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);


/* Private defines -----------------------------------------------------------*/

// OSC
#define PH0_OSC_IN_Pin GPIO_PIN_0
#define PH0_OSC_IN_GPIO_Port GPIOH
#define PH1_OSC_OUT_Pin GPIO_PIN_1
#define PH1_OSC_OUT_GPIO_Port GPIOH

// PUSHBUTTON and BOOT
#define PUSHBUTTON_Pin GPIO_PIN_0
#define PUSHBUTTON_GPIO_Port GPIOA
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB

// LED
#define LED_GREEN_Pin   GPIO_PIN_12
#define LED_ORANGE_Pin  GPIO_PIN_13
#define LED_RED_Pin     GPIO_PIN_14
#define LED_BLUE_Pin    GPIO_PIN_15
#define LED_Port GPIOD

// USB
#define VBUS_FS_Pin GPIO_PIN_9
#define VBUS_FS_GPIO_Port GPIOA
#define OTG_FS_DM_Pin GPIO_PIN_11
#define OTG_FS_DM_GPIO_Port GPIOA
#define OTG_FS_DP_Pin GPIO_PIN_12
#define OTG_FS_DP_GPIO_Port GPIOA
#define OTG_FS_ID_Pin GPIO_PIN_10
#define OTG_FS_ID_GPIO_Port GPIOA

// SPI
/*
#define SPI_NSS_Pin   GPIO_PIN_4  // PA4
#define SPI_SCK_Pin   GPIO_PIN_5  // PA5
#define SPI_MISO_Pin  GPIO_PIN_6  // PA6
#define SPI_MOSI_Pin  GPIO_PIN_7  // PA7
#define SPI_Port GPIOA
*/

#define SPI_NSS_Pin   GPIO_PIN_7  // PA4
#define SPI_SCK_Pin   GPIO_PIN_3  // PA5
#define SPI_MISO_Pin  GPIO_PIN_4  // PA6
#define SPI_MOSI_Pin  GPIO_PIN_5  // PA7
#define SPI_Port GPIOB

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
