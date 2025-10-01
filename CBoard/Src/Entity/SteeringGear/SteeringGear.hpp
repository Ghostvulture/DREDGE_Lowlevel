#ifndef STEERINGGEAR_HPP
#define STEERINGGEAR_HPP

#include "bsp_tim.hpp"
#include "Math.hpp"

class SteeringGear
{
public:
    void Init();
		void Stop();
		void Start();
    void SetAngle(int angle, int number);

    static SteeringGear *Instance()
    {
        static SteeringGear instance;
        return &instance;
    }
};

#endif