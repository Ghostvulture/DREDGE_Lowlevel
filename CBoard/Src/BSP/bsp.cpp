#include "bsp.hpp"
#include "bsp_dwt.hpp"

void bsp_init()
{
  CAN_Init();    // CAN初始化
  DWT_Init(168); // 168MHz，c板主频168MHz
  GPIO_Init();   // GPIO初始化，主要是将LED，SPI，IIC所需要的引脚初始化
  USART_Init();
}
