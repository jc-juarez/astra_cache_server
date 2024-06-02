// *************************************
// Astra Cache Server
// Server
// 'main.cc'
// Author: jcjuarez
// *************************************

#include "common.hh"
#include "logger.hh"
#include "system_server.hh"
#include "system_configuration.hh"

int main(int argc, char** argv)
{
    using namespace astra;

    std::vector<std::string> command_line_arguments(argv, argv + argc);

    //
    // Initialize the system configuration for all components.
    //
    try
    {
        system_configuration astra_system_configuration(
            command_line_arguments);

        //
        // Initialize singleton logger for the system.
        //
        status_code status = logger::initialize(astra_system_configuration.m_logger_configuration);

        if (status::failed(status))
        {
            log_critical_message("Astra cache server logger initialization failed. Status={:#X}.",
                status);

            return EXIT_FAILURE;
        }

        astra::server::system_server server;
        server.start();

        return EXIT_SUCCESS;
    }
    catch (const status_exception& exception)
    {
        log_critical_message("Astra cache server system initialization failed. Status={:#X}. Exception={}",
            exception.get_status(),
            exception.what());

        return EXIT_FAILURE;
    }
}