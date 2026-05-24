#include "app_can.h"
#include "main.h"
#include "app_uart.h"
#include "app_dtc.h"
#include "app_ecu.h"
#include <stdio.h>

/*
 * Chu ky gui CAN tu dong, don vi ms.
 */
#define CAN_AUTO_PERIOD_MS      5000

/*
 * Co bat/tat gui CAN tu dong.
 */
static uint8_t canAutoTransmitEnabled = 0;

/*
 * Moc thoi gian gui CAN tu dong lan gan nhat.
 */
static uint32_t lastAutoCanTick = 0;

/*
 * Bien hcan1 duoc CubeIDE tao trong main.c
 * khi ban bat CAN1 trong file .ioc.
 */
extern CAN_HandleTypeDef hcan1;

/*
 * AppCAN_Init:
 *
 * Khoi tao filter va start CAN.
 */
void AppCAN_Init(void)
{
    CAN_FilterTypeDef canFilter;

    /*
     * Cau hinh filter nhan tat ca CAN ID.
     */
    canFilter.FilterBank = 0;
    canFilter.FilterMode = CAN_FILTERMODE_IDMASK;
    canFilter.FilterScale = CAN_FILTERSCALE_32BIT;
    canFilter.FilterIdHigh = 0x0000;
    canFilter.FilterIdLow = 0x0000;
    canFilter.FilterMaskIdHigh = 0x0000;
    canFilter.FilterMaskIdLow = 0x0000;
    canFilter.FilterFIFOAssignment = CAN_RX_FIFO0;
    canFilter.FilterActivation = ENABLE;
    canFilter.SlaveStartFilterBank = 14;

    if (HAL_CAN_ConfigFilter(&hcan1, &canFilter) != HAL_OK)
    {
        UART_SendString("[ERROR] CAN FILTER CONFIG FAIL\r\n");
        return;
    }

    if (HAL_CAN_Start(&hcan1) != HAL_OK)
    {
        UART_SendString("[ERROR] CAN START FAIL\r\n");
        return;
    }

//    if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
//    {
//        UART_SendString("[ERROR] CAN NOTIFICATION FAIL\r\n");
//        return;
//    }

    UART_SendString("[INFO] CAN INIT OK\r\n");
}

/*
 * AppCAN_SendTestFrame:
 *
 * Gui mot CAN frame test.
 */
void AppCAN_SendTestFrame(void)
{
    CAN_TxHeaderTypeDef txHeader;
    uint8_t txData[8] = {0};
    uint32_t txMailbox;
    char buffer[96];

    txHeader.StdId = 0x100;
    txHeader.ExtId = 0x00;
    txHeader.IDE = CAN_ID_STD;
    txHeader.RTR = CAN_RTR_DATA;
    txHeader.DLC = 1;
    txHeader.TransmitGlobalTime = DISABLE;

    txData[0] = 0x01;

    if (HAL_CAN_AddTxMessage(&hcan1, &txHeader, txData, &txMailbox) == HAL_OK)
    {
        snprintf(buffer,
                 sizeof(buffer),
                 "[INFO] CAN TX ID=0x%03lX DATA=%02X\r\n",
                 txHeader.StdId,
                 txData[0]);

        UART_SendString(buffer);
    }
    else
    {
        snprintf(buffer,
                 sizeof(buffer),
                 "[ERROR] CAN TX FAIL ERROR=0x%08lX\r\n",
                 HAL_CAN_GetError(&hcan1));

        UART_SendString(buffer);
    }
}

