// *************************************
// Astra Cache Server
// Utilities
// 'system_configuration.cc'
// Author: jcjuarez
// *************************************

#include "logger.hh"
#include <unordered_set>
#include "system_configuration.hh"

namespace astra
{

logger_configuration::logger_configuration()
    : m_debug_mode_enabled(c_default_debug_mode_enabled),
      m_logs_directory_path("")
{}

server_configuration::server_configuration()
    : m_port_number(c_default_port_number)
{}

status_code
system_configuration::set_logs_directory_path(
    const std::string& p_logs_directory_path)
{
    if (!p_logs_directory_path.empty())
    {
        m_logger_configuration.m_logs_directory_path = p_logs_directory_path;

        return status::success;
    }

    const character* home_environment_variable = std::getenv(c_default_logs_directory_environment_variable);

    if (home_environment_variable == nullptr)
    {
        log_critical_message("Astra cache server system configuration could not access the '{}' environment variable.",
            c_default_logs_directory_environment_variable);
        
        return status::environment_variable_access_failed;
    }

    m_logger_configuration.m_logs_directory_path = std::string(home_environment_variable) + "/" + std::string(c_default_logs_directory_name);

    return status::success;
}

system_configuration::system_configuration(
    const std::vector<std::string>& p_command_line_arguments)
{
    status_code status = status::success;

    std::string logs_directory_path;

    if (!p_command_line_arguments.empty())
    {
        status = parse_command_line_arguments(
            p_command_line_arguments,
            &logs_directory_path);

        if (status::failed(status))
        {
            throw status_exception(status, "Failed to parse command line arguments.");
        }
    }

    //
    // Initialize runtime defined configurations.
    //
    status = set_logs_directory_path(logs_directory_path);

    if (status::failed(status))
    {
        throw status_exception(status, "Failed to set the logs directory path.");
    }
}

status_code
system_configuration::parse_command_line_arguments(
    const std::vector<std::string>& p_command_line_arguments,
    std::string* p_logs_directory_path)
{
    const std::string astra_executable_name = p_command_line_arguments.front();

    //
    // Configurations override is based on flags.
    //
    uint8 flag_indicator_symbol_index = 0;
    uint8 flag_name_index = 1;
    uint8 flag_assignment_symbol_index = 2;
    uint8 flag_value_index = 3;
    uint8 minimum_flag_size = 4;

    const std::unordered_set<character> available_flags
    {
        c_debug_mode_enabled_flag,
        c_logs_directory_flag,
        c_port_number
    };

    for (const std::string& flag : p_command_line_arguments)
    {
        if (flag == astra_executable_name ||
            flag == c_sudo)
        {
            continue;
        }

        //
        // Care for malformed flags.
        //
        if (flag.size() < minimum_flag_size ||
            flag[flag_indicator_symbol_index] != c_flag_indicator ||
            flag[flag_assignment_symbol_index] != c_flag_assignment)
        {            
            log_critical_message("Astra cache server could not parse the '{}' flag.",
                flag.c_str());

            return status::malformed_command_line_arguments;
        }

        character flag_name = flag[flag_name_index];

        //
        // Ensure that the provided configuration flag is valid.
        //
        if (available_flags.find(flag_name) == available_flags.end())
        {
            log_critical_message("Astra cache server could not recognize the '{}' flag name.",
                flag_name);

            return status::configuration_flag_not_recognized;
        }

        std::string flag_value = flag.substr(flag_value_index);

        switch (flag_name)
        {
            case c_debug_mode_enabled_flag:
            {
                status_code status = parse_on_off_to_bool(
                    flag_value,
                    &(m_logger_configuration.m_debug_mode_enabled));

                if (status::failed(status))
                {
                    log_critical_message("Astra cache server could not parse the '{}' flag value.",
                        flag_value);

                    return status;
                }

                break;
            }
            case c_logs_directory_flag:
            {
                *p_logs_directory_path = flag_value;

                break;
            }
            case c_port_number:
            {
                try
                {
                    m_server_configuration.m_port_number = std::stoi(flag_value);
                }
                catch (const std::exception& exception)
                {
                    log_critical_message("Astra cache server could not parse the '{}' flag value.",
                        flag_value);

                    return status::incorrect_parameters;
                }

                break;
            }
            default:
            {
                return status::configuration_flag_not_recognized;
            }
        }
    }

    return status::success;
}

status_code
system_configuration::parse_on_off_to_bool(
    const std::string& p_value,
    bool* p_bool)
{
    if (p_value == c_on_value)
    {
        *p_bool = true;

        return status::success;
    }
    else if (p_value == c_off_value)
    {
        *p_bool = false;

        return status::success;
    }

    return status::incorrect_parameters;
}

} // namespace astra.