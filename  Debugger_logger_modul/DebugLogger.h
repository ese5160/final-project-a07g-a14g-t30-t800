/**
 * @file DebugLogger.h
 * @brief Debug Logger Module header file
 *
 * This module provides logging functionality for debugging purposes.
 * It allows logging at different severity levels and filtering based on a set threshold.
 */

 #ifndef DEBUG_LOGGER_H
 #define DEBUG_LOGGER_H
 
 #include <stdarg.h>
 
 /**
  * @brief Enumeration of debug log levels
  */
 enum eDebugLogLevels {
     LOG_INFO_LVL    = 0, /**< Logs an INFO message */
     LOG_DEBUG_LVL   = 1, /**< Logs a DEBUG message */
     LOG_WARNING_LVL = 2, /**< Logs a WARNING message */
     LOG_ERROR_LVL   = 3, /**< Logs an ERROR message */
     LOG_FATAL_LVL   = 4, /**< Logs a FATAL message (non-recoverable error) */
     LOG_OFF_LVL     = 5, /**< Disables logging */
     N_DEBUG_LEVELS  = 6  /**< Maximum number of log levels */
 };
 
 /**
  * @brief Get the current log level
  * @return Current log level
  */
 enum eDebugLogLevels getLogLevel(void);
 
 /**
  * @brief Set the debug log level
  * @param debugLevel The log level to set
  */
 void setLogLevel(enum eDebugLogLevels debugLevel);
 
 /**
  * @brief Log a message at the specified level
  * @param level The log level of the message
  * @param format Format string (like in printf)
  * @param ... Variable arguments to be formatted
  */
 void LogMessage(enum eDebugLogLevels level, const char *format, ...);
 
 #endif /* DEBUG_LOGGER_H */