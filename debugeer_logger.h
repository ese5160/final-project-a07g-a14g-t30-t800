#ifndef DEBUG_LOGGER_H
#define DEBUG_LOGGER_H

#include <stdarg.h>

/**
 * Enumeration for different levels of debug messages.
 */
typedef enum {
    LOG_INFO_LVL    = 0, /**< Logs an INFO message */
    LOG_DEBUG_LVL   = 1, /**< Logs a DEBUG message */
    LOG_WARNING_LVL = 2, /**< Logs a WARNING message */
    LOG_ERROR_LVL   = 3, /**< Logs an ERROR message */
    LOG_FATAL_LVL   = 4, /**< Logs a FATAL message */
    LOG_OFF_LVL     = 5, /**< Disables logging */
    N_DEBUG_LEVELS  = 6  /**< Maximum number of log levels */
} eDebugLogLevels;

/**
 * @brief Sets the current logging level.
 * @param level The logging level to set.
 */
void setLogLevel(eDebugLogLevels level);

/**
 * @brief Gets the current logging level.
 * @return The current logging level.
 */
eDebugLogLevels getLogLevel(void);

/**
 * @brief Logs a message if the level is greater than or equal to the current log level.
 * @param level The logging level of the message.
 * @param format A format string as described in printf.
 * @param ... Variable arguments providing additional information (printf-style).
 */
void LogMessage(eDebugLogLevels level, const char *format, ...);

#endif // DEBUG_LOGGER_H
