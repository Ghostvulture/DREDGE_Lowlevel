# USART

目前只使用了串口3，后续还需要使用其他串口接收裁判系统信息或者用于自定义控制器。

## USART3

开启了双DMA通道，在`usart3_init`函数中实现相关初始化，这个函数在remoteControl.c文件中被调用，传入双DMA缓存数组。在.c文件中有串口3中断服务函数`USART3_IRQHandler`的具体定义，实现Dr16信息的接收和初步处理。

