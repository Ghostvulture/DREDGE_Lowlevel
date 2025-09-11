#ifndef KALMANFILTER_HPP
#define KALMANFILTER_HPP

#include "Math.hpp"

class KalmanFilter
{
    float LastP; // 上次估算协方差 初始化值为0.02		--e(ESTk-1)  上次协方差
    float Now_P; // 当前估算协方差 初始化值为0		--预测e(ESTk)	当前估算协方差
    float result;   // 卡尔曼滤波器输出 初始化值为0
    float Kg;    // 卡尔曼增益 初始化值为0				--Kk
    float Q;     // 过程噪声协方差 初始化值为0.001
    float R;     // 观测噪声协方差 初始化值为0.543		--e(MEAk)  测量误差
public:
/**
 * @brief 构造函数，简单复制初始化，避免出现未知错误
 */
    KalmanFilter();

    /**
     * @brief 清空卡尔曼滤波器
     */
    void Clear();

    /**
     * @brief 设置卡尔曼滤波器的增益
     * @param kg 卡尔曼滤波器的增益
     * @return void
     */
    void SetKg(float kg);
    
    /**
     * @brief 设置卡尔曼滤波器的过程噪声协方差
     * @param q 过程噪声协方差
     */
    void SetQ(float q);

    /**
     * @brief 设置卡尔曼滤波器的观测噪声协方差
     */
    void SetR(float r);

    /**
     * @brief 更新卡尔曼滤波器的输出
     * @param input 卡尔曼滤波器的输入
     * @return 卡尔曼滤波器的输出
     */
    float Update(float input);

};

#endif
