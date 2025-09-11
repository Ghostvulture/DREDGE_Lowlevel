#ifndef MATH_FIRST_ORDER_FILTER_H_
#define MATH_FIRST_ORDER_FILTER_H_

#include <stdint.h>
#include <math.h>
#include "arm_math.h"

class FirstOrderFilter
{
private:
    float Input;        // 设置滤波器的输入值
    float OutPut;       // 设置滤波器的输出值
    float Tau;          // 设置滤波器的时间常数
    float UpdatePeriod; // 设置滤波器的更新周期，单位为秒，但是设置时以毫秒为单位

public:
    /**
     * @brief 设置滤波器的输入值
     */
    void SetInput(float in);

    /*
     * @brief 设置滤波器的时间常数
     */
    void SetTau(float tau);

    /**
     * @brief 设置滤波器的输出值
     */
    void SetResult(float out);

    /**
     * @brief 设置滤波器的更新周期
     */
    void SetUpdatePeriod(float t);

    /**
     * @brief 获取滤波器的输出值
     */
    float GetResult();

    /**
     * @brief 获取滤波器的输入值
     */
    float GetTau();

    /**
     * @brief 获取滤波器的更新周期
     */
    float GetUpdatePeriod();

    /**
     * @brief 初始化滤波器
     */
    void Init();

    /**
     * @brief 更新滤波器
     */
    void Update();

    void Clear();
};

#endif /* MATH_FIRST_ORDER_FILTER_H_ */
