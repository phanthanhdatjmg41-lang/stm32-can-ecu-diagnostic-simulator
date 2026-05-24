#ifndef APP_CAN_H
#define APP_CAN_H

#include "stdint.h"
/*
 * app_can.h
 *
 * Module nay dung de quan ly CAN loopback.
 */

void AppCAN_Init(void);
void AppCAN_SendTestFrame(void);
void AppCAN_PollRx(void);
void AppCAN_ShowStatus(void);
void AppCAN_SendDtcFrame(void);
void AppCAN_SendEcuFrame(void);
void AppCAN_SetAutoTransmit(uint8_t enable);
uint8_t AppCAN_GetAutoTransmit(void);
void AppCAN_ProcessAutoTransmit(void);
void AppCAN_PollRxAfterTx(void);

#endif
