#ifndef BSP_GPIO_HPP
#define BSP_GPIO_HPP

#include "main.h"

void GPIO_Init(void);

/**
 * @brief  获取指定GPIO口的电平状态
 * @param  
 * @return GPIO_PIN_SET / GPIO_PIN_RESET
*/
//GPIO_PinState gpio_pin_read(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#endif // _GPIO_H
