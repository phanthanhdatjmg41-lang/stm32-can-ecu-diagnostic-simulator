#ifndef APP_DTC_H
#define APP_DTC_H

#include <stdint.h>
#include "app_config.h"

/*
 * app_dtc.h
 *
 * Module nay quan ly ma loi DTC cua ECU gia lap.
 *
 * DTC co the hieu la ma loi chan doan.
 * Vi du:
 * - P0001: SENSOR_FAIL
 * - P0002: COMM_TIMEOUT
 * - P0003: LOW_VOLTAGE
 */

/*
 * DtcStatus_t:
 *
 * Trang thai cua DTC.
 */
typedef enum
{
    DTC_STATUS_INACTIVE = 0,    // Chua co loi
    DTC_STATUS_ACTIVE          // Dang co loi
} DtcStatus_t;

/*
 * DtcCode_t:
 *
 * Danh sach cac ma loi gia lap.
 */
typedef enum
{
    DTC_NONE = 0,
    DTC_SENSOR_FAIL,
    DTC_COMM_TIMEOUT,
    DTC_LOW_VOLTAGE
} DtcCode_t;

/*
 * Dtc_Init:
 *
 * Khoi tao module DTC.
 */
void Dtc_Init(void);

/*
 * Dtc_Set:
 *
 * Set mot ma loi DTC.
 */
void Dtc_Set(DtcCode_t code);

/*
 * Dtc_Clear:
 *
 * Xoa loi DTC hien tai.
 */
void Dtc_Clear(void);

/*
 * Dtc_GetCode:
 *
 * Lay ma loi hien tai.
 */
DtcCode_t Dtc_GetCode(void);

/*
 * Dtc_GetStatus:
 *
 * Lay trang thai DTC.
 */
DtcStatus_t Dtc_GetStatus(void);

/*
 * Dtc_GetCodeString:
 *
 * Chuyen ma loi thanh chuoi.
 */
const char* Dtc_GetCodeString(DtcCode_t code);

/*
 * Dtc_GetDescription:
 *
 * Lay mo ta loi.
 */
const char* Dtc_GetDescription(DtcCode_t code);

#endif
