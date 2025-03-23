#include "DebugLogger.h"
#include <stdio.h>
#include <stdarg.h>

static eDebugLogLevels currentLogLevel = LOG_INFO_LVL;

void setLogLevel(eDebugLogLevels level) {
    currentLogLevel = level;
}

eDebugLogLevels getLogLevel(void) {
    return currentLogLevel;
}

void LogMessage(eDebugLogLevels level, const char *format, ...) {
    if (level < getLogLevel()) {
        return;
    }

    va_list args;
    va_start(args, format);
    char buffer[256]; // Adjust size as needed
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    printf("%s", buffer); // Replace this with your specific serial output function if necessary
}
