#include "M3508.hpp"
#include "bsp_can.hpp"
#include "main.h"

/**
 * @brief M3508类的构造函数。
 * 初始化电机的控制模式、各种设定值和PID控制器。
 */
M3508::M3508()
{
    // 初始化为松开模式
    controlMode = RELAX_MODE;

    // 初始化为0
    speedSet = 0;
    positionSet = 0;
    currentSet = 0;
    maxCurrent = 16384; // 电机最大电流设定

    // 初始化电机反馈数据
    motorFeedback.speedFdb = 0;
    motorFeedback.lastSpeedFdb = 0;
    motorFeedback.positionFdb = 0;
    motorFeedback.lastPositionFdb = 0;
    motorFeedback.temperatureFdb = 0;

    // pid初始化
    speedPid.mode = PID_POSITION;
    speedPid.kp = 0.1;
    speedPid.ki = 0.0;
    speedPid.kd = 0.0;
    speedPid.maxOut = 15000;
    speedPid.maxIOut = 3;

    positionPid.mode = PID_POSITION;
    positionPid.kp = 0.1;
    positionPid.ki = 0.0;
    positionPid.kd = 0.0;
    positionPid.maxOut = 15000;
    positionPid.maxIOut = 3;
}

/**
 * @brief M6020类的析构函数。
 */
M3508::~M3508()
{
}

/**
 * @brief 设置电机输出。
 * 根据当前控制模式，计算并设置电机的当前输出。
 */
void M3508::setOutput()
{
    if (this->controlMode == SPD_MODE)
    {
        // 内环控制，速度环控制
        this->speedPid.ref = this->speedSet;
        this->speedPid.fdb = this->motorFeedback.speedFdb;
        this->speedPid.UpdateResult();

        this->currentSet = this->speedPid.result; // 根据速度PID结果设置电流
    }
    else if (this->controlMode == POS_MODE)
    {
        // 外环控制，位置环控制
        this->positionPid.ref = this->positionSet;
        this->positionPid.fdb = this->motorFeedback.positionFdb;
        this->positionPid.UpdateResult();
        this->speedSet = this->positionPid.result;

        // 内环控制，速度环控制
        this->speedPid.ref = speedSet;
        this->speedPid.fdb = this->motorFeedback.speedFdb;
        this->speedPid.UpdateResult();

        this->currentSet = this->speedPid.result; // 根据速度PID结果设置电流
    }
    else
    {
        this->currentSet = 0; // 其他情况电流设定为0
    }

    if (this->controlMode == RELAX_MODE)
    {
        this->currentSet = 0.0; // 松开模式下电流设定为0
    }

    // 限制电流输出不超过最大值
    if (currentSet > maxCurrent)
        currentSet = maxCurrent;
    else if (currentSet < -maxCurrent)
        currentSet = -maxCurrent;
}

/**
 * @brief 检查电机是否在线。
 */
M3508::MotorStateTypedef M3508::AliveCheck()
{
    if (AliveFlag == Pre_AliveFlag)
    {
        MotorState = MOTOR_OFFLINE;
    }
    else
    {
        Pre_AliveFlag = AliveFlag;
        MotorState = MOTOR_ONLINE;
    }
    return MotorState;
}

void M3508::BlockedCheck()
{
    if (motorFeedback.currentFdb > 2048)
    {
        Blocked = true; // 2.5A / 20.0A * 16384
    }
    else
    {
        Blocked = false;
    }
}
