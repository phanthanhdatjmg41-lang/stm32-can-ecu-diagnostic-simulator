#include "app_command.h"
#include "app_ecu.h"
#include "app_dtc.h"
#include "app_log.h"
#include "app_uart.h"
#include "app_can.h"
#include "stm32f7xx_hal.h"

#include <string.h>
#include <stdio.h>

/*
 * Command_ShowHelp:
 *
 * Ham nay hien thi danh sach lenh ho tro.
 */
static void Command_ShowHelp(void)
{
    UART_SendString("\r\n===== COMMAND LIST =====\r\n");
    UART_SendString("help              : Show command list\r\n");
    UART_SendString("status            : Show ECU status\r\n");
    UART_SendString("start             : Start ECU\r\n");
    UART_SendString("stop              : Stop ECU\r\n");
    UART_SendString("reset             : Reset ECU\r\n");
    UART_SendString("sleep             : Put ECU to sleep\r\n");
    UART_SendString("set dtc P0001     : Set SENSOR_FAIL fault\r\n");
    UART_SendString("set dtc P0002     : Set COMM_TIMEOUT fault\r\n");
    UART_SendString("set dtc P0003     : Set LOW_VOLTAGE fault\r\n");
    UART_SendString("clear dtc         : Clear current DTC\r\n");
    UART_SendString("can test          : Send CAN test frame\r\n");
    UART_SendString("can status        : Show CAN status\r\n");
    UART_SendString("can dtc           : Send current DTC over CAN\r\n");
    UART_SendString("can ecu           : Send current ECU state over CAN\r\n");
    UART_SendString("can all           : Send ECU state and DTC over CAN\r\n");
    UART_SendString("diag report       : Show full diagnostic report\r\n");
    UART_SendString("can auto on       : Enable periodic CAN report\r\n");
    UART_SendString("can auto off      : Disable periodic CAN report\r\n");
    UART_SendString("can auto status   : Show CAN auto status\r\n");
    UART_SendString("========================\r\n");
}
/*
 * Command_ShowStatus:
 *
 * Ham nay gui trang thai hien tai cua ECU ra UART.
 */
static void Command_ShowStatus(void)
{
    char buffer[96];

    UART_SendString("\r\n===== ECU STATUS =====\r\n");

    /*
     * Gui trang thai ECU.
     */
    snprintf(buffer,
             sizeof(buffer),
             "ECU State : %s\r\n",
             Ecu_GetStateString(Ecu_GetState()));
    UART_SendString(buffer);

    /*
     * Gui ma loi DTC hien tai.
     */
    snprintf(buffer,
             sizeof(buffer),
             "DTC Code  : %s\r\n",
             Dtc_GetCodeString(Dtc_GetCode()));
    UART_SendString(buffer);

    /*
     * Gui mo ta loi DTC hien tai.
     */
    snprintf(buffer,
             sizeof(buffer),
             "DTC Desc  : %s\r\n",
             Dtc_GetDescription(Dtc_GetCode()));
    UART_SendString(buffer);

    /*
     * Gui log moi nhat.
     */
    snprintf(buffer,
             sizeof(buffer),
             "Last Log  : %s\r\n",
             Log_GetLastEvent());
    UART_SendString(buffer);

    UART_SendString("======================\r\n");
}

/*
 * Command_ShowDiagReport:
 *
 * Hien thi bao cao chan doan tong hop.
 */
static void Command_ShowDiagReport(void)
{
    char buffer[128];

    UART_SendString("\r\n===== DIAGNOSTIC REPORT =====\r\n");

    /*
     * Hien thi trang thai ECU.
     */
    snprintf(buffer,
             sizeof(buffer),
             "ECU State    : %s\r\n",
             Ecu_GetStateString(Ecu_GetState()));
    UART_SendString(buffer);

    /*
     * Hien thi ma loi DTC hien tai.
     */
    snprintf(buffer,
             sizeof(buffer),
             "DTC Code     : %s\r\n",
             Dtc_GetCodeString(Dtc_GetCode()));
    UART_SendString(buffer);

    /*
     * Hien thi mo ta loi DTC.
     */
    snprintf(buffer,
             sizeof(buffer),
             "DTC Desc     : %s\r\n",
             Dtc_GetDescription(Dtc_GetCode()));
    UART_SendString(buffer);

    /*
     * Hien thi log gan nhat.
     */
    snprintf(buffer,
             sizeof(buffer),
             "Last Event   : %s\r\n",
             Log_GetLastEvent());
    UART_SendString(buffer);

    /*
     * Hien thi so luong log theo muc.
     */
    snprintf(buffer,
             sizeof(buffer),
             "Info Count   : %lu\r\n",
             (uint32_t)Log_GetInfoCount());
    UART_SendString(buffer);

    snprintf(buffer,
             sizeof(buffer),
             "Warn Count   : %lu\r\n",
             (uint32_t)Log_GetWarningCount());
    UART_SendString(buffer);

    snprintf(buffer,
             sizeof(buffer),
             "Error Count  : %lu\r\n",
             (uint32_t)Log_GetErrorCount());
    UART_SendString(buffer);

    UART_SendString("=============================\r\n");
}

/*
 * Command_Process:
 *
 * Ham nay nhan vao mot chuoi lenh va dieu khien ECU.
 *
 * Vi du:
 * Command_Process("start");
 * Command_Process("set dtc P0001");
 */
