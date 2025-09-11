#ifndef QUEUE_HPP
#define QUEUE_HPP

template<typename Type, uint32_t Max_Size = 256>
class Queue
{
public:
    void Init();
    inline uint32_t GetLength();
    inline Type GetFront();
    inline Type GetRear();
    inline void Push(Type _data);
    inline Type Pop();
    inline void Clear();
    inline bool IsEmpty();
    uint32_t Front = 0;
    uint32_t Rear = 0;
    uint32_t Length = 0;
protected:
    Type _Data[Max_Size];
};

/**
 * @brief 初始化
 *
 * @tparam Type 类型
 * @tparam Max_Size 队列长度最大值
 */
template<typename Type, uint32_t Max_Size>
void Queue<Type, Max_Size>::Init()
{
    Front = 0;
    Rear = 0;
    Length = 0;
}

/**
* @brief 获取队列长度
 *
* @tparam Type 类型
* @tparam Max_Size 队列长度最大值
* @return 队首元素
*/
template<typename Type, uint32_t Max_Size>
inline uint32_t Queue<Type, Max_Size>::GetLength()
{
    return (Length);
}

/**
* @brief 获取队首元素
 *
* @tparam Type 类型
* @tparam Max_Size 队列长度最大值
* @return 队首元素
*/
template<typename Type, uint32_t Max_Size>
inline Type Queue<Type, Max_Size>::GetFront()
{
    return (_Data[Front]);
}

/**
 * @brief 获取队尾元素
 *
 * @tparam Type 类型
 * @tparam Max_Size 队列长度最大值
 * @return 队尾元素
 */
template<typename Type, uint32_t Max_Size>
inline Type Queue<Type, Max_Size>::GetRear()
{
    return (_Data[Rear]);
}

/**
* @brief 送入队列
*
* @tparam Type 类型
* @tparam Max_Size 队列长度最大值
* @param _data 传入值
*/
template<typename Type, uint32_t Max_Size>
inline void Queue<Type, Max_Size>::Push(Type _data)
{
    if (Length == Max_Size)
    {
        return;
    }
    else
    {
        if (Length == 0)
        {
            Front = 0;
            Rear = 0;
        }
        else
        {
            Rear = (Rear + 1) % Max_Size;
        }

        _Data[Rear] = _data;
        Length++;
    }
}

/**
* @brief 弹出队列
*
* @tparam Type 类型
* @tparam Max_Size 队列长度最大值
* @return 弹出值
*/
template<typename Type, uint32_t Max_Size>
inline Type Queue<Type, Max_Size>::Pop()
{
    Type temp = _Data[Front];


    if (Length != 0)
    {
        Front = (Front + 1) % Max_Size;
        Length--;
    }

    return (temp);
}

/**
* @brief 清空队列
*
* @tparam Type 类型
* @tparam Max_Size 队列长度最大值
*/
template<typename Type, uint32_t Max_Size>
inline void Queue<Type, Max_Size>::Clear()
{
    Front = 0;
    Rear = 0;
    Length = 0;
}

/**
* @brief 判断空队列
*
* @tparam bool 类型
* @tparam Max_Size 队列长度最大值
*/
template<typename Type, uint32_t Max_Size>
inline bool Queue<Type, Max_Size>::IsEmpty()
{
    return (Length == 0);
}

#endif