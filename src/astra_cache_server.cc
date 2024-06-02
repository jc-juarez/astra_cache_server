// *************************************
// Astra Cache Server
// Server
// 'astra_cache_server.cc'
// Author: jcjuarez
// *************************************

#include "logger.hh"
#include "system_server.hh"
#include "astra_cache_server.hh"
#include "system_configuration.hh"

namespace astra
{

astra_cache_server::astra_cache_server(
    const system_configuration& p_system_configuration)
{
    try
    {
        m_system_server = std::make_unique<server::system_server>(
            p_system_configuration.m_server_configuration);
    }
    catch (const status_exception& status_exception)
    {
        log_critical_message("Astra cache server encountered an error while initializing its subcomponents. Status={:#X}. Exception={}",
            status_exception.get_status(),
            status_exception.what());

        //
        // Rethrow to the upper level caller.
        //
        throw;
    }
}

status_code
astra_cache_server::start_server()
{
    status_code status = status::success;

    status = m_system_server->start();

    if (status::failed(status))
    {
        log_critical_message("Astra cache server encountered an error during the system server startup process. Status={:#X}.",
            status);

        return status;
    }

    return status;
}

exit_code
astra_cache_server::run(
    const std::vector<std::string>&& p_command_line_arguments)
{
    status_code status = initialize(std::move(p_command_line_arguments));

    return status::succeeded(status) ? EXIT_SUCCESS : EXIT_FAILURE;
}

status_code
astra_cache_server::initialize(
    const std::vector<std::string>&& p_command_line_arguments)
{
    //
    // Initialize the system configuration for all components.
    //
    try
    {
        const system_configuration astra_system_configuration(
            p_command_line_arguments);

        //
        // Initialize singleton logger for the system.
        //
        status_code status = logger::initialize(astra_system_configuration.m_logger_configuration);

        if (status::failed(status))
        {
            log_critical_message("Astra cache server logger initialization failed. Status={:#X}.",
                status);

            return status;
        }

        astra::server::system_server server(astra_system_configuration.m_server_configuration);
        server.start();

        return status::success;
    }
    catch (const status_exception& status_exception)
    {
        log_critical_message("Astra cache server system initialization failed. Status={:#X}. Exception={}",
            status_exception.get_status(),
            status_exception.what());

        return status_exception.get_status();
    }
}

} // namespace astra.