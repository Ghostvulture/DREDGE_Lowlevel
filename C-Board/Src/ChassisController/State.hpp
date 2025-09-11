#ifndef State_HPP
#define State_HPP

/**
 * @class StateMachine
 * @brief 状态基类
 */
class State
{
public:
    /**
     * @brief 初始化状态机
     */
    virtual void Init() = 0;

    /**
     * @brief 进入状态时执行一次
     */
    virtual void Enter() = 0;

    /**
     * @brief 执行状态
     */
    virtual void Execute() = 0;

    /**
     * @brief 退出状态时执行一次
     */
    virtual void Exit() = 0;

    State() {};

    ~State() {};
};

#endif // StateMachine_HPP
