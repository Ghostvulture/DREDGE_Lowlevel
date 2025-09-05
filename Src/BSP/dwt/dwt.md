在Cortex-M里面有一个外设叫DWT(DataWatchpoint andTrace)，是用于系统调试及跟踪，DWT的中文名字应该是：数据观察点触发。它的频率就是内核的主频。简单点说，就是内核时钟跳动一下，CYCCNT计数器就加1。

可以说，DWT是STM32中的隐藏的计时器，精度高，不会被中断打断。故此非常时候用于延时和计时。

使用流程：

1. DWT_Init(CPU_Freq_mHz)

   在调用任何DWT中的函数前必须初始化。

2. 之后即可使用DWT_Delay()进行延时操作。