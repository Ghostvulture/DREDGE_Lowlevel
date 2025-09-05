#ifndef M2006_HPP
#define M2006_HPP

#include "main.h"
#include "DJIMotor.hpp"

/**
 * @class M2006
 * @brief M2006电机的控制类，继承自Motor类。
 *
 * 这个类实现了M2006电机的控制方法，包括输出设置等。
 */
class M2006 : public DJIMotor
{
public:
    /**
     * @brief 构造函数，初始化M6020电机控制类。
     */
    M2006();

    /**
     * @brief 构造函数，初始化M6020电机控制类。
     */
    ~M2006();

    /**
     * @brief 实现电机输出设置。
     * 根据当前的控制模式和PID反馈调整电机输出。
     * 必须在派生类中具体实现此方法以适应具体电机。
     */
    void setOutput() override;

    void BlockedCheck() override;

    MotorStateTypedef AliveCheck() override;
};

#endif // M2006_HPP
