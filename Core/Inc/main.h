/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdbool.h"
#include "stdint.h"
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
#define J_SWITCH_Pin GPIO_PIN_13
#define J_SWITCH_GPIO_Port GPIOC
#define STOP_SWITCH_Pin GPIO_PIN_14
#define STOP_SWITCH_GPIO_Port GPIOC
#define L_Switch_Pin GPIO_PIN_15
#define L_Switch_GPIO_Port GPIOC
#define CURRENT_U_Pin GPIO_PIN_0
#define CURRENT_U_GPIO_Port GPIOA
#define CURRENT_V_Pin GPIO_PIN_1
#define CURRENT_V_GPIO_Port GPIOA
#define SMotor_Encoder_Pin GPIO_PIN_2
#define SMotor_Encoder_GPIO_Port GPIOA
#define CURRENT_W_Pin GPIO_PIN_3
#define CURRENT_W_GPIO_Port GPIOA
#define SMotor_PWM_Pin GPIO_PIN_4
#define SMotor_PWM_GPIO_Port GPIOA
#define Hall_C_Pin GPIO_PIN_6
#define Hall_C_GPIO_Port GPIOA
#define Hall_B_Pin GPIO_PIN_7
#define Hall_B_GPIO_Port GPIOA
#define Hall_A_Pin GPIO_PIN_0
#define Hall_A_GPIO_Port GPIOB
#define Vin_DETECTION_Pin GPIO_PIN_1
#define Vin_DETECTION_GPIO_Port GPIOB
#define RETURN_SWITCH_Pin GPIO_PIN_2
#define RETURN_SWITCH_GPIO_Port GPIOB
#define R_Switch_Pin GPIO_PIN_10
#define R_Switch_GPIO_Port GPIOB
#define PWM_1N_Pin GPIO_PIN_13
#define PWM_1N_GPIO_Port GPIOB
#define PWM_2N_Pin GPIO_PIN_14
#define PWM_2N_GPIO_Port GPIOB
#define PWM_3N_Pin GPIO_PIN_15
#define PWM_3N_GPIO_Port GPIOB
#define PWM_1_Pin GPIO_PIN_8
#define PWM_1_GPIO_Port GPIOA
#define PWM_2_Pin GPIO_PIN_9
#define PWM_2_GPIO_Port GPIOA
#define PWM_3_Pin GPIO_PIN_10
#define PWM_3_GPIO_Port GPIOA
#define M1M2_SWITCH_Pin GPIO_PIN_11
#define M1M2_SWITCH_GPIO_Port GPIOA
#define SMotor_DIR_Pin GPIO_PIN_12
#define SMotor_DIR_GPIO_Port GPIOA
#define LED_RED_Pin GPIO_PIN_15
#define LED_RED_GPIO_Port GPIOA
#define LED_GREEN_Pin GPIO_PIN_3
#define LED_GREEN_GPIO_Port GPIOB
#define LED_ORANGE_Pin GPIO_PIN_4
#define LED_ORANGE_GPIO_Port GPIOB
#define LR_Delay_2s_Pin GPIO_PIN_5
#define LR_Delay_2s_GPIO_Port GPIOB
#define L_Limit_Pin GPIO_PIN_6
#define L_Limit_GPIO_Port GPIOB
#define R_Limit_Pin GPIO_PIN_7
#define R_Limit_GPIO_Port GPIOB
#define BUZZER_Pin GPIO_PIN_9
#define BUZZER_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
