# GPIO

开关GPIO口的函数本身很简单，所以大部分都是形式上的封装。最主要的是中断处理函数。`HAL_GPIO_EXTI_Callback`目前用于处理IST8310磁场数据。

### 需配置引脚

| 引脚 | 用途 |
| --- | --- |
| PA4 | BMI088加速度计 |
| PB0 | BMI088陀螺仪 |
| PH10-12 | LED |
| PG6 | IST8310_RSTN |
| PG3 | IST8310_DRDY |

### 其它配置使用引脚
| 引脚 | 用途 |
| --- | --- |
| PA8 | IIC_SCL |
| PC9 | IIC_SDA |
| PC10 | USART3_TX |
| PC11 | USART3_RX |