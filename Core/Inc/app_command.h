#ifndef APP_COMMAND_H
#define APP_COMMAND_H

/*
 * app_command.h
 *
 * Module nay dung de xu ly lenh dieu khien ECU.
 *
 * Hien tai lenh duoc goi truc tiep trong code de test.
 * Sau nay khi co UART, chuoi nhan tu Tera Term se dua vao Command_Process().
 *
 * Cac lenh ho tro:
 * - start
 * - stop
 * - reset
 * - sleep
 * - set dtc P0001
 * - set dtc P0002
 * - set dtc P0003
 * - clear dtc
 */

/*
 * Command_Process:
 *
 * Xu ly mot chuoi lenh.
 */
void Command_Process(const char* cmd);

#endif
