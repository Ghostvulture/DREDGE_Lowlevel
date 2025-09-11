#ifndef DJIMOTORHANDLER_HPP
#define DJIMOTORHANDLER_HPP

#include "main.h"

#include "bsp_can.hpp"

#include "DJIMotor.hpp"

#include "PID.hpp"
#include "Math.hpp"

#define GM6020_CAN_ID 0x1FF ///< 控制ID范围在0x205-0x208的所有电机，由于DJI6020的控制报文通常用0x1FF，所以这里用命名为DJI6020_CAN_ID，但实际上这个ID也可以控制DJI3508
#define M3508_CAN_ID 0x200 ///< 控制ID范围在0x201-0x204的所有电机

/**
 * @brief 电机控制类
 */
class DJIMotorHandler
{
public:
    /**
     *@brief 使用指针数组, 2个CAN口，每个CAN口最多8个电机
     */
    DJIMotor *DJIMotorList[2][8];

    DJIMotorHandler();
    ~DJIMotorHandler();

    /**
     * @brief CAN1接收数据，经过了初步的处理，索引对应电机ID
     */
    DJIMotor::motor_measure_t can1_receive_data[8];
    /**
     * @brief CAN2接收数据，经过了初步的处理，索引对应电机ID
     */
    DJIMotor::motor_measure_t can2_receive_data[8];

    uint8_t can1_send_data_0[8]; // CAN1电机控制数据，用于控制0x201-0x204
    uint8_t can1_send_data_1[8]; // CAN1电机控制数据，用于控制0x205-0x208

    uint8_t can2_send_data_0[8]; // CAN2电机控制数据，用于控制0x201-0x204
    uint8_t can2_send_data_1[8]; // CAN2电机控制数据，用于控制0x205-0x208

    // 四个标志位，用于判断是否需要发送控制数据
    bool CAN1_0x200_Exist = false; // CAN1是否存在控制报文为0x200电机
    bool CAN1_0x1FF_Exist = false; // CAN1是否存在控制报文为0x1FF电机
    bool CAN2_0x200_Exist = false; // CAN2是否存在控制报文为0x200电机
    bool CAN2_0x1FF_Exist = false; // CAN2是否存在控制报文为0x1FF电机

    /**
     * @brief 注册电机，将电机指针存入MotorList中
     * @param motor 电机指针
     * @param hcan CAN句柄
     * @param canId 电机ID
     */
    void registerMotor(DJIMotor *DJImotor, CAN_HandleTypeDef *hcan, uint16_t canId); // 使用指针作为参数

    /**
     * @brief 发送控制数据
     * @param hcan1 CAN1句柄
     * @param hcan2 CAN2句柄
     */
    void sendControlData();

    /**
     * @brief 处理并更新电机反馈数据
     * @param hcan1 CAN1句柄
     * @param hcan2 CAN2句柄
     */
    void updateFeedback(CAN_HandleTypeDef *hcan, uint8_t *rx_data, int index);

    void AllMotorAliveCheck();

    void AllMotorBlockedCheck();

    void UpdateSensorData(DJIMotor *motor, uint8_t *can_receive_data);

    static DJIMotorHandler *Instance()
    {
        static DJIMotorHandler instance;
        return &instance;
    }
};

#endif // DJIMOTORHANDLER_HPP
