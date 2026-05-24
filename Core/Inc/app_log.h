#ifndef APP_LOG_H
#define APP_LOG_H

#include <stdint.h>

/*
 * app_log.h
 *
 * Module log dung de luu su kien moi nhat cua he thong.
 *
 * Hien tai chi luu trong RAM.
 * Sau nay co the gui ra UART hoac ghi vao SD card.
 */

typedef enum
{
    LOG_LEVEL_INFO = 0,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR
} LogLevel_t;

void Log_Init(void);
void Log_Info(const char* message);
void Log_Warning(const char* message);
void Log_Error(const char* message);

const char* Log_GetLastEvent(void);
LogLevel_t Log_GetLastLevel(void);
const char* Log_GetLevelString(LogLevel_t level);

uint32_t Log_GetInfoCount(void);
uint32_t Log_GetWarningCount(void);
uint32_t Log_GetErrorCount(void);

#endif
