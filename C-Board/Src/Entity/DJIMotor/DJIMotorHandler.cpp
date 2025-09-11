#include "DJIMotorHandler.hpp"

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

/**
 * @brief 构造函数，将所有值初始化
 */
DJIMotorHandler::DJIMotorHandler()
{
    for (int i = 0; i < 8; i++)
        DJIMotorList[0][i] = nullptr;
    for (int i = 0; i < 8; i++)
        DJIMotorList[1][i] = nullptr;

    for (int i = 0; i < 8; i++)
        can1_send_data_0[i] = 0;
    for (int i = 0; i < 8; i++)
        can1_send_data_1[i] = 0;
    for (int i = 0; i < 8; i++)
        can2_send_data_0[i] = 0;
    for (int i = 0; i < 8; i++)
        can2_send_data_1[i] = 0;
}

DJIMotorHandler::~DJIMotorHandler()
{
}

/**
 * @brief 注册电机，将电机指针存入MotorList中
 * @param motor 电机指针
 * @param hcan CAN句柄
 * @param canId 电机ID
 */
void DJIMotorHandler::registerMotor(DJIMotor *DJImotor, CAN_HandleTypeDef *hcan, uint16_t canId)
{
    DJImotor->canId = canId;
    DJImotor->hcan = hcan;

    if (canId >= 0x201 && canId <= 0x208)
    {
        if (DJImotor->hcan == &hcan1)
        {
            DJIMotorList[0][canId - 0x201] = DJImotor; // 将电机指针存入MotorList中
            // 判断电机的控制标识符，用于判断是否需要发送控制数据
            if (canId >= 0x201 && canId <= 0x204)
            {
                CAN1_0x200_Exist = true;
            }
            else if (canId >= 0x205 && canId <= 0x208)
            {
                CAN1_0x1FF_Exist = true;
            }
            return;
        }
        else if (DJImotor->hcan == &hcan2)
        {
            DJIMotorList[1][canId - 0x201] = DJImotor; // 将电机指针存入MotorList中
            // 判断电机的控制标识符，用于判断是否需要发送控制数据
            if (canId >= 0x201 && canId <= 0x204)
            {
                CAN2_0x200_Exist = true;
            }
            else if (canId >= 0x205 && canId <= 0x208)
            {
                CAN2_0x1FF_Exist = true;
            }
        }
    }
}

/**
 * @brief 发送控制数据
 * @param hcan1 CAN1句柄
 * @param hcan2 CAN2句柄
 */
void DJIMotorHandler::sendControlData()
{
    // 循环遍历所有的电机，将电机的控制数据存入can_send_data中
    //< 如果电机列表的最大数量发生变化，这里的循环次数需要修改！！！
    for (int i = 0; i < 8; i++)
    {
        // 处理挂载在CAN1的电机
        if (DJIMotorList[0][i] != nullptr)
        {
            // 0x201-0x204，控制标识符为0x200
            if (DJIMotorList[0][i]->canId >= 0x201 && DJIMotorList[0][i]->canId <= 0x204)
            {
                int index = (DJIMotorList[0][i]->canId - 0x200) * 2;
                can1_send_data_0[index - 2] = DJIMotorList[0][i]->currentSet >> 8;
                can1_send_data_0[index - 1] = DJIMotorList[0][i]->currentSet;
            }
            // 0x205-0x208，控制标识符为0x1FF
            if (DJIMotorList[0][i]->canId >= 0x205 && DJIMotorList[0][i]->canId <= 0x208)
            {
                int index = (DJIMotorList[0][i]->canId - 0x204) * 2;
                can1_send_data_1[index - 2] = DJIMotorList[0][i]->currentSet >> 8;
                can1_send_data_1[index - 1] = DJIMotorList[0][i]->currentSet;
            }
        }
        // 处理挂载在CAN2的电机
        if (DJIMotorList[1][i] != nullptr)
        {
            // 0x201-0x204，控制标识符为0x200
            if (DJIMotorList[1][i]->canId >= 0x201 && DJIMotorList[1][i]->canId <= 0x204)
            {
                int index = (DJIMotorList[1][i]->canId - 0x200) * 2;
                can2_send_data_0[index - 2] = DJIMotorList[1][i]->currentSet >> 8;
                can2_send_data_0[index - 1] = DJIMotorList[1][i]->currentSet;
            }
            // 0x205-0x208，控制标识符为0x1FF
            if (DJIMotorList[1][i]->canId >= 0x205 && DJIMotorList[1][i]->canId <= 0x208)
            {
                int index = (DJIMotorList[1][i]->canId - 0x204) * 2;
                can2_send_data_1[index - 2] = DJIMotorList[1][i]->currentSet >> 8;
                can2_send_data_1[index - 1] = DJIMotorList[1][i]->currentSet;
            }
        }
    }
    // 使用bsp_can中的函数发送数据，只应该发送有效数据，防止堵塞。
    if (CAN1_0x200_Exist)
        CAN_Transmit(&hcan1, 0x200, can1_send_data_0, 8); // 向CAN1发送数据，电机控制报文0x200
    if (CAN1_0x1FF_Exist)
        CAN_Transmit(&hcan1, 0x1FF, can1_send_data_1, 8); // 向CAN1发送数据，电机控制报文0x1FF
    if (CAN2_0x200_Exist)
        CAN_Transmit(&hcan2, 0x200, can2_send_data_0, 8); // 向CAN2发送数据，电机控制报文0x200
    if (CAN2_0x1FF_Exist)
        CAN_Transmit(&hcan2, 0x1FF, can2_send_data_1, 8); // 向CAN2发送数据，电机控制报文0x2FF
}

