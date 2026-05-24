#include "app_ecu.h"

/*
 * currentState:
 *
 * Bien static luu trang thai hien tai cua ECU.
 * static giup bien chi duoc truy cap truc tiep trong file app_ecu.c.
 */
static EcuState_t currentState;

void Ecu_Init(void)
{
    /*
     * Khi moi khoi dong, ECU o trang thai INIT.
     */
    currentState = ECU_STATE_INIT;

    /*
     * Sau khi init xong, tam thoi dua ve IDLE.
     * Sau nay neu co nhieu buoc init phan cung, ta co the xu ly them.
     */
    currentState = ECU_STATE_IDLE;
}

void Ecu_Start(void)
{
    /*
     * Chi cho phep start neu ECU khong bi loi.
     */
    if (currentState != ECU_STATE_ERROR)
    {
        currentState = ECU_STATE_RUNNING;
    }
}

void Ecu_Stop(void)
{
    /*
     * Stop dua ECU ve IDLE.
     */
    currentState = ECU_STATE_IDLE;
}

void Ecu_Reset(void)
{
    /*
     * Reset tam thoi dua ECU ve IDLE.
     */
    currentState = ECU_STATE_IDLE;
}

void Ecu_SetError(void)
{
    /*
     * Khi co loi nghiem trong, ECU chuyen sang ERROR.
     */
    currentState = ECU_STATE_ERROR;
}

void Ecu_Sleep(void)
{
    /*
     * Chuyen ECU sang che do ngu.
     */
    currentState = ECU_STATE_SLEEP;
}

EcuState_t Ecu_GetState(void)
{
    return currentState;
}

const char* Ecu_GetStateString(EcuState_t state)
{
    switch (state)
    {
        case ECU_STATE_INIT:
            return "INIT";

        case ECU_STATE_IDLE:
            return "IDLE";

        case ECU_STATE_RUNNING:
            return "RUNNING";

        case ECU_STATE_ERROR:
            return "ERROR";

        case ECU_STATE_SLEEP:
            return "SLEEP";

        default:
            return "UNKNOWN";
    }
}
