#ifndef _CAN_H_
#define _CAN_H_
// support cpp
#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f4xx.h"

u8 CAN1_Mode_Init(u8 tsjw, u8 tbs2, u8 tbs1, u16 brp, u8 mode);
u8 CAN1_Send_Frame(u16 CobId, u8 Rtr, u8 Len, u8 *msg);

#ifdef __cplusplus
}
#endif

#endif