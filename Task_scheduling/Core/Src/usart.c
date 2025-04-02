/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
#include "include.h"
uint8_t aRxBuffer[LENTH];
//uint8_t aTxBuffer[LENTH];
uint8_t aRxData[LENTH];
uint8_t rx_flag=0;
/* USER CODE END 0 */

UART_HandleTypeDef huart1;

/* USART1 init function */

void MX_USART1_UART_Init(void)
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
  HAL_UART_Receive_IT(&huart1,aRxBuffer,1);////////////////////////////////串口中断使能
  /* USER CODE END USART1_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 2, 0);/////////////////////////////与定时器中断优先级切勿冲突
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/* 串口输出函数 */                                            //需在魔法棒启用USB MicroLIB库
void Usart_SendString(char *str)
{
	unsigned int k=0;
  do 
  {
      HAL_UART_Transmit( &huart1,(uint8_t *)(str + k) ,1,1000);
      k++;
  } while(*(str + k)!='\0');
  
}
///重定向c库函数printf到串口DEBUG_USART，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
	/* 发送一个字节数据到串口DEBUG_USART */
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 1000);	
	
	 return (ch);
}

///重定向c库函数scanf到串口DEBUG_USART，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		
	int ch;
	HAL_UART_Receive(&huart1, (uint8_t *)&ch, 1, 1000);	
	return (ch);
}

uint32_t arxdata_count=0;
//串口中断回调函数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        while(HAL_UART_Receive_IT(&huart1,aRxBuffer,1) != HAL_OK)//等待中断接受完毕，若不等待可能导致发送与接收函数产生自锁，导致串口异常
	    {
	  	    huart1.RxState = HAL_UART_STATE_READY;
		    __HAL_UNLOCK(&huart1);//串口1解锁
		}
		rx_flag=1;//表示串口接收到数据
		for(int i=0;i<LENTH;i++)//遍历缓存区内容，将有用数据存入内容判断区
			if(aRxBuffer[i]<='z'&&aRxBuffer[i]>='!')
			{
				if(arxdata_count>=LENTH-1)
					arxdata_count=0;
				aRxData[arxdata_count]=aRxBuffer[i];
				arxdata_count++;
			}
	    
    }
}
//用于清空识别缓存区
void mem(void)
{
	memset(aRxData,'\0',LENTH);
	arxdata_count=0;	
}
//用于识别内容并回传参数
uint8_t Data_command(void)
{
	if(strstr((const char*)aRxData,(const char*)"open")!=NULL)
        return 0; 
	else if(strstr((const char*)aRxData,(const char*)"off")!=NULL)
		return 1;
	else if(strstr((const char*)aRxData,(const char*)"up")!=NULL)
		return 2;
	else if(strstr((const char*)aRxData,(const char*)"down")!=NULL)
		return 3;
	else 
		return 99;
}
//串口报错回调函数，初学无需理解
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  user_main_error("Uart Error, ErrorCode = %u\r\n", (unsigned int)(huart->ErrorCode));//串口打印错误码
  UNUSED(huart); 
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_UART_ErrorCallback could be implemented in the user file
   */ 
	uint32_t isrflags   = READ_REG(huart->Instance->SR);//手册上有讲，清错误都要先读SR
	if((__HAL_UART_GET_FLAG(huart, UART_FLAG_PE))!=RESET)
	{
			READ_REG(huart->Instance->DR);//PE清标志，第二步读DR
			__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_PE);//清标志
	}
	if((__HAL_UART_GET_FLAG(huart, UART_FLAG_FE))!=RESET)
	{
			READ_REG(huart->Instance->DR);//FE清标志，第二步读DR
			__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_FE);
	}
	
	if((__HAL_UART_GET_FLAG(huart, UART_FLAG_NE))!=RESET)
	{
			READ_REG(huart->Instance->DR);//NE清标志，第二步读DR
			__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_NE);
	}        
	
	if((__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE))!=RESET)
	{
			READ_REG(huart->Instance->CR1);//ORE清标志，第二步读CR
			__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_ORE);
	} 
	if (HAL_UART_GetError(huart) & HAL_UART_ERROR_ORE)
    __HAL_UART_FLUSH_DRREGISTER(huart);	
	if(huart->ErrorCode&HAL_UART_ERROR_ORE)
	{
		__HAL_UART_CLEAR_OREFLAG(huart);
	}
	if(__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE) != RESET)
	{
		__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_ORE); //清除溢出中断
		HAL_UART_Receive_IT(&huart1, (uint8_t *)aRxBuffer, 1);
	}
 
	if(__HAL_UART_GET_FLAG(huart, UART_FLAG_RXNE) != RESET)
	{
		__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_RXNE);
	//rebuf[num++] = USART_ReceiveData(USART2); 读取串口数据
	}
}
/* USER CODE END 1 */
