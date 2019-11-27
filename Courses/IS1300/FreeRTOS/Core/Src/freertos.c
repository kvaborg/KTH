/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "semphr.h"
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
/* USER CODE BEGIN Variables */
SemaphoreHandle_t xSemaphore = NULL;
/* USER CODE END Variables */
osThreadId_t defaultTaskHandle;
osThreadId_t Blink1TaskHandle;
osThreadId_t TriggTaskHandle;
osThreadId_t UserButtonTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void Blink1(void *argument);
void Trigg(void *argument);
void UserButton(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
	xSemaphore = xSemaphoreCreateBinary();
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  const osThreadAttr_t defaultTask_attributes = {
    .name = "defaultTask",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 128
  };
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* definition and creation of Blink1Task */
  const osThreadAttr_t Blink1Task_attributes = {
    .name = "Blink1Task",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 128
  };
  Blink1TaskHandle = osThreadNew(Blink1, NULL, &Blink1Task_attributes);

  /* definition and creation of TriggTask */
  const osThreadAttr_t TriggTask_attributes = {
    .name = "TriggTask",
    .priority = (osPriority_t) osPriorityHigh,
    .stack_size = 128
  };
  TriggTaskHandle = osThreadNew(Trigg, NULL, &TriggTask_attributes);

  /* definition and creation of UserButtonTask */
  const osThreadAttr_t UserButtonTask_attributes = {
    .name = "UserButtonTask",
    .priority = (osPriority_t) osPriorityHigh,
    .stack_size = 128
  };
  UserButtonTaskHandle = osThreadNew(UserButton, NULL, &UserButtonTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	/* Infinite loop */
	for(;;)
	{
		osDelay(1);
	}
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Blink1 */
/**
 * @brief Function implementing the Blink1Task thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_Blink1 */
void Blink1(void *argument)
{
  /* USER CODE BEGIN Blink1 */
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS(100);

	// Initialize the xLasteWakeTime variable with the current time
	xLastWakeTime = xTaskGetTickCount();

	/* Infinite loop */
	for(;;)
	{
		if(xSemaphore != NULL) {
			if(xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
				HAL_GPIO_TogglePin(GPIOA, LD2_Pin); // Blink PC10
				xSemaphoreGive(xSemaphore);
			}
		}
		vTaskDelayUntil(&xLastWakeTime, xPeriod);
	}
  /* USER CODE END Blink1 */
}

/* USER CODE BEGIN Header_Trigg */
/**
 * @brief Function implementing the TriggTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_Trigg */
void Trigg(void *argument)
{
  /* USER CODE BEGIN Trigg */
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS(20); // ms to ticks

	// Initialize the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();

	/* Infinite loop */
	for(;;)
	{
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_2); // Blink PD2
		vTaskDelayUntil(&xLastWakeTime, xPeriod);
	}
  /* USER CODE END Trigg */
}

/* USER CODE BEGIN Header_UserButton */
/**
 * @brief Function implementing the UserButtonTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_UserButton */
void UserButton(void *argument)
{
  /* USER CODE BEGIN UserButton */
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS(20);

	xLastWakeTime = xTaskGetTickCount();
	/* Infinite loop */
	for(;;)
	{
		if(xSemaphore != NULL) {
			if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET && HAL_GPIO_ReadPin(LD2_GPIO_Port, LD2_Pin) == GPIO_PIN_RESET)
			{
				xSemaphoreTake(xSemaphore, 10);
			} else
			{
				xSemaphoreGive(xSemaphore);
			}
		}

		vTaskDelayUntil(&xLastWakeTime, xPeriod);
	}
  /* USER CODE END UserButton */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
