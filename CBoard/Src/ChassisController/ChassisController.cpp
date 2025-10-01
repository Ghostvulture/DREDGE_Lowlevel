#include "ChassisController.hpp"
#include "SteeringGear.hpp"
#include "MaixComm.hpp"
#include "bsp_usart.hpp"
#include "bsp_dwt.hpp"

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

float K_Q = 0.001f;
float K_R = 0.6f;
float kp = 150.0f;
float ki = 0.0f;
float kd = 4.5f;
float VKp = 1000.0f;

float LIMIT_POWER;
float POWER_NOW;
float POWER_SET;
float current_debug;
float temp_debug;
float torque_debug;
float debug_rf_spd_set;
float debug_rf_spd_fdb;
float debug_rr_spd_set;
float debug_rr_spd_fdb;
float debug_lf_spd_set;
float debug_lf_spd_fdb;
float debug_lr_spd_set;
float debug_lr_spd_fdb;
float tempspeed[4];

/**
 * @brief 初始化函数，用于挂载四个底盘电机，并设置PID参数
 */
void ChassisController::Init()
{
    /*-----------------------初始化一些基本数值-----------------------*/
    Vx = 0;
    Vy = 0;
    Vw = 0;
    RelativeAngle = 0;

    RF_speedSet = 0;
    LF_speedSet = 0;
    RR_speedSet = 0;
    LR_speedSet = 0;

    /*----------------------------PID参数----------------------------*/
    M2006SpeedPid.kp = 200.0f;
    M2006SpeedPid.ki = 0.0f;
    M2006SpeedPid.kd = 10.0f;
    M2006SpeedPid.maxOut = 25000;
    M2006SpeedPid.maxIOut = 0;

    /*----------------------------右前轮----------------------------*/
    R_Front.controlMode = DJIMotor::SPD_MODE;
    R_Front.gearBox = GearBox::GearBox_M2006;
    R_Front.speedPid = M2006SpeedPid;
    R_Front.positionSet = R_Front.motorFeedback.positionFdb;
    R_Front.positionPid.Clear();
    R_Front.speedPid.Clear();
    R_Front.setOutput();
    R_Front.currentSet = 0;
    /*----------------------------左前轮----------------------------*/
    L_Front.controlMode = DJIMotor::SPD_MODE;
    L_Front.gearBox = GearBox::GearBox_M2006;
    L_Front.speedPid = M2006SpeedPid;
    L_Front.positionSet = L_Front.motorFeedback.positionFdb;
    L_Front.positionPid.Clear();
    L_Front.speedPid.Clear();
    L_Front.setOutput();
    L_Front.currentSet = 0;
    /*----------------------------右后轮----------------------------*/
    R_Rear.controlMode = DJIMotor::SPD_MODE;
    R_Rear.gearBox = GearBox::GearBox_M2006;
    R_Rear.speedPid = M2006SpeedPid;
    R_Rear.positionSet = R_Rear.motorFeedback.positionFdb;
    R_Rear.positionPid.Clear();
    R_Rear.speedPid.Clear();
    R_Rear.setOutput();
    R_Rear.currentSet = 0;
    /*----------------------------左后轮----------------------------*/
    L_Rear.controlMode = DJIMotor::SPD_MODE;
    L_Rear.gearBox = GearBox::GearBox_M2006;
    L_Rear.speedPid = M2006SpeedPid;
    L_Rear.positionSet = L_Rear.motorFeedback.positionFdb;
    L_Rear.positionPid.Clear();
    L_Rear.speedPid.Clear();
    L_Rear.setOutput();
    L_Rear.currentSet = 0;

    /*---------------------------挂载电机---------------------------*/
    DJIMotorHandler::Instance()->registerMotor(&L_Rear, &hcan1, 0x202);
    DJIMotorHandler::Instance()->registerMotor(&L_Front, &hcan1, 0x201);
    DJIMotorHandler::Instance()->registerMotor(&R_Front, &hcan1, 0x204);
    DJIMotorHandler::Instance()->registerMotor(&R_Rear, &hcan1, 0x203);

    /*---------------------------初始化舵机---------------------------*/
    SteeringGear::Instance()->Init();
}

