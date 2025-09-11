#include "MaixComm.hpp"

void MaixComm::Init()
{
    memset(MaixCommRx.buffer, 128, MAIX_COMM_SIZE);
	memset(PrevReceivedData, 128, MAIX_COMM_SIZE);
}

void MaixComm::Update()
{
	if (Verify_CRC16_Check_Sum((uint8_t *)&MaixCommRx.data, MAIX_COMM_SIZE))
	{
			memcpy(PrevReceivedData, &MaixCommRx.data, MAIX_COMM_SIZE);
	}
	else
	{
			memcpy(&MaixCommRx.data, PrevReceivedData, MAIX_COMM_SIZE);
	}
}
