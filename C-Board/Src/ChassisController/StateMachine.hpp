#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include "State.hpp"

class StateMachine
{
protected:
    State *p_CurrentState;
    State *p_PreviousState;
    State *p_DefaultState;

public:
    /**
     * @brief 设置当前状态
     * @param s 当前状态指针
     */
    void SetCurrentState(State *s)
    {
        p_CurrentState = s;
    }

    /**
     * @brief 设置上一个状态
     * @param s 上一个状态指针
     */
    void SetPreviousState(State *s)
    {
        p_PreviousState = s;
    }

    /**
     * @brief 设置默认状态
     * @param s 默认状态指针
     */
    void SetDefaultState(State *s)
    {
        p_DefaultState = s;
    }
    
    State *GetDefaultState()
    {
        return p_DefaultState;
    }

    State *GetCurrentState()
    {
        return p_CurrentState;
    }

    State *GetPreviousState()
    {
        return p_PreviousState;
    }

    /**
     * @brief 初始化状态机
     */
    virtual void Init() = 0;

    /**
     * @brief 处理输入，如遥控器输入，切换状态等等
     */
    virtual void HandleInput() = 0;

    /**
     * @brief 运行状态机
     * @note 在主循环中调用
     */
    virtual void Run() = 0;

    /**
     * @brief 执行当前状态
     */
    void Update()
    {
        if (p_CurrentState)
        {
            p_CurrentState->Execute();
        }
    }

    void ChangeState(State *newState)
    {
        // 如果新状态为空，直接进入默认状态
        if (!newState)
        {
            if (!p_DefaultState)
            {
                return;
            }
            p_CurrentState = p_DefaultState;
        }
        // 如果新状态和当前状态相同，直接返回
        if (p_CurrentState == newState)
        {
            return;
        }
        // 更新当前状态和上一个状态
        p_PreviousState = p_CurrentState;
        // 执行退出当前状态
        if (p_CurrentState)
        {
            p_CurrentState->Exit();
        }
        // 进入新状态
        p_CurrentState = newState;
        if (p_CurrentState)
        {
            p_CurrentState->Enter();
        }
    }
};

#endif // STATEMACHINE_HPP
