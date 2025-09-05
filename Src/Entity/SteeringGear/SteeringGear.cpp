#include "SteeringGear.hpp"
#include <cmath>

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim8;

//初始化舵机
void SteeringGear::Init()
{
   PWM_SetPeriod(&htim1, 20.0f); // 设置PWM周期为20ms
   PWM_SetPeriod(&htim8, 20.0f); // 设置PWM周期为20ms


   PWM_Start(&htim1, TIM_CHANNEL_1);
   PWM_Start(&htim1, TIM_CHANNEL_2);
   PWM_Start(&htim1, TIM_CHANNEL_3);
   PWM_Start(&htim1, TIM_CHANNEL_4);
   PWM_Start(&htim8, TIM_CHANNEL_1);
   PWM_Start(&htim8, TIM_CHANNEL_2);
   PWM_Start(&htim8, TIM_CHANNEL_3);
}

/**
 * @brief 设置舵机角度
 * @param angle是舵机目标角度，限幅在0~180之间
 *        number用于选择PWM输出口，7个选项对应C板7个PWM输出口，具体选择取决于你的硬件连线
 */
void SteeringGear::SetAngle(int angle, int number)
{
   //限幅到0~180°之间
   if(angle > 180.0f){ angle = 180.0f;}
   else if(angle < 0.0f){ angle = 0.0f;}
   // 将角度转换为PWM占空比
   float dutyRatio = angle / 180.0f;

   switch (number)
   {
       case 1:
           PWM_SetDutyRatio(&htim1,dutyRatio,TIM_CHANNEL_1);
       case 2:
           PWM_SetDutyRatio(&htim1,dutyRatio,TIM_CHANNEL_2);
       case 3:
           PWM_SetDutyRatio(&htim1,dutyRatio,TIM_CHANNEL_3);
       case 4:
           PWM_SetDutyRatio(&htim1,dutyRatio,TIM_CHANNEL_4);
       case 5:
           PWM_SetDutyRatio(&htim8,dutyRatio,TIM_CHANNEL_1);
       case 6:
           PWM_SetDutyRatio(&htim8,dutyRatio,TIM_CHANNEL_2);
       case 7:
           PWM_SetDutyRatio(&htim8,dutyRatio,TIM_CHANNEL_3);
       default:
           return;
   }
}
