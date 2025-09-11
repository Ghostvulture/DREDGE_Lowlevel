#ifndef BSP_USART_HPP
#define BSP_USART_HPP

#include "main.h"
#include "string.h"

extern uint8_t UART6RxBuffer[12];
	
enum USART_Mode
{
  USART_MODE_BLOCK = 0,
  USART_MODE_DMA = 1,
  USART_MODE_IT = 2
};

/**
 * @brief 初始化串口。
 */
void USART_Init(void);

/**
 * @brief 初始化串口6。
 * @note 串口6用于和裁判系统通信。使用DMA发送和接收。
 */
void USART6_Init(void);

/**
 * @brief 串口发送数据。
 * @param huart 指向串口句柄的指针
 * @param pData 发送的数据
 * @param Size 数据长度
 * @param mode 发送模式
 */
void USART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, enum USART_Mode mode);

/**
 * @brief 串口接收数据。
 * @param huart 指向串口句柄的指针
 * @param pData 接收数据的缓冲区
 * @param Size 数据长度
 */
void USART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

#endif //  __BSP_USART_H