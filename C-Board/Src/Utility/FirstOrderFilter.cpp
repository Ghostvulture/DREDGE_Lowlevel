#include "FirstOrderFilter.hpp"

void FirstOrderFilter::SetInput(float in)
{
    Input = in;
}
/*
 * @brief 设置滤波器的时间常数
 */
void FirstOrderFilter::SetTau(float tau)
{
    Tau = tau;
}

/**
 * @brief 设置滤波器的输出值
 */
void FirstOrderFilter::SetResult(float out)
{
    OutPut = out;
}

/**
 * @brief 设置滤波器的更新周期
 */
void FirstOrderFilter::SetUpdatePeriod(float t)
{
    UpdatePeriod = t * 0.001f;
} /* t in ms */

/**
 * @brief 获取滤波器的输出值
 */
float FirstOrderFilter::GetResult()
{
    return OutPut;
}

/**
 * @brief 获取滤波器的输入值
 */
float FirstOrderFilter::GetTau()
{
    return Tau;
}

/**
 * @brief 获取滤波器的更新周期
 */
float FirstOrderFilter::GetUpdatePeriod()
{
    return UpdatePeriod;
}

/**
 * @brief 初始化滤波器
 */
void FirstOrderFilter::Init()
{
    Clear();
    UpdatePeriod = 0.001f;
    Tau = 0.25f;
}

/**
 * @brief 更新滤波器
 */
void FirstOrderFilter::Update()
{
    float a = UpdatePeriod / (Tau);
    OutPut = (1 - a) * OutPut + a * Input;

    if (isnan(OutPut))
    {
        OutPut = Input;
    }
}

void FirstOrderFilter::Clear()
{
    OutPut = 0;
    Input = 0;
}
