#ifndef GM6020_HPP
#define GM6020_HPP

#include "main.h"
#include "DJIMotor.hpp"

/**
 * @class GM6020
 * @brief GM6020电机的控制类，继承自GMMotor类。
 *
 * 这个类实现了GM6020电机的控制方法，包括输出设置等。
 * GM6020电机通常用于精确的运动控制和高负载应用。
 */
class GM6020 : public DJIMotor
{
public:
    /**
     * @brief 构造函数，初始化GM6020电机控制类。
     */
    GM6020();

    /**
     * @brief 构造函数，初始化GM6020电机控制类。
     */
    ~GM6020();

    float Offset;
    /**
     * @brief 实现电机输出设置。
     * 根据当前的控制模式和PID反馈调整电机输出。
     * 必须在派生类中具体实现此方法以适应具体电机。
     */
    void setOutput() override;

    void BlockedCheck() override;

    MotorStateTypedef AliveCheck() override;
};

#endif // GM6020_HPP