void Command_Process(const char* cmd)
{
    /*
     * Neu cmd la NULL thi bao loi va thoat.
     */
    if (cmd == 0)
    {
        Log_Error("NULL COMMAND");
        return;
    }
    /*
     * Lenh help:
     * Hien thi danh sach lenh.
     */
    if (strcmp(cmd, "help") == 0)
    {
        Command_ShowHelp();
    }

    /*
     * Lenh start:
     * Dua ECU sang RUNNING.
     */
    else if (strcmp(cmd, "start") == 0)
    {
        Ecu_Start();
        Log_Info("ECU START");
    }

    /*
     * Lenh stop:
     * Dua ECU ve IDLE.
     */
    else if (strcmp(cmd, "stop") == 0)
    {
        Ecu_Stop();
        Log_Info("ECU STOP");
    }

    /*
     * Lenh reset:
     * Reset ECU ve IDLE.
     */
    else if (strcmp(cmd, "reset") == 0)
    {
        Ecu_Reset();
        Dtc_Clear();
        Log_Info("ECU RESET");
    }

    /*
     * Lenh sleep:
     * Dua ECU sang SLEEP.
     */
    else if (strcmp(cmd, "sleep") == 0)
    {
        Ecu_Sleep();
        Log_Info("ECU SLEEP");
    }

    /*
     * Lenh set dtc P0001:
     * Gia lap loi SENSOR_FAIL.
     */
    else if (strcmp(cmd, "set dtc P0001") == 0)
    {
        Dtc_Set(DTC_SENSOR_FAIL);
        Ecu_SetError();
        Log_Error("DTC P0001 SENSOR_FAIL");
    }

    /*
     * Lenh set dtc P0002:
     * Gia lap loi COMM_TIMEOUT.
     */
    else if (strcmp(cmd, "set dtc P0002") == 0)
    {
        Dtc_Set(DTC_COMM_TIMEOUT);
        Ecu_SetError();
        Log_Error("DTC P0002 COMM_TIMEOUT");
    }

    /*
     * Lenh set dtc P0003:
     * Gia lap loi LOW_VOLTAGE.
     */
    else if (strcmp(cmd, "set dtc P0003") == 0)
    {
        Dtc_Set(DTC_LOW_VOLTAGE);
        Ecu_SetError();
        Log_Error("DTC P0003 LOW_VOLTAGE");
    }

    /*
     * Lenh clear dtc:
     * Xoa loi DTC hien tai.
     */
    else if (strcmp(cmd, "clear dtc") == 0)
    {
        Dtc_Clear();
        Ecu_Reset();
    }
    /*
     * Lenh status:
     * In trang thai hien tai cua ECU ra UART.
     */
    else if (strcmp(cmd, "status") == 0)
    {
        Command_ShowStatus();
    }
    /*
     * Lenh can test:
     * Gui mot CAN frame test va doc lai FIFO RX neu co.
     */
    else if (strcmp(cmd, "can test") == 0)
    {
        AppCAN_SendTestFrame();

        /*
         * Doc lai frame CAN loopback sau khi gui.
         */
        AppCAN_PollRxAfterTx();
    }

    /*
     * Lenh can status:
     * Hien thi trang thai CAN hien tai.
     */
    else if (strcmp(cmd, "can status") == 0)
    {
        AppCAN_ShowStatus();
    }
    /*
     * Lenh can dtc:
     * Gui ma loi DTC hien tai qua CAN.
     */
    else if (strcmp(cmd, "can dtc") == 0)
    {
        AppCAN_SendDtcFrame();

        AppCAN_PollRxAfterTx();
    }
    /*
     * Lenh can ecu:
     * Gui trang thai ECU hien tai qua CAN.
     */
    else if (strcmp(cmd, "can ecu") == 0)
    {
        AppCAN_SendEcuFrame();

        AppCAN_PollRxAfterTx();
    }
    /*
     * Lenh can all:
     * Gui ca trang thai ECU va DTC hien tai qua CAN.
     */
    else if (strcmp(cmd, "can all") == 0)
    {
        AppCAN_SendEcuFrame();

        AppCAN_PollRxAfterTx();

        AppCAN_SendDtcFrame();

        AppCAN_PollRxAfterTx();
    }
    /*
     * Lenh diag report:
     * Hien thi bao cao chan doan tong hop.
     */
    else if (strcmp(cmd, "diag report") == 0)
    {
        Command_ShowDiagReport();
    }
    /*
     * Lenh can auto on:
     * Bat gui CAN tu dong theo chu ky.
     */
    else if (strcmp(cmd, "can auto on") == 0)
    {
        AppCAN_SetAutoTransmit(1);
    }

    /*
     * Lenh can auto off:
     * Tat gui CAN tu dong.
     */
    else if (strcmp(cmd, "can auto off") == 0)
    {
        AppCAN_SetAutoTransmit(0);
    }

    /*
     * Lenh can auto status:
     * Hien thi trang thai gui CAN tu dong.
     */
    else if (strcmp(cmd, "can auto status") == 0)
    {
        if (AppCAN_GetAutoTransmit() != 0)
        {
            UART_SendString("[INFO] CAN AUTO STATUS=ON\r\n");
        }
        else
        {
            UART_SendString("[INFO] CAN AUTO STATUS=OFF\r\n");
        }
    }

    /*
     * Lenh khong hop le.
     */
    else
    {
        Log_Warning("UNKNOWN COMMAND");
    }
}
