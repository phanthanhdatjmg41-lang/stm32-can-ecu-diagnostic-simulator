#include "app_log.h"
#include "app_config.h"
#include "app_uart.h"
#include <string.h>
#include <stdio.h>

/*
 * lastEvent:
 *
 * Luu su kien moi nhat.
 */
static char lastEvent[APP_LOG_LAST_EVENT_SIZE];

/*
 * lastLevel:
 *
 * Luu muc log moi nhat.
 */
static LogLevel_t lastLevel;

/*
 * Cac bien dem so log theo muc.
 */
static uint32_t infoCount;
static uint32_t warningCount;
static uint32_t errorCount;

/*
 * Log_Save:
 *
 * Ham noi bo de luu log.
 */
static void Log_Save(LogLevel_t level, const char* message)
{
    char uartBuffer[96];

    lastLevel = level;

    if (message == 0)
    {
        message = "";
    }

    strncpy(lastEvent, message, APP_LOG_LAST_EVENT_SIZE - 1);
    lastEvent[APP_LOG_LAST_EVENT_SIZE - 1] = '\0';

    if (level == LOG_LEVEL_INFO)
    {
        infoCount++;
    }
    else if (level == LOG_LEVEL_WARNING)
    {
        warningCount++;
    }
    else if (level == LOG_LEVEL_ERROR)
    {
        errorCount++;
    }

    /*
     * Tao chuoi log va gui ra UART.
     */
    snprintf(uartBuffer,
             sizeof(uartBuffer),
             "[%s] %s\r\n",
             Log_GetLevelString(level),
             lastEvent);

    UART_SendString(uartBuffer);
}

void Log_Init(void)
{
    /*
     * Dua toan bo thong tin log ve mac dinh.
     */
    strcpy(lastEvent, "SYSTEM INIT");
    lastLevel = LOG_LEVEL_INFO;

    infoCount = 0;
    warningCount = 0;
    errorCount = 0;

    /*
     * Gui log khoi dong ra UART.
     */
    Log_Info("SYSTEM INIT");
}

void Log_Info(const char* message)
{
    Log_Save(LOG_LEVEL_INFO, message);
}

void Log_Warning(const char* message)
{
    Log_Save(LOG_LEVEL_WARNING, message);
}

void Log_Error(const char* message)
{
    Log_Save(LOG_LEVEL_ERROR, message);
}

const char* Log_GetLastEvent(void)
{
    return lastEvent;
}

LogLevel_t Log_GetLastLevel(void)
{
    return lastLevel;
}

const char* Log_GetLevelString(LogLevel_t level)
{
    switch (level)
    {
        case LOG_LEVEL_INFO:
            return "INFO";

        case LOG_LEVEL_WARNING:
            return "WARNING";

        case LOG_LEVEL_ERROR:
            return "ERROR";

        default:
            return "UNKNOWN";
    }
}

uint32_t Log_GetInfoCount(void)
{
    return infoCount;
}

uint32_t Log_GetWarningCount(void)
{
    return warningCount;
}

uint32_t Log_GetErrorCount(void)
{
    return errorCount;
}
