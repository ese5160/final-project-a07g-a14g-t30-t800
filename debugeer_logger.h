#ifndef DEBUG_LOGGER_H
#define DEBUG_LOGGER_H

#include <stdarg.h>

typedef enum {
    LOG_INFO_LVL = 0,
    LOG_DEBUG_LVL = 1,
    LOG_WARNING_LVL = 2,
    LOG_ERROR_LVL = 3,
    LOG_FATAL_LVL = 4,
    LOG_OFF_LVL = 5,
    N_DEBUG_LEVELS = 6
} eDebugLogLevels;

void LogMessage(eDebugLogLevels level, const char *format, ...);
void setLogLevel(eDebugLogLevels debugLevel);
eDebugLogLevels getLogLevel(void);

#endif // DEBUG_LOGGER_H
