#include "app_uart.h"
#include "main.h"
#include "stm32f7xx_hal.h"
#include "app_command.h"
#include <string.h>

/*
 * Bien huart1 duoc tao trong main.c
 * khi USART1 duoc cau hinh o che do Asynchronous.
 */
extern UART_HandleTypeDef huart1;

/*
 * Byte nhan duoc tu UART.
 */
static uint8_t uartRxByte;

/*
 * Buffer luu lenh nguoi dung go tu Tera Term.
 */
static char uartRxBuffer[64];

/*
 * Vi tri ghi hien tai trong buffer.
 */
static uint8_t uartRxIndex = 0;

/*
 * Co bao da co lenh hoan chinh.
 */
static volatile uint8_t uartCommandReady = 0;

void UART_SendString(const char* str)
{
    if (str == 0)
    {
        return;
    }

    HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), 100);
}

void UART_StartReceive(void)
{
    /*
     * Xoa buffer truoc khi bat nhan.
     */
    memset(uartRxBuffer, 0, sizeof(uartRxBuffer));
    uartRxIndex = 0;
    uartCommandReady = 0;

    /*
     * Bat dau nhan 1 byte bang interrupt.
     */
    HAL_UART_Receive_IT(&huart1, &uartRxByte, 1);
}

void UART_ProcessReceivedCommand(void)
{
    /*
     * Neu chua co lenh thi thoat.
     */
    if (uartCommandReady == 0)
    {
        return;
    }

    /*
     * Xu ly lenh vua nhan.
     */
    Command_Process(uartRxBuffer);

    /*
     * Xoa buffer sau khi xu ly.
     */
    memset(uartRxBuffer, 0, sizeof(uartRxBuffer));
    uartRxIndex = 0;
    uartCommandReady = 0;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        /*
         * Neu nhan Enter thi ket thuc lenh.
         */
        if ((uartRxByte == '\r') || (uartRxByte == '\n'))
        {
            if ((uartRxIndex > 0) && (uartCommandReady == 0))
            {
                uartRxBuffer[uartRxIndex] = '\0';
                uartCommandReady = 1;
                UART_SendString("\r\n");
            }
        }

        /*
         * Xu ly phim Backspace hoac Delete.
         */
        else if ((uartRxByte == 8) || (uartRxByte == 127))
        {
            if ((uartRxIndex > 0) && (uartCommandReady == 0))
            {
                uartRxIndex--;
                uartRxBuffer[uartRxIndex] = '\0';
                UART_SendString("\b \b");
            }
        }

        /*
         * Chi nhan ky tu ASCII in duoc.
         */
        else if ((uartRxByte >= 32) && (uartRxByte <= 126))
        {
            if (uartCommandReady == 0)
            {
                if (uartRxIndex < sizeof(uartRxBuffer) - 1)
                {
                    uartRxBuffer[uartRxIndex] = (char)uartRxByte;
                    uartRxIndex++;
                    HAL_UART_Transmit(&huart1, &uartRxByte, 1, 10);
                }
                else
                {
                    /*
                     * Neu day buffer thi xoa, khong goi Log trong callback.
                     */
                    memset(uartRxBuffer, 0, sizeof(uartRxBuffer));
                    uartRxIndex = 0;
                }
            }
        }

        /*
         * Bat nhan byte tiep theo.
         */
        HAL_UART_Receive_IT(&huart1, &uartRxByte, 1);
    }
}
