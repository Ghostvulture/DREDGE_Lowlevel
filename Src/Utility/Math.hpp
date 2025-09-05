#ifndef MATH_HPP
#define MATH_HPP

#include "stm32f4xx.h"
#include "stm32f407xx.h"
#include "arm_math.h"
#include "main.h"

#include "stdint.h"
#include "stdlib.h"
#include "math.h"

namespace Math
{
#define MatAdd arm_mat_add_f32         // 定义矩阵加法
#define MatSubtract arm_mat_sub_f32    // 定义矩阵减法
#define MatMultiply arm_mat_mult_f32   // 定义矩阵乘法
#define MatTranspose arm_mat_trans_f32 // 定义矩阵转置
#define MatInverse arm_mat_inverse_f32 // 定义矩阵求逆
                                       // 若运算速度不够,可以使用q31代替f32,但是精度会降低
    typedef arm_matrix_instance_f32 mat;

#define msin(x) (arm_sin_f32(x)) // 定义正弦函数
#define mcos(x) (arm_cos_f32(x)) // 定义余弦函数

    constexpr float Pi = 3.14159265358979f;    ///< 圆周率
    constexpr float PiX2 = 6.283185307f;       ///< 2倍圆周率
    constexpr float Gravity = 9.81f;           ///< 重力加速度
    constexpr float DegreeToRad = Pi / 180.0f; ///< 角度转弧度

    /**
     * @brief 计算两个角度之间的最短角度，单位为弧度
     * @param target_rad 目标角度
     * @param current_rad 当前角度
     * @return float 最短角度
     */
    float CalculateShortestAngle(float target_rad, float current_rad);

    /**
     * @brief 循环限制浮点数的范围
     * @param input 输入值
     * @param minValue 最小值
     * @param maxValue 最大值
     * @return float 限制后的值
     */
    float LoopFloatConstrain(float input, float minValue, float maxValue);

    /**
     * @brief 限制浮点数的范围
     * @param Input 输入值
     * @param minValue 最小值
     * @param maxValue 最大值
     * @return float 限制后的值
     */
    float FloatConstrain(float Input, float minValue, float maxValue);

    /**
     * @brief 限制浮点数的绝对值
     * @param _input 输入值
     * @param _max 最大值
     * @return float 限制后的值
     */
    float LimitABS(float _input, float _max);

    /**
     * @brief 将浮点数转换为定点数
     * @param _inNum 输入浮点数
     * @param _inMin 输入最小值
     * @param _inPrecision 输入精度
     * @return uint32_t 输出定点数
     */
    uint32_t ConvertToFixed(float _inNum, float _inMin, float _inPrecision);

    /**
     * @brief 将定点数转换为浮点数
     * @param _inNum 输入定点数
     * @param _inMin 输入最小值
     * @param _inPrecision 输入精度
     * @return float 输出浮点数
     */
    float ConvertFromFixed(uint32_t _inNum, float _inMin, float _inPrecision);

    /**
     * @brief 快速计算平方根的倒数
     * @param x 输入值
     * @return float 输出值，平方根的倒数
     */
    float invSqrt(float x);

    /**
     * @brief 快速计算平方根
     * @param x 输入值
     * @return float 输出值，平方根
     */
    float Sqrt(float x);

    /**
     * @brief 计算绝对值
     */
    float abs(float x);

    /**
     * @brief 计算符号
     * @param value 输入值
     * @return float 符号，大于等于0返回1，小于0返回-1
     */
    float sign(float value);

    /**
     * @brief 死区函数
     * @param Value 输入值
     * @param minValue 最小值
     * @param maxValue 最大值
     * @return float 输出值，若在[minValue, maxValue]之间则返回0，否则返回原值
     */
    float FloatDeadband(float Value, float minValue, float maxValue);

    /**
     * @brief 限制16位整数范围
     * @param Value 输入值
     * @param minValue 最小值
     * @param maxValue 最大值
     * @return int16_t 输出值
     */
    int16_t Int16Constrain(int16_t Value, int16_t minValue, int16_t maxValue);

    /**
     * @brief 角度格式化
     * @param Ang 角度，单位为度
     * @return float 角度，范围为[-180, 180]
     */
    float ThetaFormat(float Ang);

    /**
     * @brief 浮点数四舍五入
     * @param raw 输入值
     * @return int 输出值
     */
    int FloatRounding(float raw);

    /**
     * @brief 三维向量模长
     * @param v 输入向量
     * @return float* 输出向量
     */
    float *Norm3d(float *v);

    /**
     * @brief 三维向量模长
     * @param v 输入向量
     * @return float 输出模长
     */
    float NormOf3d(float *v);

    /**
     * @brief 三维向量相加
     * @param v1 输入向量1
     * @param v2 输入向量2
     * @param res 输出向量
     */
    void Cross3d(float *v1, float *v2, float *res);

    /**
     * @brief 三维向量点乘
     * @param v1 输入向量1
     * @param v2 输入向量2
     * @return float 输出值
     */
    float Dot3d(float *v1, float *v2);

    /**
     * @brief 均值滤波,删除buffer中的最后一个元素,填入新的元素并求平均值
     * @param new_data 新数据
     * @param buf 缓冲区
     * @param len 缓冲区长度
     */
    float AverageFilter(float new_data, float *buf, uint8_t len);

    /**
     * @brief 矩阵初始化
     * @param m 矩阵指针
     * @param row 行数
     * @param col 列数
     */
    void MatInit(mat *m, uint8_t row, uint8_t col);

    /**
     * @brief 四元数转欧拉角
     */
    void QuaternionToEularAngle(float *q, float *euler);
};

#endif
