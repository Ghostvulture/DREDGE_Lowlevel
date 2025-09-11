#include "KalmanFilter.hpp"

KalmanFilter::KalmanFilter()
{
    LastP = 0.02;
    Now_P = 0;
    result = 0;
    Kg = 0;
    Q = 0.001;
    R = 0.543;
}

void KalmanFilter::Clear()
{
    LastP = 0.02;
    Now_P = 0;
    result = 0;
    Kg = 0;
    Q = 0.001;
    R = 0.543;
}

void KalmanFilter::SetKg(float kg)
{
    this->Kg = kg;
}

void KalmanFilter::SetQ(float q)
{
    this->Q = q;
}

void KalmanFilter::SetR(float r)
{
    this->R = r;
}

float KalmanFilter::Update(float input)
{
    // 预测协方差方程：k时刻系统估算协方差 = k-1时刻的系统协方差 + 过程噪声协方差
    this->Now_P = this->LastP + this->Q;

    // 卡尔曼增益方程：卡尔曼增益 = k1-1时刻系统估算协方差 / （k时刻系统估算协方差 + 观测噪声协方差）
    this->Kg = this->Now_P * (1 / (this->Now_P + this->R));
    // 更新最优值方程：k时刻状态变量的最优值 = 状态变量的预测值 + 卡尔曼增益 * （测量值 - 状态变量的预测值）
    this->result = this->result + this->Kg * (input - this->result); // 因为这一次的预测值就是上一次的输出值
    // 更新协方差方程: 本次的系统协方差付给 kfp->LastP 威下一次运算准备。
    this->LastP = (1 - this->Kg) * this->Now_P;

    return result;
}