/*
 * HAL_CAN_RxFifo0MsgPendingCallback:
 *
 * Ham nay duoc HAL goi khi CAN FIFO0 co frame moi.
 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef rxHeader;
    uint8_t rxData[8];
    char buffer[128];

    if (hcan->Instance == CAN1)
    {
        if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rxHeader, rxData) == HAL_OK)
        {
            snprintf(buffer,
                     sizeof(buffer),
                     "[INFO] CAN RX ID=0x%03lX DLC=%lu DATA=%02X %02X %02X %02X %02X %02X %02X %02X\r\n",
                     rxHeader.StdId,
                     rxHeader.DLC,
                     rxData[0],
                     rxData[1],
                     rxData[2],
                     rxData[3],
                     rxData[4],
                     rxData[5],
                     rxData[6],
                     rxData[7]);

            UART_SendString(buffer);
        }
    }
}

void AppCAN_PollRx(void)
{
    CAN_RxHeaderTypeDef rxHeader;
    uint8_t rxData[8];
    char buffer[128];

    /*
     * Neu FIFO0 khong co frame thi bao ro.
     */
    if (HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0) == 0)
    {
        UART_SendString("[WARNING] CAN RX FIFO EMPTY\r\n");
        return;
    }

    if (HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &rxHeader, rxData) == HAL_OK)
    {
        snprintf(buffer,
                 sizeof(buffer),
                 "[INFO] CAN RX ID=0x%03lX DLC=%lu DATA=%02X %02X %02X %02X %02X %02X %02X %02X\r\n",
                 rxHeader.StdId,
                 rxHeader.DLC,
                 rxData[0],
                 rxData[1],
                 rxData[2],
                 rxData[3],
                 rxData[4],
                 rxData[5],
                 rxData[6],
                 rxData[7]);

        UART_SendString(buffer);
    }
    else
    {
        snprintf(buffer,
                 sizeof(buffer),
                 "[ERROR] CAN RX FAIL ERROR=0x%08lX\r\n",
                 HAL_CAN_GetError(&hcan1));

        UART_SendString(buffer);
    }
}
/*
 * AppCAN_GetStateString:
 *
 * Chuyen trang thai CAN thanh chuoi de hien thi de doc.
 */
static const char* AppCAN_GetStateString(HAL_CAN_StateTypeDef state)
{
    switch (state)
    {
        case HAL_CAN_STATE_RESET:
            return "RESET";

        case HAL_CAN_STATE_READY:
            return "READY";

        case HAL_CAN_STATE_LISTENING:
            return "LISTENING";

        case HAL_CAN_STATE_SLEEP_PENDING:
            return "SLEEP_PENDING";

        case HAL_CAN_STATE_SLEEP_ACTIVE:
            return "SLEEP_ACTIVE";

        case HAL_CAN_STATE_ERROR:
            return "ERROR";

        default:
            return "UNKNOWN";
    }
}

void AppCAN_ShowStatus(void)
{
    char buffer[128];

    UART_SendString("\r\n===== CAN STATUS =====\r\n");

    snprintf(buffer,
             sizeof(buffer),
             "CAN State : %s\r\n",
             AppCAN_GetStateString(HAL_CAN_GetState(&hcan1)));
    UART_SendString(buffer);

    snprintf(buffer,
             sizeof(buffer),
             "CAN Error : 0x%08lX\r\n",
             HAL_CAN_GetError(&hcan1));
    UART_SendString(buffer);

    snprintf(buffer,
             sizeof(buffer),
             "RX FIFO0  : %lu\r\n",
             HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0));
    UART_SendString(buffer);

    snprintf(buffer,
             sizeof(buffer),
             "TX Free   : %lu\r\n",
             HAL_CAN_GetTxMailboxesFreeLevel(&hcan1));
    UART_SendString(buffer);

    UART_SendString("======================\r\n");
}

/*
 * AppCAN_SendDtcFrame:
 *
 * Gui CAN frame chua ma loi DTC hien tai.
 *
 * CAN ID:
 * 0x321
 *
 * Data[0]:
 * 0x00 = Khong co loi
 * 0x01 = P0001 SENSOR_FAIL
 * 0x02 = P0002 COMM_TIMEOUT
 * 0x03 = P0003 LOW_VOLTAGE
 */
void AppCAN_SendDtcFrame(void)
{
    CAN_TxHeaderTypeDef txHeader;
    uint8_t txData[8] = {0};
    uint32_t txMailbox;
    char buffer[128];

    txHeader.StdId = 0x321;
    txHeader.ExtId = 0x00;
    txHeader.IDE = CAN_ID_STD;
    txHeader.RTR = CAN_RTR_DATA;
    txHeader.DLC = 1;
    txHeader.TransmitGlobalTime = DISABLE;

    /*
     * Lay ma DTC hien tai va dua vao data[0].
     */
    txData[0] = (uint8_t)Dtc_GetCode();

    if (HAL_CAN_AddTxMessage(&hcan1, &txHeader, txData, &txMailbox) == HAL_OK)
    {
        snprintf(buffer,
                 sizeof(buffer),
                 "[INFO] CAN TX DTC ID=0x%03lX DTC=%s DATA=%02X\r\n",
                 txHeader.StdId,
                 Dtc_GetCodeString(Dtc_GetCode()),
                 txData[0]);

        UART_SendString(buffer);
    }
    else
    {
        snprintf(buffer,
                 sizeof(buffer),
                 "[ERROR] CAN TX DTC FAIL ERROR=0x%08lX\r\n",
                 (uint32_t)HAL_CAN_GetError(&hcan1));

        UART_SendString(buffer);
    }
}

