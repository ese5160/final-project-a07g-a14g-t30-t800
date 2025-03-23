#include "DebugLogger.h"

int main() {
    setLogLevel(LOG_ERROR_LVL);

    LogMessage(LOG_INFO_LVL, "Performing Temperature Test...\r\n");
    int sensorTemperature = 150;
    LogMessage(LOG_FATAL_LVL, "Err: Temperature over %d degrees!\r\n", sensorTemperature);
    LogMessage(LOG_ERROR_LVL, "System error!\r\n");

    return 0;
}
