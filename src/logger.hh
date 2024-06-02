// *************************************
// Astra Cache Server
// Utilities
// 'logger.hh'
// Author: jcjuarez
// *************************************

#ifndef LOGGER_ 
#define LOGGER_

#include <mutex>
#include <atomic>
#include <random>
#include <format>
#include <cassert>
#include <unistd.h>
#include "common.hh"
#include <filesystem>
#include "random_identifier_generator.hh"

namespace astra
{

//
// Log level for logs classification.
//
enum class log_level : uint8
{

    //
    // Information level logs.
    // Used for debugging actions occurring in the system.
    //
    info = 0,

    //
    // Warning level logs.
    // Used for non-error-related events that require attention.
    //
    warning = 1,

    //
    // Error level logs.
    // Used for error-related events that indicate a failed action.
    //
    error = 2,

    //
    // Critical level logs.
    // Used for critical error-related events that may provoke a system shutdown.
    //
    critical = 3
    
};

struct logger_configuration;

//
// Logger singleton class for managing logging in the system.
//
class logger
{

private:

    //
    // Private constructor for the singleton instance.
    //
    logger(
        std::string* p_initial_message,
        const logger_configuration* p_logger_configuration);

public:

    //
    // Initialize singleton logger instance. Must be called only once.
    //
    static
    status_code
    initialize(
        const logger_configuration& p_logger_configuration);

    //
    // Logging external method.
    //
    static
    void
    log(
        const log_level& p_log_level,
        std::string&& p_message,
        status_code* p_status = nullptr,
        const logger_configuration* p_logger_configuration = nullptr);

    //
    // Default error logging fallback mechanism to console and syslog.
    //
    static
    void
    log_error_fallback(
        std::string&& p_message);

    //
    // Sets the activity id for the current thread.
    //
    static
    void
    set_activity_id(
        const std::string& p_activity_id);

    //
    // Resets the activity id back to the default value.
    //
    static
    void
    reset_activity_id();

    //
    // Gets the logger initialization status.
    //
    static
    bool
    is_logger_initialized();

    //
    // Default activity id value.
    //
    static constexpr const character* c_default_activity_id = "0";

private:

    //
    // Logging internal method.
    //
    void
    log_message(
        const log_level& p_log_level,
        const character* p_message);

    //
    // Constructs the log message with formatting.
    //
    std::string
    create_formatted_log_message(
        const log_level& p_log_level,
        const character* p_message) const;

    //
    // Logs a message to a log file.
    //
    status_code
    log_to_file(
        const character* p_message);

    //
    // Generates the curently pointed logs file path.
    //
    std::filesystem::path
    get_current_logs_file_path() const;

    //
    // Logs a message to the console.
    //
    static
    void
    log_message_to_console(
        const character* p_message);

    //
    // Logs an error to the console.
    //
    static
    void
    log_error_to_console(
        const character* p_message);

    //
    // Logs a message to syslog.
    //
    static
    void
    log_to_syslog(
        const character* p_message);

    //
    // Flag for determining is the singleton instance is initialized.
    //
    static std::atomic<bool> s_initialized;

    //
    // Text for info level logs.
    //
    static constexpr const character* c_info_log_level = "Info";

    //
    // Text for warning level logs.
    //
    static constexpr const character* c_warning_log_level = "Warning";

    //
    // Text for error level logs.
    //
    static constexpr const character* c_error_log_level = "Error";

    //
    // Text for critical level logs.
    //
    static constexpr const character* c_critical_log_level = "Critical";

    //
    // Text for default level logs.
    //
    static constexpr const character* c_default_log_level = "Unknown";

    //
    // Session logs directory prefix.
    //
    static constexpr const character* c_session_logs_directory_prefix = "astra-logs-";

    //
    // Logs files extension.
    //
    static constexpr const character* c_logs_files_extension = "log";

    //
    // Astra executable name.
    //
    static constexpr const character* c_astra_executable_name = "astra";

    //
    // Max size in MiB for individual logs files.
    //
    static constexpr uint8 c_max_logs_file_size_mib = 10u;

    //
    // Max retries count for incremental search for logging.
    //
    static constexpr uint8 c_max_incremental_search_retry_count = 5u;

    //
    // Max retries count for logs writing attempts.
    //
    static constexpr uint8 c_max_logs_writing_attempts_retry_count = 10u;

    //
    // Lock for synchronizing access across threads.
    //
    std::mutex m_lock;

    //
    // Random identifier generator for logging purposes.
    //
    random_identifier_generator m_random_identifier_generator; 

    //
    // Flag for determining whether debug mode is enabled.
    //
    bool m_debug_mode_enabled;

    //
    // Path to the directory where system logs will be stored for the session.
    //
    std::filesystem::path m_session_logs_directory_path;

    //
    // Logger session ID.
    //
    std::string m_session_id;

    //
    // Logs files count.  
    //
    uint64 m_logs_files_count;

    //
    // Path to the currently pointed logs file.
    //
    std::filesystem::path m_current_logs_file_path;

    //
    // Process ID for the session.
    //
    pid_t m_process_id;
    
};

//
// Log info message macro.
//
#define log_info_message(p_format, ...) \
    do \
    { \
        assert(logger::is_logger_initialized()); \
        logger::log(log_level::info, std::format(p_format, ##__VA_ARGS__)); \
    } \
    while (false)

//
// Log warning message macro.
//
#define log_warning_message(p_format, ...) \
    do \
    { \
        assert(logger::is_logger_initialized()); \
        logger::log(log_level::warning, std::format(p_format, ##__VA_ARGS__)); \
    } \
    while (false)

//
// Log error message macro.
//
#define log_error_message(p_format, ...) \
    do \
    { \
        assert(logger::is_logger_initialized()); \
        logger::log(log_level::error, std::format(p_format, ##__VA_ARGS__)); \
    } \
    while (false)

//
// Log critical message macro.
//
#define log_critical_message(p_format, ...) \
    do \
    { \
        if (logger::is_logger_initialized()) \
        { \
            logger::log(log_level::critical, std::format(p_format, ##__VA_ARGS__)); \
        } \
        else \
        { \
            logger::log_error_fallback(std::format(p_format, ##__VA_ARGS__)); \
        } \
    } \
    while (false)

} // namespace astra.

#endif