/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32h5xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define NOP4()   do { __NOP(); __NOP(); __NOP(); __NOP(); } while (0)
#define NOP8()   do { NOP4(); NOP4(); } while (0)
#define NOP16()  do { NOP8(); NOP8(); } while (0)
#define NOP32()  do { NOP16(); NOP16(); } while (0)
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
#define BUS_2_Pin GPIO_PIN_2
#define BUS_2_GPIO_Port GPIOE
#define BUS_3_Pin GPIO_PIN_3
#define BUS_3_GPIO_Port GPIOE
#define BUS_4_Pin GPIO_PIN_4
#define BUS_4_GPIO_Port GPIOE
#define BUS_1_DETECT_Pin GPIO_PIN_5
#define BUS_1_DETECT_GPIO_Port GPIOE
#define BUS_2_DETECT_Pin GPIO_PIN_6
#define BUS_2_DETECT_GPIO_Port GPIOE
#define J_C_Pin GPIO_PIN_13
#define J_C_GPIO_Port GPIOC
#define J_C_EXTI_IRQn EXTI13_IRQn
#define J_A_Pin GPIO_PIN_14
#define J_A_GPIO_Port GPIOC
#define J_A_EXTI_IRQn EXTI14_IRQn
#define J_B_Pin GPIO_PIN_15
#define J_B_GPIO_Port GPIOC
#define J_B_EXTI_IRQn EXTI15_IRQn
#define J_UP_Pin GPIO_PIN_0
#define J_UP_GPIO_Port GPIOC
#define J_UP_EXTI_IRQn EXTI0_IRQn
#define J_DOWN_Pin GPIO_PIN_1
#define J_DOWN_GPIO_Port GPIOC
#define J_DOWN_EXTI_IRQn EXTI1_IRQn
#define J_LEFT_Pin GPIO_PIN_2
#define J_LEFT_GPIO_Port GPIOC
#define J_LEFT_EXTI_IRQn EXTI2_IRQn
#define J_RIGHT_Pin GPIO_PIN_3
#define J_RIGHT_GPIO_Port GPIOC
#define J_RIGHT_EXTI_IRQn EXTI3_IRQn
#define burst_40_Pin GPIO_PIN_2
#define burst_40_GPIO_Port GPIOA
#define burst_39_Pin GPIO_PIN_3
#define burst_39_GPIO_Port GPIOA
#define burst_38_Pin GPIO_PIN_4
#define burst_38_GPIO_Port GPIOC
#define burst_37_Pin GPIO_PIN_5
#define burst_37_GPIO_Port GPIOC
#define burst_36_Pin GPIO_PIN_0
#define burst_36_GPIO_Port GPIOB
#define burst_35_Pin GPIO_PIN_1
#define burst_35_GPIO_Port GPIOB
#define burst_34_Pin GPIO_PIN_2
#define burst_34_GPIO_Port GPIOB
#define burst_33_Pin GPIO_PIN_7
#define burst_33_GPIO_Port GPIOE
#define burst_32_Pin GPIO_PIN_8
#define burst_32_GPIO_Port GPIOE
#define burst_31_Pin GPIO_PIN_9
#define burst_31_GPIO_Port GPIOE
#define burst_30_Pin GPIO_PIN_10
#define burst_30_GPIO_Port GPIOE
#define burst_29_Pin GPIO_PIN_11
#define burst_29_GPIO_Port GPIOE
#define burst_28_Pin GPIO_PIN_12
#define burst_28_GPIO_Port GPIOE
#define burst_27_Pin GPIO_PIN_13
#define burst_27_GPIO_Port GPIOE
#define burst_26_Pin GPIO_PIN_14
#define burst_26_GPIO_Port GPIOE
#define burst_25_Pin GPIO_PIN_15
#define burst_25_GPIO_Port GPIOE
#define BUS_4_DETECT_Pin GPIO_PIN_10
#define BUS_4_DETECT_GPIO_Port GPIOB
#define burst_24_Pin GPIO_PIN_12
#define burst_24_GPIO_Port GPIOB
#define burst_23_Pin GPIO_PIN_13
#define burst_23_GPIO_Port GPIOB
#define burst_22_Pin GPIO_PIN_14
#define burst_22_GPIO_Port GPIOB
#define burst_21_Pin GPIO_PIN_15
#define burst_21_GPIO_Port GPIOB
#define burst_20_Pin GPIO_PIN_8
#define burst_20_GPIO_Port GPIOD
#define burst_19_Pin GPIO_PIN_9
#define burst_19_GPIO_Port GPIOD
#define burst_18_Pin GPIO_PIN_10
#define burst_18_GPIO_Port GPIOD
#define burst_17_Pin GPIO_PIN_11
#define burst_17_GPIO_Port GPIOD
#define burst_16_Pin GPIO_PIN_12
#define burst_16_GPIO_Port GPIOD
#define burst_15_Pin GPIO_PIN_13
#define burst_15_GPIO_Port GPIOD
#define burst_14_Pin GPIO_PIN_14
#define burst_14_GPIO_Port GPIOD
#define burst_13_Pin GPIO_PIN_15
#define burst_13_GPIO_Port GPIOD
#define burst_12_Pin GPIO_PIN_6
#define burst_12_GPIO_Port GPIOC
#define burst_11_Pin GPIO_PIN_7
#define burst_11_GPIO_Port GPIOC
#define burst_10_Pin GPIO_PIN_8
#define burst_10_GPIO_Port GPIOC
#define burst_9_Pin GPIO_PIN_9
#define burst_9_GPIO_Port GPIOC
#define burst_8_Pin GPIO_PIN_8
#define burst_8_GPIO_Port GPIOA
#define burst_7_Pin GPIO_PIN_9
#define burst_7_GPIO_Port GPIOA
#define burst_6_Pin GPIO_PIN_10
#define burst_6_GPIO_Port GPIOA
#define burst_5_Pin GPIO_PIN_11
#define burst_5_GPIO_Port GPIOA
#define burst_4_Pin GPIO_PIN_12
#define burst_4_GPIO_Port GPIOA
#define burst_3_Pin GPIO_PIN_10
#define burst_3_GPIO_Port GPIOC
#define burst_2_Pin GPIO_PIN_11
#define burst_2_GPIO_Port GPIOC
#define burst_1_Pin GPIO_PIN_12
#define burst_1_GPIO_Port GPIOC
#define burst_41_Pin GPIO_PIN_0
#define burst_41_GPIO_Port GPIOD
#define burst_42_Pin GPIO_PIN_1
#define burst_42_GPIO_Port GPIOD
#define burst_43_Pin GPIO_PIN_2
#define burst_43_GPIO_Port GPIOD
#define burst_44_Pin GPIO_PIN_3
#define burst_44_GPIO_Port GPIOD
#define burst_45_Pin GPIO_PIN_4
#define burst_45_GPIO_Port GPIOD
#define burst_46_Pin GPIO_PIN_5
#define burst_46_GPIO_Port GPIOD
#define burst_47_Pin GPIO_PIN_6
#define burst_47_GPIO_Port GPIOD
#define burst_48_Pin GPIO_PIN_7
#define burst_48_GPIO_Port GPIOD
#define RTS_Pin GPIO_PIN_5
#define RTS_GPIO_Port GPIOB
#define SRAM_CS_Pin GPIO_PIN_7
#define SRAM_CS_GPIO_Port GPIOB
#define INT_Pin GPIO_PIN_8
#define INT_GPIO_Port GPIOB
#define BUS_1_Pin GPIO_PIN_9
#define BUS_1_GPIO_Port GPIOB
#define BUS_3_DETECT_Pin GPIO_PIN_0
#define BUS_3_DETECT_GPIO_Port GPIOE
#define CTS_GPIO_Port GPIOB
#define CTS_Pin GPIO_PIN_6

/* USER CODE BEGIN Private defines */
extern UART_HandleTypeDef huart4;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
