#include "DebugLogger.h"
#include "SerialConsole.h" // 假设存在用于输出的SerialConsole模块
#include <stdio.h>

static eDebugLogLevels currentLogLevel = LOG_INFO_LVL;

void setLogLevel(eDebugLogLevels debugLevel) {
    currentLogLevel = debugLevel;
}

eDebugLogLevels getLogLevel(void) {
    return currentLogLevel;
}

void LogMessage(eDebugLogLevels level, const char *format, ...) {
    if (level < currentLogLevel) {
        return;
    }

    char buffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    SerialConsoleWriteString(buffer);
}
