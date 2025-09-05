#ifndef M3508_HPP
#define M3508_HPP

#include "main.h"
#include "DJIMotor.hpp"

/**
 * @class M3508
 * @brief M3508电机的控制类，继承自Motor类。
 *
 * 这个类实现了M3508电机的控制方法，包括输出设置等。
 */
class M3508 : public DJIMotor
{
public:
    /**
     * @brief 构造函数，初始化GM6020电机控制类。
     */
    M3508();

    /**
     * @brief 构造函数，初始化GM6020电机控制类。
     */
    ~M3508();

    /**
     * @brief 实现电机输出设置。
     * 根据当前的控制模式和PID反馈调整电机输出。
     * 必须在派生类中具体实现此方法以适应具体电机。
     */
    void setOutput() override;

    void BlockedCheck() override;

    MotorStateTypedef AliveCheck() override;
};

#endif // M3508_HPP
