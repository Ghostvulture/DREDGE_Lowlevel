#ifndef MAIXCOMM_HPP
#define MAIXCOMM_HPP
#include "bsp_usart.hpp"
#include "crc.hpp"

struct maix_comm_data_t
{
    uint8_t header;
    uint8_t Vx;
    uint8_t Vy;
    uint8_t Vw;
    uint8_t M1;
		uint8_t M2;
		uint8_t M3;
		uint8_t M4;
		uint8_t M5;
		uint8_t M6;
    uint16_t crc;
}__attribute__((packed));

union maix_comm_rx_t
{
    maix_comm_data_t data;
    uint8_t buffer[sizeof(maix_comm_data_t)];
};

#define MAIX_COMM_SIZE sizeof(maix_comm_data_t)

class MaixComm
{
public:
    maix_comm_rx_t MaixCommRx;
    void Init();
    void Update();
    static MaixComm *Instance()
    {
        static MaixComm instance;
        return &instance;
    }
private:
	uint8_t PrevReceivedData[MAIX_COMM_SIZE];
    // uint32_t channels[] = {TIM_CHANNEL_1, TIM_CHANNEL_2, TIM_CHANNEL_3, TIM_CHANNEL_4};
};
#endif
