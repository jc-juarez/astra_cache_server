// *************************************
// Astra Cache Server
// Utilities
// 'logger.cc'
// Author: jcjuarez
// *************************************

#include <ctime>
#include <limits>
#include <iostream>
#include <syslog.h>
#include "logger.hh"
#include "timestamp.hh"
#include <sys/syscall.h>
#include "system_configuration.hh"
#include "filesystem_utilities.hh"

namespace astra
{

thread_local std::string g_activity_id = logger::c_default_activity_id;

std::atomic<bool> logger::s_initialized = false;

logger::logger(
    std::string* p_initial_message,
    const logger_configuration* p_logger_configuration)
    : m_logs_files_count(0),
      m_process_id(getpid()),
      m_random_identifier_generator()
{
    //
    // The logger is agnostic to the default configurations given by the
    // configurations provider; if none are given, abort the system execution.
    //
    if (p_logger_configuration == nullptr)
    {
        log_critical_message("Astra cache server logger has received incorrect initialization configuration parameters.");

        throw status_exception(status::incorrect_parameters, "Incorrect initialization configuration parameters.");
    }

    m_debug_mode_enabled = p_logger_configuration->m_debug_mode_enabled;
    const std::filesystem::path logs_directory_path = std::filesystem::absolute(p_logger_configuration->m_logs_directory_path);

    //
    // Set the session ID after the random number generator has been
    // initialized and ensure that the session ID does not already exist.
    //
    std::string session_id;
    std::filesystem::path session_logs_directory_path;

    do
    {
        session_id = m_random_identifier_generator.generate_double_random_identifier();
        session_logs_directory_path = logs_directory_path;
        session_logs_directory_path.append(c_session_logs_directory_prefix + session_id);
    }
    while (std::filesystem::exists(session_logs_directory_path));

    m_session_id = session_id;

    std::string exception;
    status_code status = utilities::filesystem_utilities::create_directory(
        session_logs_directory_path.string(),
        &exception);

    if (status::failed(status))
    {
        log_critical_message("Astra cache server logger failed to create session logs directory '{}'. Exception: '{}'.",
            session_logs_directory_path.string().c_str(),
            exception.c_str());

        throw status_exception(status, "Failed to create session logs directory.");
    }

    m_session_logs_directory_path = session_logs_directory_path;

    p_initial_message->append("Logs will be stored at '" + m_session_logs_directory_path.string() + "'.");

    //
    // Set the initially pointed logs file after successful initialization.
    //
    m_current_logs_file_path = get_current_logs_file_path();

    //
    // Set the fact that the logger is now initialized.
    //
    s_initialized = true;
}

status_code
logger::initialize(
    const logger_configuration& p_logger_configuration)
{
    if (s_initialized)
    {
        log_critical_message("Astra cache server logger has already been initialized.");

        return status::logger_already_initialized;
    }

    status_code status = status::success;

    log(log_level::info,
        "Astra cache server logger has been initialized. ",
        &status,
        &p_logger_configuration);

    return status;
}

void
logger::log(
    const log_level& p_log_level,
    std::string&& p_message,
    status_code* p_status,
    const logger_configuration* p_logger_configuration)
{
    if (!s_initialized &&
        p_logger_configuration == nullptr)
    {
        log_critical_message("Astra cache server logger has not been yet initialized.",
            status::logger_not_initialized);

        return;
    }

    //
    // Forceful lazy initialization for the
    // singleton through the initialize method.
    //
    try
    {
        static logger logger_singleton_instance(
            &p_message,
            p_logger_configuration);

        logger_singleton_instance.log_message(
            p_log_level,
            p_message.c_str());
    }
    catch (const status_exception& status_exception)
    {
        //
        // Initialization has failed; the error will be circled back to the upper level caller.
        //
        *p_status = status_exception.get_status();
    }
}

void
logger::log_error_fallback(
    std::string&& p_message)
{
    const std::string formatted_message = "<!> Critical error: " + p_message + "\n";
    log_to_syslog(formatted_message.c_str());
    log_error_to_console(formatted_message.c_str());
}

void
logger::set_activity_id(
    const std::string& p_activity_id)
{
    g_activity_id = p_activity_id;
}

void
logger::reset_activity_id()
{
    g_activity_id = c_default_activity_id;
}

bool
logger::is_logger_initialized()
{
    return s_initialized;
}

void
logger::log_message(
    const log_level& p_log_level,
    const character* p_message)
{
    const std::string formatted_log_message = create_formatted_log_message(
        p_log_level,
        p_message);

    {
        std::scoped_lock<std::mutex> lock(m_lock);

        if (m_debug_mode_enabled)
        {
            log_message_to_console(formatted_log_message.c_str());
        }

        status_code status = log_to_file(formatted_log_message.c_str());

        //
        // Syslog retains errors and lost messages if any problem occurs.
        //
        if (status::failed(status))
        {
            log_to_syslog(std::format(
                "Status={}, Message={}",
                status,
                formatted_log_message.c_str()).c_str()); 
        }
    }
}

std::string
logger::create_formatted_log_message(
    const log_level& p_log_level,
    const character* p_message) const
{
    const character* level = nullptr;

    switch (static_cast<uint8>(p_log_level))
    {
        case static_cast<uint8>(log_level::info):
        {
            level = c_info_log_level;

            break;
        }
        case static_cast<uint8>(log_level::warning):
        {
            level = c_warning_log_level;

            break;
        }
        case static_cast<uint8>(log_level::error):
        {
            level = c_error_log_level;

            break;
        }
        case static_cast<uint8>(log_level::critical):
        {
            level = c_critical_log_level;

            break;
        }
        default:
        {
            level = c_default_log_level;

            break;
        }
    }

    return std::format(
        "[{}] ({}) PID={}, TID={}, ActivityID={}. <{}> {}\n",
        timestamp::get_current_timestamp().to_string().c_str(),
        m_session_id.c_str(),
        m_process_id,
        syscall(SYS_gettid),
        g_activity_id,
        level,
        p_message);
}

status_code
logger::log_to_file(
    const character* p_message)
{
    status_code status = status::success;

    //
    // Idemponent logging even if the directory is not present.
    //
    if (!std::filesystem::exists(m_session_logs_directory_path))
    {
        status = utilities::filesystem_utilities::create_directory(m_session_logs_directory_path);

        return_status_if_failed(status)
    }

    //
    // Incremental search for determining the file on which to log the message. Performance of
    // this logging mechanism can be impacted if other processes interfere with the directory.
    // In case of continuous errors that exceed a retry limit, the operation is considered failed.
    //
    std::filesystem::path current_logs_file;

    for (uint16 incremental_search_retry_count = 1; incremental_search_retry_count <= c_max_incremental_search_retry_count; ++incremental_search_retry_count)
    {
        //
        // If the file exists ensure that it has not exceeded the size limit; if it 
        // has, rollover the logs file count and switch the currently pointed logs file.
        //
        if (!std::filesystem::exists(m_current_logs_file_path) ||
            utilities::filesystem_utilities::get_file_size(m_current_logs_file_path.string()) < c_max_logs_file_size_mib)
        {
            for (uint16 logs_writing_attempts_retry_count = 1; logs_writing_attempts_retry_count <= c_max_logs_writing_attempts_retry_count; ++logs_writing_attempts_retry_count)
            {
                status = utilities::filesystem_utilities::append_content_to_file(
                    m_current_logs_file_path,
                    p_message);

                return_status_if_succeeded(status)
            }
        }

        if (incremental_search_retry_count == c_max_incremental_search_retry_count)
        {
            return status::logging_incremental_search_failed;
        }

        ++m_logs_files_count;
        m_current_logs_file_path = get_current_logs_file_path();
    }

    return status;
}

std::filesystem::path
logger::get_current_logs_file_path() const
{
    std::string current_logs_file_name = std::format(
        "log_{}_{}.{}",
        m_session_id,
        m_logs_files_count,
        c_logs_files_extension);

    return m_session_logs_directory_path / current_logs_file_name;
}

void
logger::log_message_to_console(
    const character* p_message)
{
    std::cout << p_message;
}

void
logger::log_error_to_console(
    const character* p_message)
{
    std::cerr << p_message;
}

void
logger::log_to_syslog(
    const character* p_message)
{
    openlog(c_astra_executable_name, LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_ERR, "%s", p_message);
    closelog();
}

} // namespace astra.