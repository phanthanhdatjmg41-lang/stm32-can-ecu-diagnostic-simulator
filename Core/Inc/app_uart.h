#ifndef APP_UART_H
#define APP_UART_H

/*
 * app_uart.h
 *
 * Module nay dung de gui/nhan chuoi debug qua UART.
 */

void UART_SendString(const char* str);

/*
 * UART_StartReceive:
 *
 * Bat dau nhan UART tung ky tu bang interrupt.
 */
void UART_StartReceive(void);

/*
 * UART_ProcessReceivedCommand:
 *
 * Kiem tra xem da nhan duoc mot lenh hoan chinh chua.
 * Neu co thi xu ly lenh do.
 */
void UART_ProcessReceivedCommand(void);

#endif
