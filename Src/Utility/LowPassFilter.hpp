#ifndef MATH_LOW_PASS_FILTER_H_
#define MATH_LOW_PASS_FILTER_H_

#include <stdint.h>
#include <math.h>
#include "arm_math.h"

/*
 * @brief 二阶低通滤波器
 * @note 基于MATLAB的filterDesigner，滤波器结构：一节
 * @note 采样频率1000Hz，截止频率1Hz
 * @ref https://blog.csdn.net/qq_48919837/article/details/138919160?fromshare=blogdetail&sharetype=blogdetail&sharerId=138919160&sharerefer=PC&sharesource=Ghostvulture&sharefrom=from_link
 */
#define FILTER_ORDER 2
# define NUM_STAGE (FILTER_ORDER / 2)

class LowPassFilter_1Hz
{
private:
    float Output;
    float buff[8] = {0};
    float coeff[NUM_STAGE * 5] = {
        //b0  b1    b2    a1                                          a2
        1.0f, 2.0f, 1.0f, 1.991114292201653590552723471773788332939f, -0.99115359586893536647522751081851311028f
    };  //滤波器系数，MATLAB生成去掉a0,a1a2取反
    float gain = 0.000009825916820482034428198107878227319f;//x阶IIR滤波器，gain需要乘以（x/2）次方
    arm_biquad_casd_df1_inst_f32 S;

public:

    LowPassFilter_1Hz(){
        arm_biquad_cascade_df1_init_f32(&S, NUM_STAGE, coeff, buff);
    }

    float calculate(float _input)
    {   
        float temp;
        arm_biquad_cascade_df1_f32(&S, &_input, &temp, 1);
        temp *= gain;
        Output = temp;
        return Output;
    }

    void reset(){
        for (auto& i : buff){
            i = 0;
        }
    }

    float getOutput(){
        return Output;
    }


};

class LowPassFilter_100Hz
{
private:
    float Output;
    float buff[8] = {0};
    float coeff[NUM_STAGE * 5] = {
        //b0  b1    b2    a1                                           a2
        1.0f, 2.0f, 1.0f, 1.142980502539901133118860343529377132654f, -0.412801598096188770981029847462195903063f
    };  //滤波器系数，MATLAB生成去掉a0,a1a2取反
    float gain = 0.067455273889071895587754568168747937307f;//x阶IIR滤波器，gain需要乘以（x/2）次方
    arm_biquad_casd_df1_inst_f32 S;

public:

    LowPassFilter_100Hz(){
        arm_biquad_cascade_df1_init_f32(&S, NUM_STAGE, coeff, buff);
    }

    float calculate(float _input)
    {   
        float temp;
        arm_biquad_cascade_df1_f32(&S, &_input, &temp, 1);
        temp *= gain;
        Output = temp;
        return Output;
    }

    void reset(){
        for (auto& i : buff){
            i = 0;
        }
    }

    float getOutput(){
        return Output;
    }


};


class LowPassFilter_333Hz
{
private:
    float Output;
    float buff[8] = {0};
    float coeff[NUM_STAGE * 5] = {
        //b0  b1    b2    a1                                           a2
        1.0f, 2.0f, 1.0f, -0.617669743139197424675046477204887196422f, -0.239839843702840921357832826288358774036f
    };  //滤波器系数，MATLAB生成去掉a0,a1a2取反
    float gain = 0.464377396710509593447113729780539870262f;//x阶IIR滤波器，gain需要乘以（x/2）次方
    arm_biquad_casd_df1_inst_f32 S;

public:

    LowPassFilter_333Hz(){
        arm_biquad_cascade_df1_init_f32(&S, NUM_STAGE, coeff, buff);
    }

    float calculate(float _input)
    {   
        float temp;
        arm_biquad_cascade_df1_f32(&S, &_input, &temp, 1);
        temp *= gain;
        Output = temp;
        return Output;
    }

    void reset(){
        for (auto& i : buff){
            i = 0;
        }
    }

    float getOutput(){
        return Output;
    }


};
#endif /* MATH_FIRST_ORDER_FILTER_H_ */
