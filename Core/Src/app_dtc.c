#include "app_dtc.h"
#include "app_log.h"

/*
 * currentDtc:
 *
 * Luu ma loi DTC hien tai.
 */
static DtcCode_t currentDtc;

/*
 * currentStatus:
 *
 * Luu trang thai DTC hien tai.
 */
static DtcStatus_t currentStatus;

void Dtc_Init(void)
{
    /*
     * Ban dau khong co loi.
     */
    currentDtc = DTC_NONE;
    currentStatus = DTC_STATUS_INACTIVE;

    Log_Info("DTC INIT");
}

void Dtc_Set(DtcCode_t code)
{
    /*
     * Neu code la DTC_NONE thi xem nhu xoa loi.
     */
    if (code == DTC_NONE)
    {
        Dtc_Clear();
        return;
    }

    /*
     * Luu ma loi moi.
     */
    currentDtc = code;
    currentStatus = DTC_STATUS_ACTIVE;

    /*
     * Ghi log loi.
     */
    Log_Error("DTC SET");
}

void Dtc_Clear(void)
{
    /*
     * Xoa ma loi hien tai.
     */
    currentDtc = DTC_NONE;
    currentStatus = DTC_STATUS_INACTIVE;

    Log_Info("DTC CLEARED");
}

DtcCode_t Dtc_GetCode(void)
{
    return currentDtc;
}

DtcStatus_t Dtc_GetStatus(void)
{
    return currentStatus;
}

const char* Dtc_GetCodeString(DtcCode_t code)
{
    switch (code)
    {
        case DTC_NONE:
            return "NONE";

        case DTC_SENSOR_FAIL:
            return "P0001";

        case DTC_COMM_TIMEOUT:
            return "P0002";

        case DTC_LOW_VOLTAGE:
            return "P0003";

        default:
            return "UNKNOWN";
    }
}

const char* Dtc_GetDescription(DtcCode_t code)
{
    switch (code)
    {
        case DTC_NONE:
            return "NO_ERROR";

        case DTC_SENSOR_FAIL:
            return "SENSOR_FAIL";

        case DTC_COMM_TIMEOUT:
            return "COMM_TIMEOUT";

        case DTC_LOW_VOLTAGE:
            return "LOW_VOLTAGE";

        default:
            return "UNKNOWN_ERROR";
    }
}
