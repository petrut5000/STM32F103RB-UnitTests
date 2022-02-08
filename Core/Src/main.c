/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "testFramework.h"
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "stdlib.h"
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
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint8_t myMSG[100] = { '\0' };
uint8_t result[10];
uint8_t passed[6] = { 'P', 'A', 'S', 'S', 'E', 'D' };
uint8_t failed[6] = { 'F', 'A', 'I', 'L', 'E', 'D' };
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
int32_t getMax(int32_t term1, int32_t term2) {
	if (term1 > term2)
		return term1;
	else
		return term2;
}

void myPrint(char *pData) {
	uint8_t MSG[255] = { '\0' };
	sprintf((char*) MSG, (char*) pData);
	HAL_UART_Transmit(&huart2, MSG, sizeof(MSG), 0xFFFF);
}

void uprints(char *pData) {
	HAL_UART_Transmit(&huart2, (uint8_t*) pData, strlen(pData), 0xF);
}

char* i32toStringDec(int32_t number) {
	char *number_string;
	int no_of_digits, prev = 0, i, j;

	for (i = 10, no_of_digits = 0;; i *= 10, no_of_digits++) {
		if ((int) number / i == 0) {
			break;
		}
	}
	no_of_digits++;

	number_string = (char*) malloc(no_of_digits + 1); // +1 for NULL
	for (i = 0, j = pow(10, no_of_digits - 1); i < no_of_digits; i++, j /= 10) {
		number_string[i] = (number / j - (prev * 10)) + 48;  // int to ascii
		prev = number / j;
	}
	number_string[i] = '\0';

	return number_string;
}

char* i32toStringHex(int32_t number) {
	char number_string[10];
	int prev = 0, i, j;
	uint32_t zweier;
	zweier = (uint32_t) number;
	///TODO Negative Berechnung

	//number_string = (char*) malloc(10);
	number_string[0] = '0';
	number_string[1] = 'x';
	for (i = 2, j = pow(16, 8 - 1); i < 10; i++, j /= 16) {
		if ((number_string[i] = zweier / j - (prev * 16)) < 0xA) {
			number_string[i] += 48; // int to ascii
		} else {
			number_string[i] += 55;
		}
		prev = zweier / j;
	}
	number_string[i] = '\0';

	return number_string;
}

void showContent(uint32_t addresse) {
	char *number_string;
	int prev = 0, i, j;

	//if (number < 0) number = 0xFFFFFFFF - number + 1;
	///TODO Negative Berechnung

	number_string = (char*) malloc(10);
	number_string[0] = '0';
	number_string[1] = 'x';
	for (i = 2, j = pow(16, 8 - 1); i < 10; i++, j /= 16) {
		if ((addresse / j - (prev * 16)) < 0xA) {
			number_string[i] = (addresse / j - (prev * 16)) + 48; // int to ascii
		} else {
			number_string[i] = (addresse / j - (prev * 16)) + 55;
		}
		prev = addresse / j;
	}
	number_string[i] = '\0';

	uprints(number_string);
}

char ugetc() {
	char in='\0';
	if (HAL_UART_Receive(&huart2, (uint8_t*) &in, 1, 10) == HAL_OK)
		return in;
	else
		return '\0';
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */
	//int32_t a=-1, b=2, c=-3, d=5;
	char eingabe[1]={'\0'};
	result[0] = UNITTEST_ASSERT_EQUAL_UINT32(2, getMax(0, 2));
	result[1] = UNITTEST_ASSERT_EQUAL_UINT32(100, getMax(100, 25));
	result[2] = UNITTEST_ASSERT_EQUAL_UINT32(32, getMax(12, 32));
	result[3] = UNITTEST_ASSERT_EQUAL_UINT32(5, getMax(1, 5));
	result[4] = UNITTEST_ASSERT_EQUAL_UINT32(-424, getMax(-424, -1201));
	result[5] = UNITTEST_ASSERT_EQUAL_UINT32(-124, getMax(-124, -54564));
	result[6] = UNITTEST_ASSERT_EQUAL_UINT32(-45, getMax(-4561, -45));
	result[7] = UNITTEST_ASSERT_EQUAL_UINT32(456, getMax(456, -8757));
	result[8] = UNITTEST_ASSERT_EQUAL_UINT32(246345, getMax(-754, 246345));
	result[9] = UNITTEST_ASSERT_EQUAL_UINT32(456, getMax(456, -245));
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
	MX_USART2_UART_Init();
	/* USER CODE BEGIN 2 */

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */
		eingabe[0] = ugetc();
		uprints(eingabe);
		//HAL_Delay(10);
		/*for (int32_t i = 0; i < sizeof(result); i++) {
		 uprints("Test ");
		 uprints(i32toStringHex(i * -10));
		 uprints(":\t");
		 uprints(i32toStringHex(i * +10));
		 uprints(":\t");
		 //showContent(&i);
		 uprints(":\t");
		 if (result[i]) {
		 uprints("PASSED");
		 } else {
		 uprints("FAILED");
		 }
		 uprints("\n");
		 }
		 uprints("\n");
		 uprints("\n");

		 HAL_Delay(500);*/

		/*
		 myPrint(huart2, "Max von a und c:");
		 myPrint(huart2, DtoZkette(getMax(a, c)));
		 HAL_Delay(1000);
		 myPrint(huart2, "\n");

		 myPrint(huart2, "Max von b und d:");
		 myPrint(huart2, DtoZkette(getMax(b, d)));
		 HAL_Delay(1000);
		 myPrint(huart2, "\n");

		 myPrint(huart2, "Max von c und d:");
		 myPrint(huart2, DtoZkette(getMax(c, d)));
		 HAL_Delay(1000);
		 myPrint(huart2, "\n");
		 myPrint(huart2, "\n");
		 myPrint(huart2, "\n");*/
		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void) {

	/* USER CODE BEGIN USART2_Init 0 */

	/* USER CODE END USART2_Init 0 */

	/* USER CODE BEGIN USART2_Init 1 */

	/* USER CODE END USART2_Init 1 */
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART2_Init 2 */

	/* USER CODE END USART2_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : B1_Pin */
	GPIO_InitStruct.Pin = B1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : LD2_Pin */
	GPIO_InitStruct.Pin = LD2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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

