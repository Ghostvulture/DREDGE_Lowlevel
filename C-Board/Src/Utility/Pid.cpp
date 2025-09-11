#include "PID.hpp"

static void f_Trapezoid_Intergral(PID *pid)
{
    pid->iTerm = pid->ki * ((pid->err[0] + pid->err[1]) / 2.0f);
}

static void f_Derivative_On_Measurement(PID *pid)
{
    pid->dResult = pid->kd * (pid->last_fbd - pid->fdb);
}

static void f_Integral_Separation(PID *pid)
{
    // 首先判断该周期内积分项是否为积累趋势
    // 只有本次积分为积累趋势才会取消积分项
    if (pid->err[0] * pid->iResult > 0)
    {
        if (fabs(pid->err[0]) <= pid->maxOut)
            return; // 完整积分
        else
            pid->iTerm = 0; // 取消积分环节
    }
}

static void f_Changing_Integral_Rate(PID *pid)
{
    if (pid->err[0] * pid->iResult > 0)
    {
        if (fabs(pid->err[0]) <= pid->ScalarB)
            return; // 完整积分
        if (fabs(pid->err[0]) <= (pid->ScalarA + pid->ScalarB))
            // 使用线性函数过渡
            pid->iTerm *= (pid->ScalarA - fabs(pid->err[0]) + pid->ScalarB) / pid->ScalarA;
        else
            pid->iTerm = 0; // 取消积分环节
    }
}

static void f_Integral_Limit(PID *pid)
{
    float temp_Output, temp_Iout;
    temp_Iout = pid->iResult + pid->iTerm;
    temp_Output = pid->pResult + pid->iResult + pid->dResult;
    if (fabs(temp_Output) > pid->maxOut)
    {
        if (pid->err[0] * pid->iResult > 0)
        {
            // 在取消积分作用前，同样需要先判断当前周期内积分是否积累
            // 如果积分为减小趋势则不需要限制其减小
            // 原因与（三）中相同。
            pid->iTerm = 0;
        }
    }

    if (temp_Iout > pid->maxIOut || temp_Iout < -pid->maxIOut)
    {
        pid->iTerm = 0;
    }
}

static void f_PID_BlockedHandle(PID *pid)
{
   // 排除PID输出本身很小的情况
    if (abs(pid->ref) < pid->maxOut * 0.01)
        return;
	
    // 考虑到该判断策略的灵活性，0.9这个常数的选取是很灵活的
    if ((abs(pid->ref - pid->fdb) / abs(pid->ref)) > 0.8f)
    {
        // 一旦可能堵转正常计数归零
        pid->rightcount = 0;
        // 电机堵转计数
        pid->errorcount++; 
    }
    else if ((abs(pid->ref - pid->fdb) / abs(pid->ref)) < 0.2f)
    {
        pid->rightcount++;
    }

    if (pid->errorcount > 500)
    {
        // 上述现象持续一段时间则被认定为电机堵转
        pid->Motorblocked = true;
		pid->Motornormal = false;
    }
    if (pid->rightcount > 300)
    {
        // 上述现象持续一段时间则被认定为电机正常
        pid->Motorblocked = false;
        pid->Motornormal = true;
        pid->errorcount = 0;
    }
}

PID::PID() : mode(PID_POSITION),
             kp(0.0f),
             ki(0.0f),
             kd(0.0f),
             maxOut(0.0f),
             maxIOut(0.0f)
{
    fdb = last_fbd = 0.0f;
    err[0] = err[1] = err[2] = 0.0f;
    deadband = 0.0f;
    errorcount = 0;
    rightcount = 0;
    Motorblocked = false;
    Motornormal = true;
}

float max_delta = 100;
void PID::UpdateResult(void)
{
    if(ref - last_ref > max_delta)
    {
        ref = last_ref + max_delta;
    }
    else if(last_ref - ref > max_delta)
    {
        ref = last_ref - max_delta;
    }
    // 更新误差缓存
    err[2] = err[1];
    err[1] = err[0];
    err[0] = ref - fdb;

    if (fabs(err[0]) < deadband) // 死区
    {
        return;
    }

    if (mode & PID_POSITION)
    {
        pResult = kp * err[0];
        dResult = kd * (err[0] - err[1]);
        iResult += err[0];
        iResult = Math::LimitABS(iResult, maxIOut);
         // 计算输出
        result = pResult + iResult*ki + dResult;
        result = Math::LimitABS(result, maxOut);
    }
    else if (mode & PID_DELTA)
    {
        pResult = kp * (err[0] - err[1]);
        iResult = ki * err[0];
        dResult = kd * (err[0] - 2.0f * err[1] + err[2]);
         // 计算输出
        result += pResult + iResult + dResult;
        result = Math::LimitABS(result, maxOut);
    }
    

    if (mode & PID_Trapezoid_Intergral)
        f_Trapezoid_Intergral(this); // 梯形积分
    if (mode & PID_Derivative_On_Measurement)
        f_Derivative_On_Measurement(this); // 微分先行
    if (mode & PID_Integral_Separation)
        f_Integral_Separation(this); // 积分分离
    if (mode & PID_Changing_Integral_Rate)
        f_Changing_Integral_Rate(this); // 变速积分
    if (mode & PID_Integral_Limit)
        f_Integral_Limit(this); // 积分限幅

    // 堵转检测
    f_PID_BlockedHandle(this);

    // 更新反馈值缓存
    last_fbd = fdb;
    last_ref = ref;
}

void PID::Clear()
{
    last_fbd = fdb = 0.0f;
    err[0] = err[1] = err[2] = 0.0f;
    pResult = iResult = dResult = result = 0.0f;
    ref = fdb = 0.0f;
    iResult = 0.0f;
    pResult = 0.0f;
    dResult = 0.0f;

    ScalarA = 1.0f;
    ScalarB = 1.0f;
}