/**
 * @brief 处理并更新电机反馈数据
 * 将电机的反馈数据存入Motorlist中存在的电机的MotorFeedback中
 * @param hcan1 CAN1句柄
 * @param hcan2 CAN2句柄
 */
void DJIMotorHandler::updateFeedback(CAN_HandleTypeDef *hcan, uint8_t *rx_data, int index)
{
    if (hcan == &hcan1)
    {
        // 处理CAN1的电机
        if (DJIMotorList[0][index] != nullptr)
        {
            UpdateSensorData(DJIMotorList[0][index], rx_data);
        }
    }

    else if (hcan == &hcan2)
    {
        // 处理CAN2的电机
        if (DJIMotorList[1][index] != nullptr)
        {
            UpdateSensorData(DJIMotorList[1][index], rx_data);
        }
    }
}

void DJIMotorHandler::UpdateSensorData(DJIMotor *motor, uint8_t *can_data)
{
    motor->AliveFlag++;

    motor->motorFeedback.last_ecd = motor->motorFeedback.ecd;
    motor->motorFeedback.lastSpeedFdb = motor->motorFeedback.speedFdb;
    motor->motorFeedback.lastPositionFdb = motor->motorFeedback.positionFdb;

    motor->motorFeedback.ecd = (uint16_t)(can_data[0] << 8 | can_data[1]);
    motor->motorFeedback.speed_rpm = (uint16_t)(can_data[2] << 8 | can_data[3]);
    motor->motorFeedback.currentFdb = (float)(can_data[4] << 8 | can_data[5]);
    motor->motorFeedback.temperatureFdb = (float)can_data[6];

    if (motor->motorFeedback.currentFdb >= 65535)
    {
        motor->motorFeedback.currentFdb -= 65535;
    }

    switch (motor->gearBox)
    {
    case GearBox_None:
        motor->motorFeedback.speedFdb = motor->motorFeedback.speed_rpm * motor->gearRatio_Rpm2Rps.None;
        motor->motorFeedback.positionFdb = motor->motorFeedback.ecd * motor->gearRatio_Pos2Rad.None - motor->gearRatio_PI.None;
        break;

    case GearBox_M2006:
        motor->motorFeedback.speedFdb = motor->motorFeedback.speed_rpm * motor->gearRatio_Rpm2Rps.M2006;
        motor->motorFeedback.positionFdb += Math::FloatConstrain((motor->motorFeedback.ecd - motor->motorFeedback.last_ecd) * motor->gearRatio_Pos2Rad.M2006, - motor->gearRatio_PI.M2006, motor->gearRatio_PI.M2006);
        break;

    case GearBox_M3508:
        motor->motorFeedback.speedFdb = motor->motorFeedback.speed_rpm * motor->gearRatio_Rpm2Rps.M3508;
        motor->motorFeedback.positionFdb += Math::FloatConstrain((motor->motorFeedback.ecd - motor->motorFeedback.last_ecd) * motor->gearRatio_Pos2Rad.M3508, - motor->gearRatio_PI.M3508, motor->gearRatio_PI.M3508);
        break;

    case GearBox_XRoll:
        motor->motorFeedback.speedFdb = motor->motorFeedback.speed_rpm * motor->gearRatio_Rpm2Rps.XRoll;
        motor->motorFeedback.positionFdb += Math::FloatConstrain((motor->motorFeedback.ecd - motor->motorFeedback.last_ecd) * motor->gearRatio_Pos2Rad.XRoll, - motor->gearRatio_PI.XRoll, motor->gearRatio_PI.XRoll);
        break;

    default:
        break;
    }
}

/**
 * @brief 检查所有列表中存在的电机是否在线
 * @note 需要在主循环中调用
 */
void DJIMotorHandler::AllMotorAliveCheck()
{
    for (uint8_t i = 0; i < 2; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (DJIMotorList[i][j] != nullptr)
            {
                DJIMotorList[i][j]->AliveCheck();
            }
        }
    }
}

/**
 * @brief 检查所有列表中存在的电机是否堵转
 * @note 需要在主循环中调用
 */
void DJIMotorHandler::AllMotorBlockedCheck()
{
    for (uint8_t i = 0; i < 2; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (DJIMotorList[i][j] != nullptr)
            {
                DJIMotorList[i][j]->BlockedCheck();
            }
        }
    }
}
