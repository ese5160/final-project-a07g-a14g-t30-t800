/**
 * @file LoggerExample.c
 * @brief Example using the Debug Logger Module
 */

 #include "DebugLogger.h"
 #include <stdio.h>
 
 /* This is a mock implementation of SerialConsoleWriteString for testing */
 void SerialConsoleWriteString(const char *string) {
     /* In a real implementation, this would send data to a serial port */
     /* For this example, we'll just print to stdout */
     printf("%s", string);
 }
 
 /**
  * @brief Example function that initializes hardware
  */
 void InitializeHardware(void) {
     int error = 0; /* 0 means no error in this example */
     int sensorTemperature = 85; /* Example sensor reading */
     
     LogMessage(LOG_INFO_LVL, "Initialize Hardware...\r\n");
     
     /* Simulate I2C initialization */
     if (error != 0) {
         LogMessage(LOG_FATAL_LVL, "Failed to init I2C!\r\n");
     } else {
         LogMessage(LOG_INFO_LVL, "Initialized I2C!\r\n");
     }
     
     /* Example of using variable parameters */
     LogMessage(LOG_WARNING_LVL, "Current temperature is %d degrees\r\n", sensorTemperature);
     
     /* This will only be printed if log level is LOG_DEBUG_LVL or lower */
     LogMessage(LOG_DEBUG_LVL, "Debug information: Voltage=%dmV, Current=%dmA\r\n", 3300, 150);
 }
 
 /**
  * @brief Main function for the example
  */
 int main(void) {
     /* Set default log level to INFO */
     setLogLevel(LOG_INFO_LVL);
     LogMessage(LOG_INFO_LVL, "Starting system with INFO level logging\r\n");
     
     InitializeHardware();
     
     /* Change log level to ERROR to filter out less severe messages */
     setLogLevel(LOG_ERROR_LVL);
     LogMessage(LOG_INFO_LVL, "This INFO message won't be printed\r\n");
     LogMessage(LOG_WARNING_LVL, "This WARNING message won't be printed\r\n");
     LogMessage(LOG_ERROR_LVL, "This ERROR message will be printed\r\n");
     LogMessage(LOG_FATAL_LVL, "System failure detected! Shutting down.\r\n");
     
     /* Turn off logging completely */
     setLogLevel(LOG_OFF_LVL);
     LogMessage(LOG_FATAL_LVL, "Even FATAL messages won't be printed now\r\n");
     
     return 0;
 }