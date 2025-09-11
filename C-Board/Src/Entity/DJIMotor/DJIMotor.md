# DJIMotor

大疆电机类

使用示例：

```c++
// 以M3508为例

M3508 aMotor;
// 初始化配置
aMotor.controlMode = GMMotor::SPD_MODE;
aMotor.speedPid = this->ChassisSpeedPid;
aMotor.positionSet = this->R_Front->motorFeedback.positionFdb;

aMotor.kp = 150.0f;
aMotor.ki = 0.0f;
aMotor.kd = 4.5f;
aMotor.maxOut = 15000;
aMotor.maxIOut = 3;

GMMotorHandler::instance()->registerMotor(&aMotor, hcan1, 0x201);

// 在主要控制逻辑中
// 设定电机
aMotor.speedSet = 10；
aMotor.setOutput();

// 主循环中
GMMotorHandler::instance()->sendControlData();
```

