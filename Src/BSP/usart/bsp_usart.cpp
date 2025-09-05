#include "bsp_usart.hpp"
#include "stm32f4xx_it.h"
#include "MaixComm.hpp"
/*------------全局变量------------*/
extern UART_HandleTypeDef huart6;
extern DMA_HandleTypeDef hdma_usart6_rx;
extern DMA_HandleTypeDef hdma_usart6_tx;

#define RXBUFFERSIZE 1
#define TXBUFFERSIZE 128

uint8_t UART6RxBuffer[MAIX_COMM_SIZE] = {0};
// uint8_t UART6RxBuffer = 0;
uint8_t UART6TxBuffer[TXBUFFERSIZE];

void USART_Init(void)
{
  USART6_Init();
}

// USART6初始化，用于和裁判系统通信，收发数据
void USART6_Init()
{
  HAL_UART_Receive_IT(&huart6, UART6RxBuffer, MAIX_COMM_SIZE); 
}

void USART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, enum USART_Mode mode)
{
  memcpy(UART6TxBuffer, pData, Size);
  switch (mode)
  {
  case USART_MODE_BLOCK:
    HAL_UART_Transmit(huart, UART6TxBuffer, Size, 100);
    break;
  case USART_MODE_DMA:
    HAL_UART_Transmit_DMA(huart, UART6TxBuffer, Size);
    break;
  case USART_MODE_IT:
    break;
  default:
    break;
  }
  
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
}

/**
 * @brief 串口接受回调函数
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART6)
  {
    memcpy(MaixComm::Instance()->MaixCommRx.buffer, UART6RxBuffer, MAIX_COMM_SIZE); // 将接收到的数据放入队列中
    HAL_UART_Receive_IT(&huart6, UART6RxBuffer, MAIX_COMM_SIZE); // 重新开启接收中断
  }
}

/**
  * @brief This function handles USART6 global interrupt.
  */
void USART6_IRQHandler(void)
{
  /* USER CODE BEGIN USART6_IRQn 0 */

  /* USER CODE END USART6_IRQn 0 */
  HAL_UART_IRQHandler(&huart6);
  /* USER CODE BEGIN USART6_IRQn 1 */

  /* USER CODE END USART6_IRQn 1 */
}

/**
 * @brief 串口空闲中断回调函数
 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{}
