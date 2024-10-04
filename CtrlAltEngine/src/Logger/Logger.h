/*!
\group      CtrlAlt
\file       Logger.h
\author     Michael Lazaroo
\par        m.lazaroo@digipen.edu
\date       Sep 09, 2024
\brief      Basic implementation of a Logging system.

This file defines the `Logger` class and the necessary components to implement a simple logging system.
It includes functionality to log messages of different severity levels and format them with timestamped output.
*/

#ifndef LOGGER_H
#define LOGGER_H

// INCLUDES
// =========================================================================================================
#include <string>
#include <vector>
#include <bitset>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <sstream>
#include <deque>

// DEFINITIONS
// =========================================================================================================

// Color definitions using ANSI escape codes for colored terminal output
// Reference: https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
constexpr const char* GREENBG = "\033[42m"; /*!< ANSI code for green background color */
constexpr const char* GREEN = "\033[32m";   /*!< ANSI code for green text color */
constexpr const char* REDBG = "\033[41m";   /*!< ANSI code for red background color */
constexpr const char* RESET = "\033[0m";    /*!< ANSI code to reset color formatting */
constexpr const char* LOG_INFO_COLOR = GREEN; /*!< Default color for info log messages */

/*!
 * \enum Severity
 * \brief Defines the severity levels for log messages.
 *
 * The `Severity` enum defines different levels of logging severity, currently supporting:
 * - `LOG_INFO`: Represents informational messages.
 */
enum Severity : uint8_t {
    LOG_INFO /*!< Informational log messages. */
};

/*!
 * \class LogEntry
 * \brief Represents a single log entry with a severity type and a message.
 *
 * The `LogEntry` class holds the severity type and the corresponding log message.
 */
class LogEntry {
public:
    Severity type; /*!< The severity type of the log entry. */
    std::string message; /*!< The message of the log entry. */
};

/*!
 * \class Logger
 * \brief The core logging system class responsible for logging messages.
 *
 * The `Logger` class provides static functions to log messages and format them with timestamps.
 * It maintains a list of all logged messages and handles formatting for different severity levels.
 */
class Logger {

public:
    /*!
     * \brief Logs an informational message.
     *
     * This static function logs a message with the `LOG_INFO` severity level.
     * \param message The message to log.
     */
    static void LogInfo(const std::string& message);

    /*!
     * \brief A collection of logged messages.
     *
     * A static vector that stores all `LogEntry` objects. It can be made `inline` to ensure a single
     * instance across all translation units.
     */
    static std::vector<LogEntry> messages;

private:
    /*!
     * \brief Gets the current date and time as a formatted string.
     *
     * This function retrieves the current system time and formats it into a string.
     * It is used to timestamp log messages.
     * \return A string representing the current date and time.
     */
    static std::string CurrentDateTimeToString();
};

#endif
