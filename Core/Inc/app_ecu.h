#ifndef APP_ECU_H
#define APP_ECU_H

/*
 * app_ecu.h
 *
 * Module nay quan ly trang thai cua ECU gia lap.
 *
 * ECU co the hieu don gian la mot bo dieu khien trong xe.
 * Vi du:
 * - ECU dong co
 * - ECU phanh
 * - ECU hop so
 *
 * Trong project nay, STM32 se dong vai tro mot ECU gia lap.
 */

#include <stdint.h>

/*
 * EcuState_t:
 *
 * Enum mo ta cac trang thai cua ECU.
 */
typedef enum
{
    ECU_STATE_INIT = 0,     // ECU vua khoi dong
    ECU_STATE_IDLE,         // ECU dang cho
    ECU_STATE_RUNNING,      // ECU dang hoat dong
    ECU_STATE_ERROR,        // ECU dang loi
    ECU_STATE_SLEEP         // ECU o che do ngu
} EcuState_t;

/*
 * Ecu_Init:
 *
 * Khoi tao ECU ve trang thai ban dau.
 */
void Ecu_Init(void);

/*
 * Ecu_Start:
 *
 * Chuyen ECU sang trang thai RUNNING.
 */
void Ecu_Start(void);

/*
 * Ecu_Stop:
 *
 * Chuyen ECU ve trang thai IDLE.
 */
void Ecu_Stop(void);

/*
 * Ecu_Reset:
 *
 * Reset ECU ve trang thai IDLE.
 */
void Ecu_Reset(void);

/*
 * Ecu_SetError:
 *
 * Chuyen ECU sang trang thai ERROR.
 */
void Ecu_SetError(void);

/*
 * Ecu_Sleep:
 *
 * Chuyen ECU sang trang thai SLEEP.
 */
void Ecu_Sleep(void);

/*
 * Ecu_GetState:
 *
 * Lay trang thai hien tai cua ECU.
 */
EcuState_t Ecu_GetState(void);

/*
 * Ecu_GetStateString:
 *
 * Chuyen trang thai enum thanh chuoi de sau nay in ra UART/LCD.
 */
const char* Ecu_GetStateString(EcuState_t state);

#endif