void ChassisController::Run()
{
    HandleInput();
    Kinematic_Inverse_Resolution(motors);

    debug_rf_spd_set = R_Front.speedPid.ref;
    debug_rf_spd_fdb = R_Front.speedPid.fdb;
    debug_rr_spd_set = R_Rear.speedPid.ref;
    debug_rr_spd_fdb = R_Rear.speedPid.fdb;
    debug_lf_spd_set = L_Front.speedPid.ref;
    debug_lf_spd_fdb = L_Front.speedPid.fdb;
    debug_lr_spd_set = L_Rear.speedPid.ref;
    debug_lr_spd_fdb = L_Rear.speedPid.fdb;
}
static uint32_t transmit_count = 0;
static uint32_t err_count = 0;
void ChassisController::HandleInput()
{
//		R_Front.speedPid.kp = 1000.0f;
//		R_Front.speedPid.ki = 2.0f;
//		R_Rear.speedPid.kp = 1000.0f;
//		R_Rear.speedPid.ki = 2.0f;
	
		transmit_count += 1;
		
		if (MaixComm::Instance()->MaixCommRx.data.header != 0xA5 || err_count >= 100){
			Vx = 0;
			Vy = 0;
			Vw = 0;
			SteeringGear::Instance()->Stop();
		}
		else{
			SteeringGear::Instance()->Start();
			Vx = (MaixComm::Instance()->MaixCommRx.data.Vx/255.0f)*6 - 3.0f; // 将速度转换为 m/s
			Vy = (MaixComm::Instance()->MaixCommRx.data.Vy/255.0f)*6 - 3.0f; // 将速度转换为 m/s
			Vw = (MaixComm::Instance()->MaixCommRx.data.Vw/255.0f)*6 - 3.0f; // 将速度转换为 rad/s
		}
    

    if (isnan(Vx) || isnan(Vy) || isnan(Vw)) // 如果出现nan错误，将速度设定值设为0
    {
        Vx = 0;
        Vy = 0;
        Vw = 0;
    }

//    // 一阶卡尔曼滤波
    Vx = VxFilter.Update(Vx);
    Vy = VyFilter.Update(Vy);
    Vw = VwFilter.Update(Vw);

    //设置舵机角度
    float M1 = ((float)MaixComm::Instance()->MaixCommRx.data.M1/255.0f)*180; //将角度转换为0~180°之间
    float M2 = ((float)MaixComm::Instance()->MaixCommRx.data.M2/255.0f)*180;
    float M3 = ((float)MaixComm::Instance()->MaixCommRx.data.M3/255.0f)*180;
    float M4 = ((float)MaixComm::Instance()->MaixCommRx.data.M4/255.0f)*180;
    float M5 = ((float)MaixComm::Instance()->MaixCommRx.data.M5/255.0f)*180;
    float M6 = ((float)MaixComm::Instance()->MaixCommRx.data.M6/255.0f)*180;
    SteeringGear::Instance()->SetAngle(M1, 1);
    SteeringGear::Instance()->SetAngle(M2, 2);
    SteeringGear::Instance()->SetAngle(M3, 3);
    SteeringGear::Instance()->SetAngle(M4, 4);
    SteeringGear::Instance()->SetAngle(M5, 5);
    SteeringGear::Instance()->SetAngle(M6, 6);

    if (transmit_count % 500 == 0){
        uart_received = false;
    }

    if (!uart_received)
    {
        err_count ++;
    }
	else
    {
        err_count = 0;
    }
}

void ChassisController::Kinematic_Inverse_Resolution(M2006 *motors[])
{
    float tmp_Speed;
    for (uint8_t i = 0; i < 4; i++)
    {
        tmp_Speed = Vx * arm_cos_f32(Math::Pi * 0.75f - RelativeAngle + Math::Pi * 0.5f * i) + Vy * arm_cos_f32(Math::Pi * 0.25f - RelativeAngle + Math::Pi * 0.5f * i) - Vw;
        tmp_Speed = std::round(tmp_Speed * 10.0f) / 10.0f;
        tempspeed[i] = tmp_Speed;
        motors[i]->speedSet = tmp_Speed / wheelRadius;
        motors[i]->setOutput();
    }
}
