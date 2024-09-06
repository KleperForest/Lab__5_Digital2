/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#define F_CPU 16000000
#include "main.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <stdint.h>
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

/* USER CODE BEGIN PV */
	volatile uint8_t Player1 = 0;// Variables de contadores de los jugadores
	volatile uint8_t Player2 = 0;
	const uint8_t time_table = 5; // Delay para mux


	//Banderas para Push Botton
	bool Bandera1 = false;// PARA BOTON 1
	bool Bandera2 = false;// PARA BOTON 2
	bool Bandera3 = false;// PARA BOTON 3

	bool FLAG = false;// PARA FIN DE PARTIDA

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void Tab_Swithc(void);// Tabla de 16 Led para contadores
void Semaforo(void);// Semaforo por un led RGB
void BTN(void);// lECTURA Y ACCION DE LOS BOTONES DE JUGADORES
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  Semaforo();// INICIA SEMAFORO

	  while(FLAG){// INICIA JUEGO
	  BTN();// Botones de Players
	  Tab_Swithc();// Contador con mux
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, RED_Pin|GREEN_Pin|BLUE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, S3_Pin|Control_Pin|S0_Pin|S1_Pin
                          |S2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, Winner2_Pin|Winner1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : BTN1_Pin BTN2_Pin BTN3_Pin */
  GPIO_InitStruct.Pin = BTN1_Pin|BTN2_Pin|BTN3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : RED_Pin GREEN_Pin BLUE_Pin */
  GPIO_InitStruct.Pin = RED_Pin|GREEN_Pin|BLUE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : S3_Pin Control_Pin S0_Pin S1_Pin
                           S2_Pin */
  GPIO_InitStruct.Pin = S3_Pin|Control_Pin|S0_Pin|S1_Pin
                          |S2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : Winner2_Pin Winner1_Pin */
  GPIO_InitStruct.Pin = Winner2_Pin|Winner1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
// Rutinas propias
	Semaforo(){
	if (HAL_GPIO_ReadPin(GPIOC, BTN3_Pin) == GPIO_PIN_RESET) { /// Se dectecta que se presiono boton pull up estado 0


				  Bandera3 = true;
					  while(Bandera3){
						  if (HAL_GPIO_ReadPin(GPIOC, BTN3_Pin) == GPIO_PIN_SET){// Se espera que camibe de estado de 0 a 1
							  Bandera3 = false;}
					  }

					  // Comienza el semaforo
					  HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, 0);
					  HAL_GPIO_WritePin(BLUE_GPIO_Port, BLUE_Pin, 0);
					  HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, 1);
					  HAL_Delay(1000);

					  HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, 0);
					  HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, 0);
					  HAL_GPIO_WritePin(BLUE_GPIO_Port, BLUE_Pin, 1);
					  HAL_Delay(3000);

					  HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, 0);
					  HAL_GPIO_WritePin(BLUE_GPIO_Port, BLUE_Pin, 0);
					  HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, 1);
					  HAL_Delay(500);

					  HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, 0);
					  HAL_GPIO_WritePin(BLUE_GPIO_Port, BLUE_Pin, 0);
					  HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, 0);

					  FLAG = true; // Permite el paso a los push de jugadores
					  Player1 = 0;
					  Player2 = 0;

					  HAL_Delay(10);


					}
	}

	BTN(){

		// Contador Jugador 1
		if (HAL_GPIO_ReadPin(GPIOC, BTN1_Pin) == GPIO_PIN_RESET) {
			  Player1++;
			  Bandera1 = true;
			  	  while(Bandera1){
			  		  if (HAL_GPIO_ReadPin(GPIOC, BTN1_Pin) == GPIO_PIN_SET){
			  			  Bandera1 = false;
			  		  }
			  	  }
			  }
		// Contador Jugador 2
		if (HAL_GPIO_ReadPin(GPIOC, BTN2_Pin) == GPIO_PIN_RESET) {
			  Player2++;
			  Bandera2 = true;
				  while(Bandera2){
					  if (HAL_GPIO_ReadPin(GPIOC, BTN2_Pin) == GPIO_PIN_SET){
						  Bandera2 = false;
				  }
			  }
		  }
		// Siguiente apartado determina ganador, y permite una nueva partida
	  if (Player1 > 8){
		  HAL_GPIO_WritePin(Control_GPIO_Port, Control_Pin, 0);// Se apagan las led del contador
		  HAL_GPIO_WritePin(Winner1_GPIO_Port, Winner1_Pin, 1);// Se prender el led ganador
		  Player1 = 0;
		  Player2 = 0;
		  // Esperar a que se presione el boton start para comencar una nueva partida
		  if (HAL_GPIO_ReadPin(GPIOC, BTN3_Pin) == GPIO_PIN_SET) {

			  Bandera3 = true;
				  while(Bandera3){
					  if (HAL_GPIO_ReadPin(GPIOC, BTN3_Pin) == GPIO_PIN_RESET){
						  Bandera3 = false;}
				  }
			}

		  HAL_GPIO_WritePin(Winner1_GPIO_Port, Winner1_Pin, 0);// Se apaga led ganador
		  FLAG = false;// Finaliza juego
		  HAL_Delay(10);
	  }
	  else if (Player2 > 8){
		  HAL_GPIO_WritePin(Control_GPIO_Port, Control_Pin, 0);// Se apagan las led del contador
		  HAL_GPIO_WritePin(Winner2_GPIO_Port, Winner2_Pin, 1);// Se prender el led ganador
		  Player1 = 0;
		  Player2 = 0;

		  // Esperar a que se presione el boton start para comencar una nueva partida
		  if (HAL_GPIO_ReadPin(GPIOC, BTN3_Pin) == GPIO_PIN_SET) {

		  			  Bandera3 = true;
		  				  while(Bandera3){
		  					  if (HAL_GPIO_ReadPin(GPIOC, BTN3_Pin) == GPIO_PIN_RESET){
		  						  Bandera3 = false;}
		  				  }
		  			}

		  HAL_GPIO_WritePin(Winner2_GPIO_Port, Winner2_Pin, 0);// Se apaga led ganador
		  FLAG = false;// Finaliza juego
		  HAL_Delay(10);
	  }


	}
	// Tabla de mux para los 16 leds, para determinar que leds se prenden. 
	Tab_Swithc(){
		// Para jugador 1
		switch (Player1) {
		        case 1:
		        	HAL_GPIO_WritePin(Control_GPIO_Port, Control_Pin, 1); // 0000_0001
		        	HAL_GPIO_WritePin(S0_GPIO_Port, S0_Pin, 1);
					HAL_GPIO_WritePin(S1_GPIO_Port, S1_Pin, 1);
					HAL_GPIO_WritePin(S2_GPIO_Port, S2_Pin, 1);
					HAL_GPIO_WritePin(S3_GPIO_Port, S3_Pin, 0);
		            break;

		        case 2:
					HAL_GPIO_WritePin(Control_GPIO_Port, Control_Pin, 1);// 0000_0010
					HAL_GPIO_WritePin(S0_GPIO_Port, S0_Pin, 0);
					HAL_GPIO_WritePin(S1_GPIO_Port, S1_Pin, 1);
					HAL_GPIO_WritePin(S2_GPIO_Port, S2_Pin, 1);
					HAL_GPIO_WritePin(S3_GPIO_Port, S3_Pin, 0);
					break;

		        case 3:
					HAL_GPIO_WritePin(Control_GPIO_Port, Control_Pin, 1);// 0000_0100
					HAL_GPIO_WritePin(S0_GPIO_Port, S0_Pin, 1);
					HAL_GPIO_WritePin(S1_GPIO_Port, S1_Pin, 0);
					HAL_GPIO_WritePin(S2_GPIO_Port, S2_Pin, 1);
					HAL_GPIO_WritePin(S3_GPIO_Port, S3_Pin, 0);
					break;

		        case 4:
					HAL_GPIO_WritePin(Control_GPIO_Port, Control_Pin, 1);// 0000_1000
					HAL_GPIO_WritePin(S0_GPIO_Port, S0_Pin, 0);
					HAL_GPIO_WritePin(S1_GPIO_Port, S1_Pin, 0);
					HAL_GPIO_WritePin(S2_GPIO_Port, S2_Pin, 1);
					HAL_GPIO_WritePin(S3_GPIO_Port, S3_Pin, 0);
					break;

		        case 5:
					HAL_GPIO_WritePin(Control_GPIO_Port, Control_Pin, 1);// 0001_0000
					HAL_GPIO_WritePin(S0_GPIO_Port, S0_Pin, 1);
					HAL_GPIO_WritePin(S1_GPIO_Port, S1_Pin, 1);
					HAL_GPIO_WritePin(S2_GPIO_Port, S2_Pin, 0);
					HAL_GPIO_WritePin(S3_GPIO_Port, S3_Pin, 0);
					break;

		        case 6:
					HAL_GPIO_WritePin(Control_GPIO_Port, Control_Pin, 1);// 0010_0000
					HAL_GPIO_WritePin(S0_GPIO_Port, S0_Pin, 0);
					HAL_GPIO_WritePin(S1_GPIO_Port, S1_Pin, 1);
					HAL_GPIO_WritePin(S2_GPIO_Port, S2_Pin, 0);
					HAL_GPIO_WritePin(S3_GPIO_Port, S3_Pin, 0);
					break;

		        case 7:
					HAL_GPIO_WritePin(Control_GPIO_Port, Control_Pin, 1);// 0100_0000
					HAL_GPIO_WritePin(S0_GPIO_Port, S0_Pin, 1);
					HAL_GPIO_WritePin(S1_GPIO_Port, S1_Pin, 0);
					HAL_GPIO_WritePin(S2_GPIO_Port, S2_Pin, 0);
					HAL_GPIO_WritePin(S3_GPIO_Port, S3_Pin, 0);
					break;

		        case 8:
					HAL_GPIO_WritePin(Control_GPIO_Port, Control_Pin, 1);// 1000_0000
					HAL_GPIO_WritePin(S0_GPIO_Port, S0_Pin, 0);
					HAL_GPIO_WritePin(S1_GPIO_Port, S1_Pin, 0);
					HAL_GPIO_WritePin(S2_GPIO_Port, S2_Pin, 0);
					HAL_GPIO_WritePin(S3_GPIO_Port, S3_Pin, 0);
					break;

		        default:
		        	HAL_GPIO_WritePin(Control_GPIO_Port, Control_Pin, 0);// 0000_0000

		    }

		HAL_Delay(time_table);

		// Para jugador 2
		switch (Player2) {
				case 1:
					HAL_GPIO_WritePin(Control_GPIO_Port, Control_Pin, 1);// 0000_0001
					HAL_GPIO_WritePin(S0_GPIO_Port, S0_Pin, 0);
					HAL_GPIO_WritePin(S1_GPIO_Port, S1_Pin, 0);
					HAL_GPIO_WritePin(S2_GPIO_Port, S2_Pin, 0);
					HAL_GPIO_WritePin(S3_GPIO_Port, S3_Pin, 1);
					break;

				case 2:
					HAL_GPIO_WritePin(Control_GPIO_Port, Control_Pin, 1);// 0000_0010
					HAL_GPIO_WritePin(S0_GPIO_Port, S0_Pin, 1);
					HAL_GPIO_WritePin(S1_GPIO_Port, S1_Pin, 0);
					HAL_GPIO_WritePin(S2_GPIO_Port, S2_Pin, 0);
					HAL_GPIO_WritePin(S3_GPIO_Port, S3_Pin, 1);
					break;

				case 3:
					HAL_GPIO_WritePin(Control_GPIO_Port, Control_Pin, 1);// 0000_0100
					HAL_GPIO_WritePin(S0_GPIO_Port, S0_Pin, 0);
					HAL_GPIO_WritePin(S1_GPIO_Port, S1_Pin, 1);
					HAL_GPIO_WritePin(S2_GPIO_Port, S2_Pin, 0);
					HAL_GPIO_WritePin(S3_GPIO_Port, S3_Pin, 1);
					break;

				case 4:
					HAL_GPIO_WritePin(Control_GPIO_Port, Control_Pin, 1);// 0000_1000
					HAL_GPIO_WritePin(S0_GPIO_Port, S0_Pin, 1);
					HAL_GPIO_WritePin(S1_GPIO_Port, S1_Pin, 1);
					HAL_GPIO_WritePin(S2_GPIO_Port, S2_Pin, 0);
					HAL_GPIO_WritePin(S3_GPIO_Port, S3_Pin, 1);
					break;

				case 5:
					HAL_GPIO_WritePin(Control_GPIO_Port, Control_Pin, 1);// 0001_0000
					HAL_GPIO_WritePin(S0_GPIO_Port, S0_Pin, 0);
					HAL_GPIO_WritePin(S1_GPIO_Port, S1_Pin, 0);
					HAL_GPIO_WritePin(S2_GPIO_Port, S2_Pin, 1);
					HAL_GPIO_WritePin(S3_GPIO_Port, S3_Pin, 1);
					break;

				case 6:
					HAL_GPIO_WritePin(Control_GPIO_Port, Control_Pin, 1);// 0010_0000
					HAL_GPIO_WritePin(S0_GPIO_Port, S0_Pin, 1);
					HAL_GPIO_WritePin(S1_GPIO_Port, S1_Pin, 0);
					HAL_GPIO_WritePin(S2_GPIO_Port, S2_Pin, 1);
					HAL_GPIO_WritePin(S3_GPIO_Port, S3_Pin, 1);
					break;

				case 7:
					HAL_GPIO_WritePin(Control_GPIO_Port, Control_Pin, 1);// 0100_0000
					HAL_GPIO_WritePin(S0_GPIO_Port, S0_Pin, 0);
					HAL_GPIO_WritePin(S1_GPIO_Port, S1_Pin, 1);
					HAL_GPIO_WritePin(S2_GPIO_Port, S2_Pin, 1);
					HAL_GPIO_WritePin(S3_GPIO_Port, S3_Pin, 1);
					break;

				case 8:
					HAL_GPIO_WritePin(Control_GPIO_Port, Control_Pin, 1);// 1000_0000
					HAL_GPIO_WritePin(S0_GPIO_Port, S0_Pin, 1);
					HAL_GPIO_WritePin(S1_GPIO_Port, S1_Pin, 1);
					HAL_GPIO_WritePin(S2_GPIO_Port, S2_Pin, 1);
					HAL_GPIO_WritePin(S3_GPIO_Port, S3_Pin, 1);
					break;

				default:
					HAL_GPIO_WritePin(Control_GPIO_Port, Control_Pin, 0);// 0000_0000

			}

		HAL_Delay(time_table);


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
