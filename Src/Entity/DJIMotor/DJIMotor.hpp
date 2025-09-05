#ifndef DJIMOTOR_HPP
#define DJIMOTOR_HPP

#include "PID.hpp"
#include "main.h"

enum GearBox
{
    GearBox_None = 0,  ///< 无减速箱
    GearBox_M2006 = 1, ///< M2006减速箱
    GearBox_M3508 = 2, ///< M3508减速箱
    GearBox_XRoll = 3  ///< XRoll减速箱
};

/**
 * @class DJIMotor
 * @brief 电机控制类，提供电机的基本控制功能。
 *
 * 该类实现了电机的各种控制模式，包括速度、位置和基于IMU的控制。
 * 它还负责处理电机反馈数据和执行PID控制。
 */
class DJIMotor
{
public:
    /**
     * @brief 定义电机测量数据的结构体。
     * @param last_ecd 上次电机编码器的读数。
     * @param ecd 当前电机编码器的读数。
     * @param speed_rpm 电机的转速，单位为rpm。
     * @param given_current 给定的电机电流，单位为毫安。
     * @param temperate 电机的温度，单位为摄氏度。
     */
    typedef struct
    {
        int16_t last_ecd;      ///< 上次电机编码器的读数
        uint16_t ecd;          ///< 当前电机编码器的读数
        int16_t speed_rpm;     ///< 电机的转速，单位rpm
        int16_t given_current; ///< 给定的电机电流
        uint8_t temperate;     ///< 电机的温度
    } motor_measure_t;

    /**
     * @enum MotorControlModeType
     * @brief 描述电机的不同控制模式。
     */
    enum MotorControlModeType
    {
        RELAX_MODE = 0,         ///< 电机松开模式，所有输出均为0。
        SPD_MODE = 1,           ///< 速度模式，控制电机速度。
        POS_MODE = 2,           ///< 位置模式，控制电机到特定位置。
        POS_FOR_NO_SPD_MODE = 3 ///< 无速度反馈下的位置模式。
    };

    enum MotorStateTypedef
    {
        MOTOR_OFFLINE = 0,
        MOTOR_ONLINE = 1
    };

    // 位置值转换为弧度的转换因子，编码器为十三位，2^13-1 = 8191, 2*PI / 8191 (rad)，这样，当编码器的值增加或减少 1 时，它表示电机轴旋转了 2*PI / 8191 (rad)
    struct GearRatio_Pos2Rad
    {
        static constexpr float None = 0.0007669903939f;   /*!< 2Pi / 8191 */
        static constexpr float M2006 = 0.00002130788978f; /*!< 2Pi / 8191 / 36 */
        static constexpr float M3508 = 0.00003994074176f; /*!< 2Pi / 8191 / 3591 * 187 */
        static constexpr float XRoll = 0.000048658315f;   /*!< 2Pi / 8191 / 268 * 17 */
    };

    struct GearRatio_Rpm2Rps
    {
        static constexpr float None = 0.1047197551196f; /*!< 2Pi / 60 (s) */
        static constexpr float M2006 = 0.002908882087f; /*!< 2Pi / 60 / 36 */
        static constexpr float M3508 = 0.005453242609f; /*!< 2Pi / 60 * 187 / 3591 */
        static constexpr float XRoll = 0.006642670920f; /*!< 2Pi / 60 / 268 * 17 */
    };

    struct GearRatio_PI
    {
        static constexpr float None = Math::Pi;       /*!< PI */
        static constexpr float M2006 = 0.0872664826f; /*!< PI / 36 */
        static constexpr float M3508 = 0.1635972783f; /*!< PI / 3591 * 187 */
        static constexpr float XRoll = 0.1992801276f; /*!< PI / 268 * 17 */
    };

    /**
     * @struct MotorFeedBack
     * @brief 电机反馈数据的结构体，包括电机的各种物理量反馈。
     * 结构体中包含了电机的电流、速度、位置等信息，以及电机的温度等状态反馈。
     */
    struct MotorFeedBack
    {
        int16_t last_ecd;      ///< 上次电机编码器的读数
        uint16_t ecd;          ///< 当前电机编码器的读数
        int16_t speed_rpm;     ///< 电机的转速，单位rpm
        float currentFdb;    ///< 电机电流反馈
        float speedFdb;        ///< 电机当前速度反馈, 单位rad/s
        float lastSpeedFdb;    ///< 上次记录的电机速度
        float positionFdb;     ///< 电机当前位置反馈
        float lastPositionFdb; ///< 上次记录的电机位置
        float temperatureFdb;  ///< 电机温度反馈
    };

    MotorStateTypedef MotorState;
    MotorControlModeType controlMode; ///< 当前电机控制模式
    MotorFeedBack motorFeedback;      ///< 处理后的电机的反馈数据
    uint16_t canId;                   ///< 电机的CAN通信ID
    CAN_HandleTypeDef *hcan;          ///< 指向电机使用的CAN接口的指针

    PID speedPid;    ///< 速度环PID控制器
    PID positionPid; ///< 位置环PID控制器

    float speedSet;    ///< 设定的目标速度
    float positionSet; ///< 设定的目标位置，范围[-Π, Π]

    int16_t currentSet;  ///< 设定的电流输出
    uint16_t maxCurrent; ///< 最大电流限制

    uint32_t AliveFlag;
    uint32_t Pre_AliveFlag;

    bool Blocked;

    GearBox gearBox;
    GearRatio_PI gearRatio_PI;
    GearRatio_Pos2Rad gearRatio_Pos2Rad;
    GearRatio_Rpm2Rps gearRatio_Rpm2Rps;

    /**
     * @brief 纯虚函数，用于设置电机输出。
     * 必须在派生类中实现此函数。
     */
    virtual void setOutput() = 0;

    virtual void BlockedCheck() = 0;

    virtual MotorStateTypedef AliveCheck() = 0;

    /**
     * @brief 构造函数
     */
    DJIMotor()
    {
        controlMode = RELAX_MODE;

        speedSet = 0;
        positionSet = 0;
        currentSet = 0;

        maxCurrent = 0;

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
        speedPid.maxOut = 25000;
        speedPid.maxIOut = 3;

        positionPid.mode = PID_POSITION;
        positionPid.kp = 0.1;
        positionPid.ki = 0.0;
        positionPid.kd = 0.0;
        positionPid.maxOut = 25000;
        positionPid.maxIOut = 3;

        MotorState = MOTOR_OFFLINE;
    }
};

#endif // MOTOR_HPP
