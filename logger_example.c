#include "DebugLogger.h"

int main(void) {
    setLogLevel(LOG_INFO_LVL); 
    LogMessage(LOG_INFO_LVL, "System is booting...\r\n");
    LogMessage(LOG_DEBUG_LVL, "Initializing system components...\r\n");

    
    LogMessage(LOG_ERROR_LVL, "Error initializing network component!\r\n");

    
    setLogLevel(LOG_ERROR_LVL);
    LogMessage(LOG_DEBUG_LVL, "This debug message will not be printed.\r\n");
    LogMessage(LOG_ERROR_LVL, "This error message will be printed.\r\n");

    return 0;
}
