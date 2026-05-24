#include "app_heartbeat.h"
#include "app_ecu.h"
#include "app_uart.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>

/*
 * Chu ky gui heartbeat, don vi ms.
 */
#define HEARTBEAT_PERIOD_MS     10000

/*
 * lastHeartbeatTick:
 *
 * Luu thoi diem gui heartbeat gan nhat.
 */
static uint32_t lastHeartbeatTick = 0;

void Heartbeat_Init(void)
{
    /*
     * Lay tick hien tai lam moc ban dau.
     */
    lastHeartbeatTick = HAL_GetTick();
}

void Heartbeat_Process(void)
{
    uint32_t currentTick = HAL_GetTick();
    char buffer[96];

    /*
     * Neu chua du thoi gian thi khong gui.
     */
    if ((currentTick - lastHeartbeatTick) < HEARTBEAT_PERIOD_MS)
    {
        return;
    }

    /*
     * Cap nhat moc thoi gian moi.
     */
    lastHeartbeatTick = currentTick;

    /*
     * Tao chuoi heartbeat.
     */
    snprintf(buffer,
             sizeof(buffer),
             "[INFO] HEARTBEAT ECU_STATE=%s\r\n",
             Ecu_GetStateString(Ecu_GetState()));

    UART_SendString(buffer);
}