/*
 * AppCAN_SendEcuFrame:
 *
 * Gui CAN frame chua trang thai ECU hien tai.
 *
 * CAN ID:
 * 0x322
 *
 * Data[0]:
 * 0x00 = INIT
 * 0x01 = IDLE
 * 0x02 = RUNNING
 * 0x03 = ERROR
 * 0x04 = SLEEP
 */
void AppCAN_SendEcuFrame(void)
{
    CAN_TxHeaderTypeDef txHeader;
    uint8_t txData[8] = {0};
    uint32_t txMailbox;
    char buffer[128];

    txHeader.StdId = 0x322;
    txHeader.ExtId = 0x00;
    txHeader.IDE = CAN_ID_STD;
    txHeader.RTR = CAN_RTR_DATA;
    txHeader.DLC = 1;
    txHeader.TransmitGlobalTime = DISABLE;

    /*
     * Lay trang thai ECU hien tai va dua vao data[0].
     */
    txData[0] = (uint8_t)Ecu_GetState();

    if (HAL_CAN_AddTxMessage(&hcan1, &txHeader, txData, &txMailbox) == HAL_OK)
    {
        snprintf(buffer,
                 sizeof(buffer),
                 "[INFO] CAN TX ECU ID=0x%03lX ECU=%s DATA=%02X\r\n",
                 txHeader.StdId,
                 Ecu_GetStateString(Ecu_GetState()),
                 txData[0]);

        UART_SendString(buffer);
    }
    else
    {
        snprintf(buffer,
                 sizeof(buffer),
                 "[ERROR] CAN TX ECU FAIL ERROR=0x%08lX\r\n",
                 (uint32_t)HAL_CAN_GetError(&hcan1));

        UART_SendString(buffer);
    }
}

/*
 * AppCAN_SetAutoTransmit:
 *
 * Bat hoac tat che do gui CAN tu dong.
 */
void AppCAN_SetAutoTransmit(uint8_t enable)
{
    char buffer[96];

    if (enable != 0)
    {
        canAutoTransmitEnabled = 1;
        lastAutoCanTick = HAL_GetTick();

        UART_SendString("[INFO] CAN AUTO TRANSMIT ON\r\n");
    }
    else
    {
        canAutoTransmitEnabled = 0;

        UART_SendString("[INFO] CAN AUTO TRANSMIT OFF\r\n");
    }

    snprintf(buffer,
             sizeof(buffer),
             "[INFO] CAN AUTO PERIOD=%lu ms\r\n",
             (uint32_t)CAN_AUTO_PERIOD_MS);

    UART_SendString(buffer);
}

/*
 * AppCAN_GetAutoTransmit:
 *
 * Lay trang thai bat/tat cua che do gui CAN tu dong.
 */
uint8_t AppCAN_GetAutoTransmit(void)
{
    return canAutoTransmitEnabled;
}

/*
 * AppCAN_ProcessAutoTransmit:
 *
 * Xu ly gui CAN tu dong theo chu ky.
 * Ham nay phai duoc goi lap lai trong while(1).
 */
void AppCAN_ProcessAutoTransmit(void)
{
    uint32_t currentTick;

    /*
     * Neu chua bat auto transmit thi thoat.
     */
    if (canAutoTransmitEnabled == 0)
    {
        return;
    }

    currentTick = HAL_GetTick();

    /*
     * Neu chua du chu ky thi thoat.
     */
    if ((currentTick - lastAutoCanTick) < CAN_AUTO_PERIOD_MS)
    {
        return;
    }

    lastAutoCanTick = currentTick;

    /*
     * Gui frame ECU state.
     */
    AppCAN_SendEcuFrame();
    HAL_Delay(10);
    AppCAN_PollRx();

    /*
     * Gui frame DTC.
     */
    AppCAN_SendDtcFrame();
    HAL_Delay(10);
    AppCAN_PollRx();
}

/*
 * AppCAN_PollRxAfterTx:
 *
 * Cho CAN loopback xu ly frame vua gui,
 * sau do doc frame tu FIFO0.
 */
void AppCAN_PollRxAfterTx(void)
{
    /*
     * Delay rat nho de CAN loopback kip dua frame vao FIFO.
     * Hien tai dung 10ms de don gian va on dinh khi test.
     */
    HAL_Delay(10);

    AppCAN_PollRx();
}
