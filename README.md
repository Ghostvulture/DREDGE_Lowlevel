# DREDGE Lowlevel
## 概述
本次比赛为降低难度，主要的编程都在上层机构（MaixCam）上实现，STM32中提前烧录好能驱动轮子的代码，同学们只需要正确接线即可。

本仓库中包含

- stm32驱动程序，包含轮组电机与舵机驱动代码，鼓励各个参赛队伍自主学习并通过修改该程序提升底层控制器性能。如果需要下载器，请联系组委会。
- MaixCam双板串口通信程序API，参赛队伍需要自主实现底盘移动速度Vx,Vy,Vw以及舵机角度的计算，再使用该API发送给下板，从而驱动轮子、舵机转动。

大致的程序实现架构如图
<center><img src="doc/pic1.png"></center>

## 结构
本仓库大致结构如下，其中较为重要的文件在下方有标注，供各个队伍对提供的代码架构有一个较为清晰的认识，并能够较快的上手开发人物。

```
├── C-Board // 底层控制板程序文件夹
│   ├── Chassis.ioc
│   ├── Core
│   │   ├── Inc
│   │   │   ├── main.h
│   │   │   ├── stm32f4xx_hal_conf.h
│   │   │   └── stm32f4xx_it.h
│   │   ├── Src
│   │   │   ├── main.cpp // 主程序
│   │   │   ├── stm32f4xx_hal_msp.c
│   │   │   ├── stm32f4xx_it.c
│   │   │   ├── syscalls.c
│   │   │   ├── sysmem.c
│   │   │   └── system_stm32f4xx.c
│   │   └── Startup
│   │       └── startup_stm32f407ighx.s
│   ├── Drivers
│   │   ├── CMSIS
│   │   └── STM32F4xx_HAL_Driver
│   ├── MDK-ARM // keil生成可运行项目
│   │   ├── Chassis
│   │   ├── Chassis.uvguix.Lenovo
│   │   ├── Chassis.uvguix.LUO
│   │   ├── Chassis.uvoptx
│   │   ├── Chassis.uvprojx
│   ├── Middlewares
│   └── Src // 主要架构
│       ├── BSP
│       │   ├── bsp.cpp
│       │   ├── bsp.hpp
│       │   ├── bsp.md
│       │   ├── can
│       │   ├── dwt
│       │   ├── gpio
│       │   ├── tim
│       │   └── usart
│       ├── ChassisController
│       ├── Entity
│       │   ├── DJIMotor
│       │   ├── entity.md
│       │   ├── LED
│       │   ├── MaixComm
│       │   └── SteeringGear
│       ├── Lib
│       └── Utility
├── doc
│   └── pic1.png
├── MaixPrograms // API
│   └── uart_transmit.py
└── README.md
```
## 协议
底层控制器的设计中，采用串口与MaixCam控制板进行通信，遵循以下通讯协议。
- 波特率：115200
- 包头：0xA5
    -  包头正确，是通讯包被正确识别的第一步
- 数据帧
    - Vx, Vy, Vw : 范围在 [-3, 3] 内的浮点数